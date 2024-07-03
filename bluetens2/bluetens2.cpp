#include <ultracore.h>
#include <sys/errno.h>

#include <gpio.h>
#include <pmu.h>
#include <pwm.h>
#include <timer.h>
#include <wdt.h>

#include "app.hpp"

#ifdef NO_PINKTENS
    #pragma GCC warning "this project is Bluetens only"
#endif

/***************************************************************************/
/** @declaration
****************************************************************************/
enum LED_indicator_t
{
    LED_IND_OFF,
    LED_IND_POWER,
    LED_IND_SELECT_FILE,
    LED_IND_BATT,
    LED_IND_LOW_BATT,
    LED_IND_INTENSITY,
};

struct LED_context_t
{
    int pwm;

    enum LED_indicator_t ind;
    event_t evt;

    int file_idx;
};

/***************************************************************************/
/** @consts
****************************************************************************/
#define PWM_FREQ                        (32000000)
#define INTENSITY_TABLE_SIZE            (60)

static uint16_t const BLUETENS_table[INTENSITY_TABLE_SIZE + 1] =
{
    800,
     15,  25,  35,  45,  55,  65,  75,  85,  95, 105,
    114, 123, 132, 141, 150, 159, 168, 177, 186, 195,
    203, 211, 219, 227, 235, 243, 251, 259, 267, 275,
    283, 291, 299, 307, 315, 323, 331, 339, 347, 355,
    362, 369, 376, 383, 390, 397, 404, 411, 418, 425,
    432, 439, 446, 453, 460, 467, 474, 481, 488, 495,
};

static uint16_t const PINKTENS_table[INTENSITY_TABLE_SIZE + 1] =
{
    800,
     15,  24,  33,  42,  51,  60,  69,  78,  87,  96,
    104, 112, 120, 128, 136, 144, 152, 160, 168, 176,
    183, 190, 197, 204, 211, 218, 225, 232, 239, 246,
    252, 258, 264, 270, 276, 282, 288, 294, 300, 306,
    312, 318, 324, 330, 336, 342, 348, 354, 360, 366,
    371, 376, 381, 386, 391, 396, 401, 406, 411, 416,
};

static uint16_t const *INTENSITY_table = NULL;

#define LED_FREQ                        (100000)
#define LED_MAX_LUMA                    (255)
#define LED_FPS                         (LED_FREQ / LED_MAX_LUMA)
#define LED_POWERUP_FRAMES              (LED_FPS / 4)
#define LED_LOW_BATT_FRAMES             (LED_FPS * 4 / 5)

/***************************************************************************/
/** @internal
****************************************************************************/
static void LED_configure(void);
static void LED_switch_indicator(enum LED_indicator_t ind);
static void LED_callback(uint16_t id, void *arg, uint32_t loop);
static void GPIO_callback(uint32_t pins, void *arg);

/// @var
static struct LED_context_t LED_context = {-1, LED_IND_OFF, EVENT_INITIALIZER(true, false), -1};
static int INTENSITY_pwm = -1;

/***************************************************************************/
/** @export
****************************************************************************/
void PLATFORM_init(void)
{
    // SYSCON_systick_precision(1);

    GPIO_setdir_input_pp(PULL_UP, PIN_POWER_BUTTON | PIN_ADD_BUTTON | PIN_SUB_BUTTON, true);
    GPIO_setdir_input_pp(PULL_UP, PIN_CHARGING_DET | PIN_HV_PULSE_DET, true);
    GPIO_setdir_input(PINKTENS_DET);

    GPIO_setdir_output(PUSH_PULL_DOWN, PIN_LDO_POWER | PWM_PIN |
        PIN_OUT1 | PIN_OUT2 | PIN_OUT3 | PIN_OUT4 |
        PIN_HV_CTRL | PIN_ASY_CTL);

    OUTPUT_release();
    LED_configure();

    // dummy, checking everytime startting output
    if (DET_is_pinktens())
        INTENSITY_table = PINKTENS_table;
    else
        INTENSITY_table = BLUETENS_table;

    WDT_CLK_enable();
    WDOG_init(64000);
}

