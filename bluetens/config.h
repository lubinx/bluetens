#ifndef __CONFIG_H
#define __CONFIG_H

#include <features.h>
#include <unistd.h>

#include <vinfo.h>
#include <gpio.h>

#define CPU_QN902X
#include "../common_config.h"

__BEGIN_DECLS

    #define PROJECT_NAME                "BluetensQ.BLT"
    #define PROJECT_ID                  "blt"
    #define PROJECT_VERSION             VERSION_INFO(3, 0, 12)

    #define CONSOLE_DEV                 QN_UART0

/// @override
    #undef NO_PRINT_LABEL
    #undef NO_ADNAME_CHANGE
    #undef NO_SHELL_DUMP

    #define SHUTDOWN_IDLE_SECONDS       (20)

/// @dutch
    #define DUTCH_SHUTDOWN_IDLE_SECONDS (60)
    #define DUTCH_LOAD_DET_TIMEOUT      (10000)

    /// @battery
    #define BATTERY_COMPAT_BLUETENS_V1
    #define BATTERY_ADC_CALIB           (600)
    /// @file io
    #undef FILE_downloading
    #undef FILE_download_complete
    #define FILE_downloading()          GPIO_toggle(PIN_POWER_LED)
    #define FILE_download_complete()    GPIO_clear(PIN_POWER_LED)

/// @buttons
    #define PIN_POWER_BUTTON            P11

/// @batt
    #define PORT_BATT                   (ADC_NO_PORT)
    #define PIN_BATT                    (ADC_CH_BATT)

/// @leds
    #define PIN_POWER_LED               P34
    #define PIN_STR_LED1                P04
    #define PIN_STR_LED2                P05
    #define PIN_STR_LED3                P02
    #define PIN_STR_LED4                P01

/// intensity @dial
    #define PIN_DIAL_EN                 P27
    #define PIN_DIAL_CCW                P26
    #define PIN_DIAL_CW                 P25

/// @output control
    #define PIN_OUT1                    P33
    #define PIN_OUT2                    P32
    #define PIN_OUT3                    P31
    #define PIN_OUT4                    P30

/// @feedbacks
    #define PIN_CHARGING_DET            P35
    #define PIN_HV_PULSE_DET            P14

/** @TUV errata */
    #define TUV_ERRATA_US               (8)

static inline
    void OUTPUT_a(void)
    {
        GPIO_clear(PIN_OUT2 | PIN_OUT3);
        GPIO_set(PIN_OUT1 | PIN_OUT4);
    }

static inline
    void OUTPUT_asy(void)
    {
        GPIO_clear(PIN_OUT1 | PIN_OUT4);
        GPIO_set(PIN_OUT2 | PIN_OUT3);
    }

static inline
    void OUTPUT_b(void)
    {
        GPIO_clear(PIN_OUT1 | PIN_OUT4);
        GPIO_set(PIN_OUT2 | PIN_OUT3);
    }

static inline
    void OUTPUT_openleak(void)
    {
        GPIO_set(PIN_OUT1 | PIN_OUT2 | PIN_OUT3 | PIN_OUT4);
    }

static inline
    void OUTPUT_off(void)
    {
        GPIO_clear(PIN_OUT1 | PIN_OUT2 | PIN_OUT3 | PIN_OUT4);
    }

static inline
    void OUTPUT_release(void)
    {
        OUTPUT_openleak();
        usleep(CAPACITOR_DISCHARGE_US);
        OUTPUT_off();
    }

static inline
    bool DET_is_charging(void)
    {
    #ifdef NO_DET_CHARGING
        return false;
    #else
        return GPIO_peek(PIN_CHARGING_DET) > 0;
    #endif
    }

static inline
    bool DET_HV_output(void)
    {
        return ! GPIO_peek(PIN_HV_PULSE_DET);
    }

__END_DECLS
#endif
