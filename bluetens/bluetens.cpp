#include <ultracore.h>
#include <sys/errno.h>

#include <gpio.h>
#include <timer.h>
#include <pwm.h>

#include "app.hpp"

/***************************************************************************/
/** @consts
****************************************************************************/
#define WDOG_feed()                     (QN_WDT->LOAD = 32879 * 3)

#define PWM_FREQ                        (16000000)
#define PIN_VOLT_PWM                    (P15)

static uint16_t const INTENSITY_table[] =
{
   1000,
     15,  25,  35,  46,  57,  68,  79,  90, 101, 112,
    124, 136, 148, 160, 172, 184, 196, 208, 220, 236,
    248, 261, 274, 287, 300, 313, 326, 339, 352, 364,
    376, 388, 400, 412, 424, 436, 448, 460, 472, 484,
    496, 507, 518, 529, 540, 551, 562, 573, 584, 595,
    606, 617, 628, 640, 652, 664, 682, 700, 718, 736
};
#define INTENSITY_MAX                   (lengthof(INTENSITY_table) - 1)
#define INTENSITY_TUV_POWER_CONTROL     (50)

// XTAL / FREQ_LED < 1024
// base 16K / 200 = 80FPS
#define LED_FREQ                        (32000)
#define LED_MAX_LUMA                    (200)
#define LED_FPS                         (LED_FREQ / LED_MAX_LUMA)

#define LED_POWER_UP_FRAMES             (LED_FPS / 6)
#define LED_POWER_DOWN_FRAMES           (LED_FPS / 8)
#define LED_LOW_BATTERY_FRAMES          (LED_FPS / 3)

static uint16_t const LED_table[sizeof(INTENSITY_table) / 4] =
{
    1, 3, 5, 8, 12, 18, 26, 36, 48, 62, 78, 96, 116, 138, 162
};

#ifdef HW_DEBUG
    #define PIN_HW_VISION_DET
#else
    #define PIN_HW_VISION_DET           P06
#endif
    #define PIN_RESISTANT               P16

/***************************************************************************/
/** @internal
****************************************************************************/
static void LED_powerup(uint16_t frames);
static void LED_powerdown(uint16_t frames);
static void LED_callback(uint16_t id, void *arg, uint32_t loop);

static void GPIO_callback(uint32_t pins, void *arg);

/*
500 ohm
    60      100
    50      85      -15
    40      73      -12
    30      60      -13
    20      47      -21
    10      26      -15
    1       9.5

    60      60.1
    51,
    41      44.8
    31      36.8
    21      27.8
    11      17.8
    1        7.1

*/
/// @var
static event_t LED_event = EVENT_INITIALIZER(true, false);
static int PWM_no = -1;

/***************************************************************************/
/** ultracore @override
****************************************************************************/
void KERNEL_next_tick(uint32_t millisecond)
{
    ARG_UNUSED(millisecond);

    WDOG_feed();
    __WFI();
}

void PLATFORM_msg_activity(uint32_t MsgId)
{
    ARG_UNUSED(MsgId);
    WDOG_feed();
}

/***************************************************************************/
/** @export
****************************************************************************/
void PLATFORM_init(void)
{
#ifndef HW_DEBUG
    QN_WDT->LOCK = 0x1ACCE551;
    WDOG_feed();
    QN_WDT->CTRL = WDT_MASK_CTRL_RESEN | WDT_MASK_CTRL_INTEN;

    BITS_setvalue(QN_SYSCON->PMCR0, 15, 12, 0x05);
    GPIO_pad_pull(PULL_DOWN, PIN_HW_VISION_DET);
#endif

    if (DET_is_charging())
        USB_plugin();

    GPIO_set(PIN_POWER_LED |
        PIN_STR_LED1 | PIN_STR_LED2 | PIN_STR_LED3 | PIN_STR_LED4 |
        PIN_RESISTANT);
    GPIO_setdir_output(PUSH_PULL, PIN_POWER_LED | PIN_DIAL_EN | PIN_VOLT_PWM |
        PIN_STR_LED1 | PIN_STR_LED2 | PIN_STR_LED3 | PIN_STR_LED4 |
        PIN_OUT1 | PIN_OUT2 | PIN_OUT3 | PIN_OUT4 |
        PIN_RESISTANT);

    GPIO_clear(PIN_VOLT_PWM);
    OUTPUT_release();

    // GPIO_pad_pull(PULL_UP, PIN_HW_VISION_DET);
    GPIO_set(PIN_DIAL_EN);
    msleep(10);

    // todo HW version det here
    // GPIO_pad_pull(PULL_DOWN, PIN_HW_VISION_DET);
}

