#include <sys/errno.h>
#include <gpio.h>
#include <pwm.h>

#include "app.hpp"

/***************************************************************************/
/** @declaration
****************************************************************************/
    #define FREQ_PWM                    8000000
    #define PIN_PWM                     P26

/***************************************************************************/
/** @internal
****************************************************************************/
static void GPIO_callback(uint32_t pins, void *arg);

/// @var
static uint8_t const INTENSITY_table[] =
{
    200,
           1,   2,   3,   4,   5,   6,   7,   8,   9,
     10,  11,  12,  13,  14,  15,  16,  17,  18,  19,
     20,  21,  22,  23,  24,  25,  26,  27,  28,  29,
     30,  31,  32,  33,  34,  35,  36,  37,  38,  39,
     40,  41,  42,  43,  44,  45,  46,  47,  48,  49,
     50,  51,  52,  53,  54,  55,  56,  57,  58,  59,
     60,  61,  62,  63,  64,  65,  66,  67,  68,  69,
     70,  71,  72,  73,  74,  75,  76,  77,  78,  79,
     80,  81,  82,  83,  84,  85,  86,  87,  88,  89,
     90,  91,  92,  93,  94,  95,  96,  97,  98,  99,
    100, 101, 102, 103, 104, 105, 106, 107, 108, 109,
    110, 111, 112, 113, 114, 115, 116, 117, 118, 119,
    120, 121, 122, 123, 124, 125, 126, 127, 128, 129,
    130, 131, 132, 133, 134, 135, 136, 137, 138, 139,
    140, 141, 142, 143, 144, 145, 146, 147, 148, 149,
    150, 151, 152, 153, 154, 155, 156, 157, 158, 159,
    160, 161, 162, 163, 164, 165, 166, 167, 168, 169,
    170, 171, 172, 173, 174, 175, 176, 177, 178, 179,
    180, 181, 182, 183, 184, 185, 186, 187, 188, 189,
    190, 191, 192, 193, 194, 195, 196, 197, 198, 199,
};

static int PWM_no = -1;

/***************************************************************************/
/** @export
****************************************************************************/
void PLATFORM_init(void)
{
#ifndef HW_DEBUG
    QN_SYSCON->PPCR0 = 0xAAAAAAAA;
    BITS_setvalue(QN_SYSCON->PMCR0, 15, 12, 0x05);
#endif
    INTENSITY_ctrl_init();

    GPIO_setdir_output(PUSH_PULL, PIN_OUT1 | PIN_OUT2 | PIN_OUT3 | PIN_OUT4);
    OUTPUT_openleak();

    GPIO_intr_enable(PIN_POWER_BUTTON, TRIG_BY_FALLING_EDGE, GPIO_callback, App);
    GPIO_intr_enable(PIN_ADD_BUTTON, TRIG_BY_FALLING_EDGE, GPIO_callback, App);
    GPIO_intr_enable(PIN_SUB_BUTTON, TRIG_BY_FALLING_EDGE, GPIO_callback, App);

    // highest priority of TENS control TIMER
    NVIC_SetPriority(TIMER0_IRQn, 0);
}

bool PLATFORM_startup(void)
{
    return true;
}

void PLATFORM_shutdown(void)
{
    OUTPUT_off();
}

void PLATFORM_lowbattery(void)
{
}

void INTENSITY_ctrl_init(void)
{
    PWM_no = PWM_get(FREQ_PWM, PIN_PWM, NULL);
}

void INTENSITY_ctrl_release(uint32_t value)
{
    PWM_release(PWM_no);
    PWM_no = -1;
}

int INTENSITY_ctrl(uint32_t value)
{
    if (-1 == PWM_no)
        return __set_errno_neg(ENODEV);
    if (0 == value)
        return __set_errno_neg(EINVAL);

    if (value > lengthof(INTENSITY_table) - 1)
        value = lengthof(INTENSITY_table) - 1;

    PWM_update(PWM_no, INTENSITY_table[value], INTENSITY_table[0]);
    return value;
}

/***************************************************************************/
/** @INT callback
****************************************************************************/
void GPIO_callback(uint32_t pins, void *arg)
{
    ((TApplication *)arg)->GPIO_callback(gpio, pins);
    /*
    if (PIN_POWER_BUTTON & PINs)
        App->StartDebug();

    if (PIN_ADD_BUTTON & PINs)
        App->AdjustIntensity(10);
    if (PIN_SUB_BUTTON & PINs)
        App->AdjustIntensity(-10);
    */
}
