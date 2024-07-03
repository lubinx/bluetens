#ifndef __BLUETENS2_PORTING_H
#define __BLUETENS2_PORTING_H           1

#include <gpio.h>
#include <uart.h>

    #define CONSOLE_DEV                 USART0
    #define CONSOLE_TXD                 PA16
    #define CONSOLE_RXD                 PA17

/// @pinktens
    #define PINKTENS_DET                PA07

/// @BLE
    #define BLE_INCLUDE_HEADER          <nxp.ble.hpp>
    #define BLE_NAMESPACE               NXP

    #define STACK_SIZE_APP              (2048)
    #define STACK_SIZE_UART_SHELL       (2048)
    #define STACK_SIZE_BLE_SHELL        (2048)

/// @buttons
    #define PIN_POWER_BUTTON            PA28
    #define PIN_SUB_BUTTON              PA29
    #define PIN_ADD_BUTTON              PA30

/// @batt
    #define PIN_BATT                    (PA05)
    #define BATT_NUMERATOR              (970)
    #define BATT_DENOMINATOR            (220)
    #define BATTERY_ADC_CALIB           (50)

/// @PWM
    #define PWM_PIN                     PA00
    #define PIN_LDO_POWER               PA06

/// @outputs
    #define PIN_OUT1                    PA04
    #define PIN_OUT2                    PA03
    #define PIN_OUT3                    PA02
    #define PIN_OUT4                    PA01

    #define PIN_HV_CTRL                 PA25
    #define PIN_ASY_CTL                 PA24

/// @leds
    #define PIN_LED1                    PA11
    #define PIN_LED2                    PA10
    #define PIN_LED3                    PA09
    #define PIN_LED4                    PA08

    #define PIN_BLUE_EN                 PA18
    #define PIN_ORANGE_EN               PA19
    #define PIN_WHITE_EN                PA20

/// @misc
    #define PIN_CHARGING_DET            PA12
    #define PIN_HV_PULSE_DET            PA21

#endif