bool PLATFORM_startup(void)
{
    bool retval;

#ifndef NO_DET_CHARGING
    if (DET_is_charging())
    {
        /* why input?
#ifdef BG22
        GPIO_setdir_input(PIN_ORANGE_EN | PIN_LED1 | PIN_LED2 | PIN_LED3 | PIN_LED4);
#endif
        */
#ifdef QN908X
        LED_switch_indicator(LED_IND_BATT);
#else
        // hardware control
        GPIO_disable(PIN_ORANGE_EN);
#endif

        while (DET_is_charging())
        {
            WDOG_feed();
            msleep(5);
        }
        retval = false;
    }
    else
#endif
    {
#ifndef NO_DET_BATTERY
        int batt;
        while (0 == (batt = App->Battery()))
            msleep(5);
#else
        int batt = 3700;
#endif
        if (BATTERY_EMPTY_VOLTAGE < batt)
            LED_switch_indicator(LED_IND_POWER);

        retval = true;
    }

    GPIO_intr_enable(PIN_POWER_BUTTON, TRIG_BY_FALLING_EDGE, GPIO_callback, App);
    GPIO_intr_enable(PIN_ADD_BUTTON, TRIG_BY_FALLING_EDGE, GPIO_callback, App);
    GPIO_intr_enable(PIN_SUB_BUTTON, TRIG_BY_FALLING_EDGE, GPIO_callback, App);

    return retval;
}

void PLATFORM_shutdown(void)
{
    OUTPUT_release();
    LED_switch_indicator(LED_IND_OFF);
    TIMER_deconfigure(HW_TIMER1);

    // wait for "NOTIFY shutdown" to be sent
    msleep(500);

#ifdef QN908X
    GPIO_wakeup_en(PIN_POWER_BUTTON, false);
    GPIO_wakeup_en(PIN_CHARGING_DET, false);
#else
    GPIO_disable(PIN_CHARGING_DET);

    GPIO_intr_disable(PIN_ADD_BUTTON);
    GPIO_intr_disable(PIN_SUB_BUTTON);

    while (0 == GPIO_peek(PIN_POWER_BUTTON));
#endif
}

void PLATFORM_lowbattery(void)
{
    LED_switch_indicator(LED_IND_LOW_BATT);
}

void PLATFORM_msg_activity(uint32_t MsgId)
{
    ARG_UNUSED(MsgId);
    WDOG_feed();
}

void PLATFORM_idle(void)
{
    WDOG_feed();
}

void INTENSITY_TUV_power_control(bool en, uint32_t intensity)
{
  ARG_UNUSED(en);
  ARG_UNUSED(intensity);
}

void INTENSITY_ctrl_init(void)
{
    INTENSITY_pwm = PWM_get(PWM_FREQ, PWM_PIN, NULL);

    if (DET_is_pinktens())
        INTENSITY_table = PINKTENS_table;
    else
        INTENSITY_table = BLUETENS_table;

    GPIO_set(PIN_LDO_POWER);
    INTENSITY_ctrl(1);

    LED_switch_indicator(LED_IND_INTENSITY);
}

void INTENSITY_ctrl_release(uint32_t value)
{
    ARG_UNUSED(value);

    GPIO_clear(PIN_LDO_POWER);
    GPIO_set(PIN_LED1 | PIN_LED2 | PIN_LED3 | PIN_LED4);

    PWM_release(INTENSITY_pwm);
    INTENSITY_pwm = -1;

    if (! App->Shuttingdown() && TApplication::stateRunning >= App->State())
        LED_switch_indicator(LED_IND_POWER);
}

