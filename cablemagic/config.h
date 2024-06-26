#ifndef __CONFIG_H
#define __CONFIG_H

#include <features.h>
#include <vinfo.h>
#include <gpio.h>
#include "../common_config.h"

__BEGIN_DECLS

    #define PROJECT_NAME                "cablemagic"
    #define PROJECT_ID                  "clt"
    #define PROJECT_VERSION             VERSION_INFO(2, 1, 1)

    #define CONSOLE_DEV                 QN_UART0

/// @override
    #define NO_SHUTDOWN
    #define NO_CHARGING_DET
    #define NO_BATTERY_DET
    #define SHUTDOWN_IDLE_SECONDS       (0) // disable shutdown

/// @batt
    #define PORT_BATT                   (ADC_NO_PORT)
    #define PIN_BATT                    (ADC_CH_BATT)
    #define BATTERY_ADC_CALIB           (0)

// 按钮
    #define PIN_POWER_BUTTON            P03
    #define PIN_ADD_BUTTON              P30
    #define PIN_SUB_BUTTON              P31

// 电击输出 1~4
    #define PIN_OUT1                    P27
    #define PIN_OUT2                    P10
    #define PIN_OUT3                    P11
    #define PIN_OUT4                    P13
// 输出检测
    #define PIN_HV_PULSE_DET            P12

static inline
    bool DET_is_charging(void)
    {
        return false;
    }

static inline
    void OUTPUT_a(void)
    {
        GPIO_clear(PIN_OUT2 | PIN_OUT3);
        GPIO_set(PIN_OUT1 | PIN_OUT4);
    }

static inline
    void OUTPUT_asy(void)
    {
        // no medic waveform
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
    bool DET_HV_output(void)
    {
        return 0 == GPIO_peek(PIN_HV_PULSE_DET);
    }

__END_DECLS
#endif