bool PLATFORM_startup(void)
{
    bool retval;

    if (DET_is_charging())
    {
        // wait charging plug
        while (DET_is_charging())
            msleep(0);

        retval = false;
    }
    else
    {
        TIMER_match_configure(HW_TIMER3, LED_FREQ, LED_callback);
        LED_powerup(LED_POWER_UP_FRAMES);
        retval = true;
    }

    GPIO_intr_enable(PIN_POWER_BUTTON, TRIG_BY_FALLING_EDGE, GPIO_callback, App);
    GPIO_intr_enable(PIN_CHARGING_DET, TRIG_BY_RISING_EDGE, GPIO_callback, App);
    GPIO_intr_enable(PIN_DIAL_CW, TRIG_BY_RISING_EDGE, GPIO_callback, App);

    return retval;
}

void PLATFORM_lowbattery(void)
{
    uint32_t v = QN_GPIO->INTENSET;
    QN_GPIO->INTENCLR = v;

    for (int i = 0; i < 3; i ++)
    {
        if (IS_DUTCH_DEVICE())
        {
            GPIO_set(PIN_POWER_LED);
            msleep(500);
            GPIO_clear(PIN_POWER_LED);
            msleep(500);
        }
        else
        {
            LED_powerdown(LED_LOW_BATTERY_FRAMES);
            LED_powerup(LED_LOW_BATTERY_FRAMES);
        }
    }
    QN_GPIO->INTENSET = v;
}

void PLATFORM_shutdown(void)
{
    OUTPUT_off();

    // GPIO high -> low power leak fix
    if (! DET_is_charging())
        GPIO_setdir_output(PUSH_PULL_DOWN, PIN_CHARGING_DET);

    // power leak
    GPIO_setdir_output(PUSH_PULL_DOWN, PIN_DIAL_EN | PIN_DIAL_CCW | PIN_DIAL_CW | PIN_VOLT_PWM |
        PIN_RESISTANT);

    if (TIMER_is_configured(HW_TIMER3))
        LED_powerdown(LED_POWER_DOWN_FRAMES);
}

void INTENSITY_ctrl_init(void)
{
    PWM_no = TIMER_PWM_get(PWM_FREQ, PIN_VOLT_PWM, NULL);
}

void INTENSITY_ctrl_release(uint32_t value)
{
    TIMER_stop(HW_TIMER3);
    GPIO_set(PIN_STR_LED1 | PIN_STR_LED2 | PIN_STR_LED3 | PIN_STR_LED4);

    TIMER_deconfigure(PWM_no);
    PWM_no = -1;
}

void INTENSITY_TUV_power_control(bool en, uint32_t intensity)
{
    if (en && (intensity > INTENSITY_TUV_POWER_CONTROL))
        TIMER_PWM_update(PWM_no, INTENSITY_table[INTENSITY_TUV_POWER_CONTROL], INTENSITY_table[0]);
    else
        TIMER_PWM_update(PWM_no, INTENSITY_table[intensity], INTENSITY_table[0]);
}