int INTENSITY_ctrl(uint32_t value)
{
    if (-1 == INTENSITY_pwm)
        return __set_errno_neg(ENODEV);
    if (0 == value)
        return __set_errno_neg(EINVAL);

    if (value > INTENSITY_TABLE_SIZE)
        value = INTENSITY_TABLE_SIZE;

    if (0 == PWM_update(INTENSITY_pwm, INTENSITY_table[value], INTENSITY_table[0]))
    {
        /*
        static uint8_t const LED_table[INTENSITY_TABLE_SIZE] =
        {
              5,   7,   9,  11,  13,  15,  17,  19,  21,  23,  25,  27,  29,  31,  33,
             36,  39,  42,  45,  48,  51,  54,  57,  60,  63,  66,  69,  72,  75,  78,
             82,  86,  90,  94,  98, 102, 106, 110, 114, 118, 122, 126, 130, 134, 138,
            153, 158, 163, 168, 173, 178, 183, 188, 193, 198, 203, 208, 213, 218, 223
        };

        if (0 >= LED_context.pwm)
            LED_context.pwm = PWM_get(LED_FREQ, PIN_BLUE_EN, NULL);

        if (0 < LED_context.pwm)
        {
            PWM_update(LED_context.pwm, LED_MAX_LUMA - LED_table[value - 1], LED_MAX_LUMA);
            GPIO_clear(PIN_LED1 | PIN_LED2 | PIN_LED3 | PIN_LED4);
        }
        */
        static uint16_t const LED_table[INTENSITY_TABLE_SIZE / 4] =
        {
            20, 28, 36, 44, 52, 60, 70, 80, 90, 115, 130, 150, 170, 200, 235
        };

        TIMER_stop(HW_TIMER1);
        uint32_t PIN_LED;

        GPIO_set(PIN_LED1 | PIN_LED2 | PIN_LED3 | PIN_LED4);

        if (value > 0)
        {
            PIN_LED = PIN_LED1;
        }
        if (value >= INTENSITY_TABLE_SIZE / 4)
        {
            GPIO_clear(PIN_LED1);
            PIN_LED = PIN_LED2;
        }
        if (value >= INTENSITY_TABLE_SIZE / 2)
        {
            GPIO_clear(PIN_LED2);
            PIN_LED = PIN_LED3;
        }
        if (value >= INTENSITY_TABLE_SIZE * 3 / 4)
        {
            GPIO_clear(PIN_LED3);
            PIN_LED = PIN_LED4;
        }
        if (value == INTENSITY_TABLE_SIZE)
        {
            GPIO_clear(PIN_LED4);
            PIN_LED = 0;
        }

        uint32_t step = value % 15;
        if (0 != step)
        {
            TIMER_match_clear(HW_TIMER1);

            TIMER_match(HW_TIMER1, 0x8000, LED_MAX_LUMA, (void *)PIN_LED);
            TIMER_match(HW_TIMER1, 0x0000, LED_table[step - 1], (void *)PIN_LED);

            TIMER_start(HW_TIMER1);
            GPIO_clear(PIN_LED);
        }
    }
    return value;
}

/***************************************************************************/
/** @internal
****************************************************************************/
static void GPIO_callback(uint32_t pins, void *arg)
{
    if (PIN_ADD_BUTTON == (PIN_ADD_BUTTON & pins) && TApplication::stateStopped == App->State())
    {
        int count = 0;
        uint8_t idx;

        for (uint8_t i = 0; i < DEF_FILE_COUNT; i ++)
        {
            char const *filename = App->DefaultFile(i);

            if ('\0' != filename[0])
            {
                count ++;
                idx = i;
            }
        }

        // direct start when only 1 default file was set
        if (1 == count)
        {
            LED_context.file_idx = idx;
            goto start_default_file;
        }

        if (0 < count)
        {
            idx = (uint8_t)LED_context.file_idx;
            while (true)
            {
                idx = (uint8_t)(idx + 1) % DEF_FILE_COUNT;

                char const *filename = App->DefaultFile(idx);

                if ('\0' != filename[0])
                    break;
            }
            LED_context.file_idx = idx;
            LED_switch_indicator(LED_IND_SELECT_FILE);
        }

        ((TApplication *)arg)->UpdateLastActivity();
    }
    else if (LED_IND_SELECT_FILE == LED_context.ind)
    {
        if (PIN_SUB_BUTTON & pins)
        {
            LED_context.file_idx = -1;
            LED_switch_indicator(LED_IND_POWER);
        }
        else if (PIN_POWER_BUTTON & pins)
        {
            LED_switch_indicator(LED_IND_POWER);

start_default_file:
            ((TApplication *)arg)->StartDefaultFile((uint8_t)LED_context.file_idx);
            LED_context.file_idx = -1;
        }

        ((TApplication *)arg)->UpdateLastActivity();
    }
    else
    {
        ((TApplication *)arg)->GPIO_callback(pins);
    }
}

static void LED_configure(void)
{
    GPIO_setdir_output(PUSH_PULL, PIN_LED1 | PIN_LED2 | PIN_LED3 | PIN_LED4);
    GPIO_set(PIN_LED1 | PIN_LED2 | PIN_LED3 | PIN_LED4);

    GPIO_setdir_output(PUSH_PULL, PIN_BLUE_EN | PIN_ORANGE_EN | PIN_WHITE_EN);
    LED_switch_indicator(LED_IND_OFF);

    TIMER_match_configure(HW_TIMER1, LED_FREQ, LED_callback);
}

