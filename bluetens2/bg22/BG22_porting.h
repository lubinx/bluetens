#ifndef __BLUETENS2_PORTING_H
#define __BLUETENS2_PORTING_H           1

    #define CONSOLE_DEV                 USART0

/// @BLE
    #define BLE_INCLUDE_HEADER          <sl.bluetooth.hpp>
    #define BLE_NAMESPACE               SiLabs

    #define STACK_SIZE_APP              (768)
    #define STACK_SIZE_UART_SHELL       (640)
    #define STACK_SIZE_BLE_SHELL        (640)

/// @pinktens
    #define PINKTENS_DET                PB00

/// @buttons
    #define PIN_POWER_BUTTON            PA04
    #define PIN_SUB_BUTTON              PA00
    #define PIN_ADD_BUTTON              PA03

/// @batt
    #define PIN_BATT                    (PB02)
    #define BATT_NUMERATOR              (970)
    #define BATT_DENOMINATOR            (220)
    #define BATTERY_ADC_CALIB           (0)

/// @PWM
    #define PIN_VOLT_PWM                PC07
    #define PIN_LDO_POWER               PA05

/// @outputs
    #define PIN_OUT1                    PC03
    #define PIN_OUT2                    PC02
    #define PIN_OUT3                    PC01
    #define PIN_OUT4                    PC00

    #define PIN_HV_CTRL                 PC04
    #define PIN_ASY_CTL                 PC05

/// @leds
    #define PIN_LED1                    PD00
    #define PIN_LED2                    PD01
    #define PIN_LED3                    PD02
    #define PIN_LED4                    PD03

    #define PIN_BLUE_EN                 PA06
    #define PIN_WHITE_EN                PA07
    #define PIN_ORANGE_EN               PA08

/// @misc
    #define PIN_CHARGING_DET            PB01
    #define PIN_HV_PULSE_DET            PC06

#endif