int INTENSITY_ctrl(uint32_t value)
{
    if (-1 == PWM_no)
        return __set_errno_neg(ENODEV);
    if (0 == value)
        return __set_errno_neg(EINVAL);

    if (value > INTENSITY_MAX)
        value = INTENSITY_MAX;

    TIMER_PWM_update(PWM_no, INTENSITY_table[value], INTENSITY_table[0]);

    TIMER_stop(HW_TIMER3);
    uint32_t PIN_STR_LED;

    GPIO_set(PIN_STR_LED1 | PIN_STR_LED2 | PIN_STR_LED3 | PIN_STR_LED4);

    if (value > 0)
    {
        PIN_STR_LED = PIN_STR_LED1;
    }
    if (value >= INTENSITY_MAX / 4)
    {
        GPIO_clear(PIN_STR_LED1);
        PIN_STR_LED = PIN_STR_LED2;
    }
    if (value >= INTENSITY_MAX / 2)
    {
        GPIO_clear(PIN_STR_LED2);
        PIN_STR_LED = PIN_STR_LED3;
    }
    if (value >= INTENSITY_MAX * 3 / 4)
    {
        GPIO_clear(PIN_STR_LED3);
        PIN_STR_LED = PIN_STR_LED4;
    }
    if (value == INTENSITY_MAX)
    {
        GPIO_clear(PIN_STR_LED4);
        PIN_STR_LED = 0;
    }

    uint32_t step = value % 15;
    if (0 != step)
    {
        TIMER_match_clear(HW_TIMER3);

        TIMER_match(HW_TIMER3, 0x8000, LED_MAX_LUMA, (void *)PIN_STR_LED);
        TIMER_match(HW_TIMER3, 0x0000, LED_table[step - 1], (void *)PIN_STR_LED);

        TIMER_start(HW_TIMER3);
        GPIO_clear(PIN_STR_LED);
    }
    return value;
}

void USB_plugin(void)
{
    BITS_setvalue(QN_SYSCON->PMCR0, 2, 0, 0x00);        // UART0.TXD to GPIO
    BITS_setvalue(QN_SYSCON->PMCR0, 32, 30, 0x00);      // UART0.RXD to GPIO
}

/***************************************************************************/
/** @internal
****************************************************************************/
static void LED_powerup(uint16_t frames)
{
    for (int i = 1; i <= frames; i ++)
    {
        TIMER_stop(HW_TIMER3);
        TIMER_match_clear(HW_TIMER3);

        TIMER_match(HW_TIMER3, 0x8000, LED_MAX_LUMA, (void *)PIN_POWER_LED);
        TIMER_match(HW_TIMER3, 0x0000, i * LED_MAX_LUMA / frames, (void *)PIN_POWER_LED);

        event_reset(&LED_event);
        TIMER_start(HW_TIMER3);

        waitfor(&LED_event, WAIT_FOREVER);
    }

    TIMER_stop(HW_TIMER3);
    GPIO_clear(PIN_POWER_LED);
}

static void LED_powerdown(uint16_t frames)
{
    TIMER_stop(HW_TIMER3);
    TIMER_match_clear(HW_TIMER3);

    for (int i = 1; i <= frames; i ++)
    {
        TIMER_stop(HW_TIMER3);
        TIMER_match_clear(HW_TIMER3);

        TIMER_match(HW_TIMER3, 0x8000, LED_MAX_LUMA, (void *)PIN_POWER_LED);
        TIMER_match(HW_TIMER3, 0x0000, LED_MAX_LUMA - i * LED_MAX_LUMA / frames, (void *)PIN_POWER_LED);

        event_reset(&LED_event);
        TIMER_start(HW_TIMER3);

        waitfor(&LED_event, WAIT_FOREVER);
    }
    TIMER_stop(HW_TIMER3);
    GPIO_set(PIN_POWER_LED);
}

static void LED_callback(uint16_t id, void *arg, uint32_t loop)
{
    if (0x8000 == id)
    {
        GPIO_clear((uint32_t)arg);
        event_signal(&LED_event);
    }
    else
        GPIO_set((uint32_t)arg);
}

/***************************************************************************/
/** @INT callback
****************************************************************************/
static void GPIO_callback(uint32_t pins, void *arg)
{
    ((TApplication *)arg)->GPIO_callback(pins);
}