static void LED_switch_indicator(enum LED_indicator_t ind)
{
    uint32_t pin;

    switch(ind)
    {
    case LED_IND_POWER:
    case LED_IND_SELECT_FILE:
        pin = PIN_WHITE_EN;
        break;

    case LED_IND_BATT:
    case LED_IND_LOW_BATT:
        pin = PIN_ORANGE_EN;
        break;

    case LED_IND_INTENSITY:
        pin = PIN_BLUE_EN; // | (DET_is_pinktens() ? PIN_ORANGE_EN : 0);
        break;

    default:
        pin = 0;
        break;
    }
    GPIO_set(PIN_BLUE_EN | PIN_ORANGE_EN | PIN_WHITE_EN);
    GPIO_set(PIN_LED1 | PIN_LED2 | PIN_LED3 | PIN_LED4);

    if (pin)
        GPIO_clear(pin);

    TIMER_stop(HW_TIMER1);
    TIMER_match_clear(HW_TIMER1);

    if (LED_IND_POWER == ind)
    {
        /// power off => power up
        if (LED_IND_OFF == LED_context.ind)
        {
            for (int i = 1; i <= LED_POWERUP_FRAMES; i ++)
            {
                TIMER_match(HW_TIMER1, 0x8000, LED_MAX_LUMA, (void *)(PIN_LED1 | PIN_LED2 | PIN_LED3 | PIN_LED4));
                TIMER_match(HW_TIMER1, 0x0000, i * LED_MAX_LUMA / LED_POWERUP_FRAMES, (void *)(PIN_LED1 | PIN_LED2 | PIN_LED3 | PIN_LED4));

                event_reset(&LED_context.evt);
                TIMER_start(HW_TIMER1);

                waitfor(&LED_context.evt, WAIT_FOREVER);

                TIMER_stop(HW_TIMER1);
                TIMER_match_clear(HW_TIMER1);
            }
            GPIO_clear(PIN_LED1 | PIN_LED2 | PIN_LED3 | PIN_LED4);
        }
        else
        {
            GPIO_clear(PIN_LED1 | PIN_LED2 | PIN_LED3 | PIN_LED4);
        }
    }
    else if (LED_IND_SELECT_FILE == ind)
    {
        GPIO_set(PIN_LED1 | PIN_LED2 | PIN_LED3 | PIN_LED4);

        switch(LED_context.file_idx)
        {
        case 0:
            GPIO_clear(PIN_LED1);
            break;
        case 1:
            GPIO_clear(PIN_LED2);
            break;
        case 2:
            GPIO_clear(PIN_LED3);
            break;
        case 3:
            GPIO_clear(PIN_LED4);
            break;
        }
    }
    else if (LED_IND_LOW_BATT == ind)
    {
        for (int n = 0; n < 3; n ++)
        {
            for (int i = LED_LOW_BATT_FRAMES; i > 1; i --)
            {
                TIMER_match(HW_TIMER1, 0x8000, LED_MAX_LUMA, (void *)PIN_ORANGE_EN);
                TIMER_match(HW_TIMER1, 0x0000, i * LED_MAX_LUMA / LED_LOW_BATT_FRAMES, (void *)PIN_ORANGE_EN);

                event_reset(&LED_context.evt);
                TIMER_start(HW_TIMER1);

                waitfor(&LED_context.evt, WAIT_FOREVER);

                TIMER_stop(HW_TIMER1);
                TIMER_match_clear(HW_TIMER1);
            }
        }
        GPIO_set(PIN_LED1 | PIN_LED2 | PIN_LED3 | PIN_LED4);
    }
    else if (LED_IND_BATT == ind)
    {
        GPIO_clear(PIN_LED1 | PIN_LED2 | PIN_LED3 | PIN_LED4);
    }

    LED_context.ind = ind;
}

static void LED_callback(uint16_t id, void *arg, uint32_t loop)
{
    ARG_UNUSED(loop);

    if (0x8000 == id)
    {
        GPIO_clear((uint32_t)arg);
        event_signal(&LED_context.evt);
    }
    else
        GPIO_set((uint32_t)arg);
}
