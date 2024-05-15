#ifndef __QN902X_CONFIG_H
#define __QN902X_CONFIG_H               1

//***************************************************************************
//<<< Use Configuration Wizard in Context Menu >>>
//
//  <h> Main Clock Selection
//      <o0> External Oscillator Frequency
//          <32000000=> 32Mhz
//          <16000000=> 16Mhz
//      <o1> 32K Clock Source
//          <0=> External
//          <1=> RCO
//      <o2> Selection: QN_SYSCON->CMDCR[31:30]
//          <0=> External Oscillator (16/32M)
//          <1=> Internal 20M
//          <2=> **failure: PLL XTAL 16M to 32M
//          <3=> **failure: 32K Low Speed/Low Power
//      <q3> Real Time Clock Enable
    #define __XTAL                      (16000000)  // Oscillator frequency
    #define __32K_CLOCK_SOURCE          (1)
    #define CLK_SELECTION               (0)
    #define RTC_ENABLE                  (1)
//  </h>
//  <h> Peripheral Clock Divisor: 0 = By Pass Divisor
//      <o0>AHB Clock Divisor                                   <0-1024:2>
//        <i> Divisor = 0~1024 Step 2
//        <i> Calculate:
//        <i>   AHB Divisor By Pass = QN_SYSCON->CMDCR[25]
//        <i>   APB_DIVIDER = QN_SYSCON->CMDCR[24:16] = 0~511
//        <i>   AHB Clock = Main Clock / (2 *(APB_DIVIDER + 1))
//      <o1> APB Clock Divisor:                                 <0-8:2>
//        <i> Divisor = 0~8 Step 2
//        <i> Calculate:
//        <i>   APB Divisor By Pass = QN_SYSCON->CMDCR[6]
//        <i>   APB_DIVIDER = QN_SYSCON->CMDCR[5:4] = 0~3
//        <i>   APB Clock = AHB Clock / (2 * (APB_DIVIDER + 1))
//      <o2> TIMER Clock Divisor                                <0-16:2>
//        <i> Divisor = 0~16 Step 2
//        <i> Calculate:
//        <i>   TIMER Divisor By Pass = QN_SYSCON->CMDCR[3]
//        <i>   TIMER_DIVIDER = QN_SYSCON->CMDCR[2:0] = 0~7
//        <i>   TIMER Clock = AHB Clock / (2 * (TIMER_DIVIDER + 1))
//      <o3> UART0/SPI0 Clock Divisor                           <0-16:2>
//        <i> Divisor = 0~16 Step 2
//        <i> Calculate:
//        <i>   UART0/SPI0 Divisor By Pass = QN_SYSCON->CMDCR[11]
//        <i>   UART0_SPI0_DIVIDER = QN_SYSCON->CMDCR[10:8] = 0~7
//        <i>   UART0/SPI0 Clock = AHB Clock / (2 * (UART0_SPI0_DIVIDER + 1))
//      <o4> UART1/SPI1 Clock Divisor                           <0-16:2>
//        <i> Divisor = 0~16 Step 2
//        <i> Calculate:
//        <i>   UART1/SPI1 Divisor By Pass = QN_SYSCON->CMDCR[15]
//        <i>   UART1_SPI1_DIVIDER = QN_SYSCON->CMDCR[14:12] = 0~7
//        <i>   UART1/SPI1 Clock = AHB Clock / (2 * (UART1_SPI1_DIVIDER + 1))
//      <o5> BLE Clock (only Support 8/16M): QN_SYSCON->CMDCR[27, 26]
//          <0=>        Disable
//          <8000000=>  8Mhz
//          <16000000=> 16Mhz
    #define AHB_CLK_DIVISOR             (0)
    #define APB_CLK_DIVISOR             (0)
    #define TIMER_CLK_DIVISOR           (0)
    #define UART0_SPI0_CLK_DIVISOR      (0)
    #define UART1_SPI1_CLK_DIVISOR      (0)
    #define BLE_CLK_VAL                 (16000000)
//  </h>
//  <h> Pin Mutex
//      <o00> P00 (GPIO / UART0.TXD /SPI0.Data.Out / RTCI)
//          <0=> GPIO0.0    <1=> UART0.TXD  <2=> SPI0.Data.Out    <3=> RTCI
//      <o01> P01 (GPIO / SPI0.CS0 / UART0.CTS)
//          <0=> GPIO0.1    <2=> SPI0.CS0   <3=> UART0.CTS
//      <o02> P02 (GPIO / I2C.SDA / SPI0.CLK / UART0.RTS)
//          <0=> GPIO0.2    <1=> I2C.SDA    <2=> SPI0.CLK   <3=> UART0.RTS
//      <o03> P03 (GPIO / RADIO.EN / CLKOUT0 / TIMER0.External.CLK)
//          <0=> GPIO0.3    <1=> RADIO.EN   <2=> CLKOUT0<3=> TIMER0.External.CLK
//      <o04> P04 (GPIO / CLKOUT1 / RTCI)
//          <0=> GPIO0.4                    <2=> CLKOUT1    <3=> RTCI
//      <o05> P05 (GPIO / I2C.SCL / ADC Tigger / ACMP1_0)
//          <0=> GPIO0.5    <1=> I2C.SCL    <2=> ADC Tigger <3=> ACMP1_O
//      <o06> P06 (SW.DAT / GPIO / AIN2/ACMP1+)
//          <0=> SW.DAT     <1=> GPIO0.6    <2=> AIN2       <3=> ACMP1+
//      <o07> P07 (SW.CLK / GPIO / AIN3 / ACMP1-)
//          <0=> SW.CLK     <1=> GPIO0.7    <2=> AIN3       <3=> ACMP1-
//      <o08> P10 (GPIO / SPI1.Data.In / UART1 / ACMP1-)
//          <0=> GPIO1.0    <1=> SPI1.Data.In <2=> UART1.RXD <3=> ACMP1-
//      <o09> P11 (GPIO / SPI1.Data.Out / UART1.TXD / TIMER1.ICP0)
//          <0=> GPIO1.1    <1=> SPI1.Data.Out <2=> UART1.TXD <3=> TIMER1.ICP0
//      <o10> P12 (GPIO / SPI1.CS0 / UART1.CTS / ADC Tigger)
//          <0=> GPIO1.2    <1=> SPI1.CS0   <2=> UART1.CTS  <3=> ADC Tigger
//      <o11> P13 (GPIO / SPI1.CLK / UART1.RTS / CLKOUT1)
//          <0=> GPIO1.3    <1=> SPI1.CLK   <2=> UART1.RTS  <3=> CLKOUT1
//      <o12> P14 (GPIO / RDYN / TIMER1.ICP3)
//          <0=> GPIO1.4    <1=> RDYN                       <3=> TIMER1.ICP3
//      <o13> P15 (GPIO / RADIO.EN / PWM1 / TIMER1.ICP2)
//          <0=> GPIO1.5    <1=> RADIO.EN   <2=> PWM1       <3=> TIMER1.ICP2
//      <o14> P16 (GPIO / SPI0.CS1 / PWM0 / TIMER0.ICP3)
//          <0=> GPIO1.6    <1=> SPI0.CS1   <2=> PWM0  <3=> TIMER0.ICP3
//      <o15> P17 (GPIO / UART0.RXD /SPI0.Data.In / TIMER0.OUT)
//          <0=> GPIO1.7    <1=> UART0.RXD  <2=> SPI0.Data.In <3=> TIMER0.OUT
//      <o16> P20 (GPIO / SPI1.Data.In / UART1.RXD / TIMER3.ICP2)
//          <0=> GPIO2.0    <1=> SPI1.Data.In   <2=> UART1.RXD <3=> TIMER3.ICP2
//      <o17> P21 (GPIO / SPI1.Data.Out / UART1.TXD / TIMER3.ICP1)
//          <0=> GPIO2.1    <1=> SPI1.Data.Out  <2=> UART1.TXD    <3=> TIMER3.ICP1
//      <o18> P22 (GPIO / SPI1.CLK / UART1.RTS / TIMER2.ICP3)
//          <0=> GPIO2.2    <1=> SPI1.CLK   <2=> UART1.RTS <3=> TIMER2.ICP3
//      <o19> P23 (GPIO / I2C.SDA / ACMP0_O / TIMER3.ICP0)
//          <0=> GPIO2.3    <1=> I2C.SDA    <2=> ACMP0_O    <3=> TIMER3.ICP0
//      <o20> P24 (GPIO / I2C.SCL / PWM1 / TIMER3.External.CLK)
//          <0=> GPIO2.4    <1=> I2C.SCL    <2=> PWM1       <3=> TIMER3.External.CLK
//      <o21> P25 (GPIO / SPI1.CS1 / TIMER2.ICP2)
//          <0=> GPIO2.5    <1=> SPI1.CS1                   <3=> TIMER2.ICP2
//      <o22> P26 (GPIO / RDYN / PWM1 / TIMER2.ICP0)
//          <0=> GPIO2.6    <1=> RDYN       <2=> PWM1       <3=> TIMER2.ICP0
//      <o23> P27 (GPIO / ACMP1_O / PWM0 / TIMER1.External.CLK)
//          <0=> GPIO2.7    <1=> ACMP1_O    <2=> PWM0       <3=> TIMER1.External.CLK
//      <o24> P30 (GPIO / TIMER2.ICP1 / AIN0 / ACMP0+)
//          <0=> GPIO3.0    <1=> TIMER2.ICP1 <2=> AIN0      <3=> ACMP0+
//      <o25> P31 (GPIO / TIMER0.ICP2 / AIN1 / ACMP0-)
//          <0=> GPIO3.1    <1=> TIMER0.ICP2 <2=> AIN1      <3=> ACMP0-
//      <o26> P32 (GPIO / SPI0.Data.In / ACMP0_O)
//          <0=> GPIO3.2    <1=> SPI0.Data.In               <3=> ACMP0_O
//      <o27> P33 (GPIO / SPI0.Data.Out / CLKOUT0)
//          <0=> GPIO3.3    <1=> SPI0.Data.Out <2=> CLKOUT0
//      <o28> P34 (GPIO / SPI0.CLK)
//          <0=> GPIO3.4    <1=> SPI0.CLK
//      <o29> P35 (GPIO / SPI0.CS0 / INT_FM / TIMER0.ICP0)
//          <0=> GPIO3.5    <1=> SPI0.CS0   <2=> INT_FM     <3=> TIMER0.ICP0
//      <o30> P36 (GPIO / SPI1.CS0 / UART1.CTS)
//          <0=> GPIO3.6    <1=> SPI1.CS0   <2=> UART1.CTS
    #define PIN00_FUNC_SEL              (1)
    #define PIN01_FUNC_SEL              (0)
    #define PIN02_FUNC_SEL              (0)
    #define PIN03_FUNC_SEL              (0)
    #define PIN04_FUNC_SEL              (0)
    #define PIN05_FUNC_SEL              (0)
    #define PIN06_FUNC_SEL              (0)
    #define PIN07_FUNC_SEL              (0)
    #define PIN10_FUNC_SEL              (0)
    #define PIN11_FUNC_SEL              (0)
    #define PIN12_FUNC_SEL              (0)
    #define PIN13_FUNC_SEL              (0)
    #define PIN14_FUNC_SEL              (0)
    #define PIN15_FUNC_SEL              (0)
    #define PIN16_FUNC_SEL              (0)
    #define PIN17_FUNC_SEL              (1)
    #define PIN20_FUNC_SEL              (0)
    #define PIN21_FUNC_SEL              (0)
    #define PIN22_FUNC_SEL              (0)
    #define PIN23_FUNC_SEL              (0)
    #define PIN24_FUNC_SEL              (0)
    #define PIN25_FUNC_SEL              (0)
    #define PIN26_FUNC_SEL              (0)
    #define PIN27_FUNC_SEL              (0)
    #define PIN30_FUNC_SEL              (0)
    #define PIN31_FUNC_SEL              (0)
    #define PIN32_FUNC_SEL              (0)
    #define PIN33_FUNC_SEL              (0)
    #define PIN34_FUNC_SEL              (0)
    #define PIN35_FUNC_SEL              (0)
    #define PIN36_FUNC_SEL              (0)
//  </h>
//  <h> Pin Input Gatting & Output Push-Pull
//      <o00> P00
//          <0=> HIGH-Z     <1=> PULL-DOWN      <2=> PULL-UP
//      <o01> P01
//          <0=> HIGH-Z     <1=> PULL-DOWN      <2=> PULL-UP
//      <o02> P02
//          <0=> HIGH-Z     <1=> PULL-DOWN      <2=> PULL-UP
//      <o03> P03
//          <0=> HIGH-Z     <1=> PULL-DOWN      <2=> PULL-UP
//      <o04> P04
//          <0=> HIGH-Z     <1=> PULL-DOWN      <2=> PULL-UP
//      <o05> P05
//          <0=> HIGH-Z     <1=> PULL-DOWN      <2=> PULL-UP
//      <o06> P06
//          <0=> HIGH-Z     <1=> PULL-DOWN      <2=> PULL-UP
//      <o07> P07
//          <0=> HIGH-Z     <1=> PULL-DOWN      <2=> PULL-UP
//      <o08> P10
//          <0=> HIGH-Z     <1=> PULL-DOWN      <2=> PULL-UP
//      <o09> P11
//          <0=> HIGH-Z     <1=> PULL-DOWN      <2=> PULL-UP
//      <o10> P12
//          <0=> HIGH-Z     <1=> PULL-DOWN      <2=> PULL-UP
//      <o11> P13
//          <0=> HIGH-Z     <1=> PULL-DOWN      <2=> PULL-UP
//      <o12> P14
//          <0=> HIGH-Z     <1=> PULL-DOWN      <2=> PULL-UP
//      <o13> P15
//          <0=> HIGH-Z     <1=> PULL-DOWN      <2=> PULL-UP
//      <o14> P16
//          <0=> HIGH-Z     <1=> PULL-DOWN      <2=> PULL-UP
//      <o15> P17
//          <0=> HIGH-Z     <1=> PULL-DOWN      <2=> PULL-UP
//      <o16> P20
//          <0=> HIGH-Z     <1=> PULL-DOWN      <2=> PULL-UP
//      <o17> P21
//          <0=> HIGH-Z     <1=> PULL-DOWN      <2=> PULL-UP
//      <o18> P22
//          <0=> HIGH-Z     <1=> PULL-DOWN      <2=> PULL-UP
//      <o19> P23
//          <0=> HIGH-Z     <1=> PULL-DOWN      <2=> PULL-UP
//      <o20> P24
//          <0=> HIGH-Z     <1=> PULL-DOWN      <2=> PULL-UP
//      <o21> P25
//          <0=> HIGH-Z     <1=> PULL-DOWN      <2=> PULL-UP
//      <o22> P26
//          <0=> HIGH-Z     <1=> PULL-DOWN      <2=> PULL-UP
//      <o23> P27
//          <0=> HIGH-Z     <1=> PULL-DOWN      <2=> PULL-UP
//      <o24> P30
//          <0=> HIGH-Z     <1=> PULL-DOWN      <2=> PULL-UP
//      <o25> P31
//          <0=> HIGH-Z     <1=> PULL-DOWN      <2=> PULL-UP
//      <o26> P32
//          <0=> HIGH-Z     <1=> PULL-DOWN      <2=> PULL-UP
//      <o27> P33
//          <0=> HIGH-Z     <1=> PULL-DOWN      <2=> PULL-UP
//      <o28> P34
//          <0=> HIGH-Z     <1=> PULL-DOWN      <2=> PULL-UP
//      <o29> P35
//          <0=> HIGH-Z     <1=> PULL-DOWN      <2=> PULL-UP
//      <o30> P36
//          <0=> HIGH-Z     <1=> PULL-DOWN      <2=> PULL-UP
    #define PIN00_PAD_PULL              (2)
    #define PIN01_PAD_PULL              (2)
    #define PIN02_PAD_PULL              (2)
    #define PIN03_PAD_PULL              (2)
    #define PIN04_PAD_PULL              (2)
    #define PIN05_PAD_PULL              (2)
    #define PIN06_PAD_PULL              (1)
    #define PIN07_PAD_PULL              (1)
    #define PIN10_PAD_PULL              (2)
    #define PIN11_PAD_PULL              (2)
    #define PIN12_PAD_PULL              (2)
    #define PIN13_PAD_PULL              (2)
    #define PIN14_PAD_PULL              (2)
    #define PIN15_PAD_PULL              (1)
    #define PIN16_PAD_PULL              (2)
    #define PIN17_PAD_PULL              (2)
    #define PIN20_PAD_PULL              (2)
    #define PIN21_PAD_PULL              (2)
    #define PIN22_PAD_PULL              (2)
    #define PIN23_PAD_PULL              (2)
    #define PIN24_PAD_PULL              (2)
    #define PIN25_PAD_PULL              (2)
    #define PIN26_PAD_PULL              (2)
    #define PIN27_PAD_PULL              (2)
    #define PIN30_PAD_PULL              (2)
    #define PIN31_PAD_PULL              (2)
    #define PIN32_PAD_PULL              (2)
    #define PIN33_PAD_PULL              (2)
    #define PIN34_PAD_PULL              (2)
    #define PIN35_PAD_PULL              (2)
    #define PIN36_PAD_PULL              (2)
//  </h>
//  <h> Pin High Driven
//      <q00> P00
//      <q01> P01
//      <q02> P02
//      <q03> P03
//      <q04> P04
//      <q05> P05
//      <q06> P06
//      <q07> P07
//      <q08> P10
//      <q09> P11
//      <q10> P12
//      <q11> P13
//      <q12> P14
//      <q13> P15
//      <q14> P16
//      <q15> P17
//      <q16> P20
//      <q17> P21
//      <q18> P22
//      <q19> P23
//      <q20> P24
//      <q21> P25
//      <q22> P26
//      <q23> P27
//      <q24> P30
//      <q25> P31
//      <q26> P32
//      <q27> P33
//      <q28> P34
//      <q29> P35
//      <q30> P36
    #define PIN00_HIGH_DRIVEN           (0)
    #define PIN01_HIGH_DRIVEN           (0)
    #define PIN02_HIGH_DRIVEN           (0)
    #define PIN03_HIGH_DRIVEN           (0)
    #define PIN04_HIGH_DRIVEN           (0)
    #define PIN05_HIGH_DRIVEN           (0)
    #define PIN06_HIGH_DRIVEN           (0)
    #define PIN07_HIGH_DRIVEN           (0)
    #define PIN10_HIGH_DRIVEN           (0)
    #define PIN11_HIGH_DRIVEN           (0)
    #define PIN12_HIGH_DRIVEN           (0)
    #define PIN13_HIGH_DRIVEN           (0)
    #define PIN14_HIGH_DRIVEN           (0)
    #define PIN15_HIGH_DRIVEN           (0)
    #define PIN16_HIGH_DRIVEN           (0)
    #define PIN17_HIGH_DRIVEN           (0)
    #define PIN20_HIGH_DRIVEN           (0)
    #define PIN21_HIGH_DRIVEN           (0)
    #define PIN22_HIGH_DRIVEN           (0)
    #define PIN23_HIGH_DRIVEN           (0)
    #define PIN24_HIGH_DRIVEN           (0)
    #define PIN25_HIGH_DRIVEN           (0)
    #define PIN26_HIGH_DRIVEN           (0)
    #define PIN27_HIGH_DRIVEN           (0)
    #define PIN30_HIGH_DRIVEN           (0)
    #define PIN31_HIGH_DRIVEN           (0)
    #define PIN32_HIGH_DRIVEN           (0)
    #define PIN33_HIGH_DRIVEN           (0)
    #define PIN34_HIGH_DRIVEN           (0)
    #define PIN35_HIGH_DRIVEN           (0)
    #define PIN36_HIGH_DRIVEN           (0)
//  </h>
//  <h> BLE Settings
//      <o0> Preallocated BLE Heap Size <0-16384:16>
//      <o1> Advertising Min Interval (MilliSecond)
//      <o2> Advertising Max Interval (MilliSecond)
    #define BLE_HEAP_SIZE               (1024)
    #define BLE_ADV_INTV_MIN            (190)
    #define BLE_ADV_INTV_MAX            (210)
//      <h> Client Preferred Parameters
//      <o0> Min Connection Interval (Val * 1.25ms)
//      <o1> Max Connection Interval (Val * 1.25ms)
//      <o2> Connection Latency
//      <o3> Connection Supervision Timeout (Seconds)
    #define GAP_PRE_CONN_INTV_MIN       (20)
    #define GAP_PRE_CONN_INTV_MAX       (40)
    #define GAP_PRE_CONN_LATENCY        (0)
    #define GAP_PRE_CONN_TIMEOUT        (30 * 10)
//      </h>
//  </h>
//  <h> Deep Sleep Settings
//      <q0> Enabled
//          <i> *Note* Enable BLE Sleep cause some peripheral NOT work: UART / SPI / TIMER
//          <i> it back to normal when BLE stack is active(connected)
//      <o1> Idle Timeout before Enter Deep Sleep in MilliSecond
//      <o2> Wakeup behavior
//          <0=> Restore Only BLE
//          <1=> Restore BLE & Peripherals (UARTs/ADC/SPI etc.)
//          <2=> NVIC_SystemReset()
//      <o3> Wakeup by 32K OSC in MilliSecond if > 0
//      <o4> Wakeup by GPIO 0.0
//          <0=> None
//          <1=> Low Voltage
//          <2=> High Voltage
//      <o5> Wakeup by GPIO 0.1
//          <0=> None
//          <1=> Low Voltage
//          <2=> High Voltage
//      <o6> Wakeup by GPIO 0.2
//          <0=> None
//          <1=> Low Voltage
//          <2=> High Voltage
//      <o7> Wakeup by GPIO 0.3
//          <0=> None
//          <1=> Low Voltage
//          <2=> High Voltage
//      <o8> Wakeup by GPIO 0.4
//          <0=> None
//          <1=> Low Voltage
//          <2=> High Voltage
//      <o9> Wakeup by GPIO 0.5
//          <0=> None
//          <1=> Low Voltage
//          <2=> High Voltage
//      <o10> Wakeup by GPIO 0.6
//          <0=> None
//          <1=> Low Voltage
//          <2=> High Voltage
//      <o11> Wakeup by GPIO 0.7
//          <0=> None
//          <1=> Low Voltage
//          <2=> High Voltage
//      <o12> Wakeup by GPIO 1.0
//          <0=> None
//          <1=> Low Voltage
//          <2=> High Voltage
//      <o13> Wakeup by GPIO 1.1
//          <0=> None
//          <1=> Low Voltage
//          <2=> High Voltage
//      <o14> Wakeup by GPIO 1.2
//          <0=> None
//          <1=> Low Voltage
//          <2=> High Voltage
//      <o15> Wakeup by GPIO 1.3
//          <0=> None
//          <1=> Low Voltage
//          <2=> High Voltage
//      <o16> Wakeup by GPIO 1.4
//          <0=> None
//          <1=> Low Voltage
//          <2=> High Voltage
//      <o17> Wakeup by GPIO 1.5
//          <0=> None
//          <1=> Low Voltage
//          <2=> High Voltage
//      <o18> Wakeup by GPIO 1.6
//          <0=> None
//          <1=> Low Voltage
//          <2=> High Voltage
//      <o19> Wakeup by GPIO 1.7
//          <0=> None
//          <1=> Low Voltage
//          <2=> High Voltage
    #define BLE_DEEP_SLEEP_ENABLED      (1)
    #define BLE_IDLE_TIMEOUT            (20)
    #define BLE_WAKEUP_BEHAVIOR         (2)
    #define BLE_WAKEUP_BY_OSC_MSEC      (0)
    #define BLE_WAKEUP_BY_GPIO_00       (0)
    #define BLE_WAKEUP_BY_GPIO_01       (0)
    #define BLE_WAKEUP_BY_GPIO_02       (0)
    #define BLE_WAKEUP_BY_GPIO_03       (0)
    #define BLE_WAKEUP_BY_GPIO_04       (0)
    #define BLE_WAKEUP_BY_GPIO_05       (0)
    #define BLE_WAKEUP_BY_GPIO_06       (0)
    #define BLE_WAKEUP_BY_GPIO_07       (0)
    #define BLE_WAKEUP_BY_GPIO_10       (0)
    #define BLE_WAKEUP_BY_GPIO_11       (1)
    #define BLE_WAKEUP_BY_GPIO_12       (0)
    #define BLE_WAKEUP_BY_GPIO_13       (0)
    #define BLE_WAKEUP_BY_GPIO_14       (0)
    #define BLE_WAKEUP_BY_GPIO_15       (0)
    #define BLE_WAKEUP_BY_GPIO_16       (0)
    #define BLE_WAKEUP_BY_GPIO_17       (0)
//  </h>
//<<< end of configuration section >>>
//***************************************************************************

#include "syscon.h"

#if CLK_SELECTION == 0
    #define SYS_CLK                     __XTAL
#elif CLK_SELECTION == 1
    #define SYS_CLK                     INAL_20M
#elif CLK_SELECTION == 2
    #define SYS_CLK                     PLL_32M
#elif CLK_SELECTION == 3
    #define SYS_CLK                     INAL_32K
#elif CLK_SELECTION == 4
    #define SYS_CLK                     XTAL_32K
#endif

#if AHB_CLK_DIVISOR == 0
    #define AHB_CLK_Val                 __XTAL
#else
    #define AHB_CLK_Val                 (__XTAL / AHB_CLK_DIVISOR)
#endif

#if APB_CLK_DIVISOR == 0
    #define APB_CLK_Val                 AHB_CLK_Val
#else
    #define APB_CLK_Val                 (AHB_CLK_Val / APB_CLK_DIVISOR)
#endif

#if TIMER_CLK_DIVISOR == 0
    #define TIMER_CLK_Val               AHB_CLK_Val
#else
    #define TIMER_CLK_Val               (AHB_CLK_Val / TIMER_CLK_DIVISOR)
#endif

#if UART0_SPI0_CLK_DIVISOR == 0
    #define UART0_SPI0_CLK_Val          AHB_CLK_Val
#else
    #define UART0_SPI0_CLK_Val          (AHB_CLK_Val / UART0_SPI0_CLK_DIVISOR)
#endif

#if UART1_SPI1_CLK_DIVISOR == 0
    #define UART1_SPI1_CLK_Val          AHB_CLK_Val
#else
    #define UART1_SPI1_CLK_Val          (AHB_CLK_Val / UART1_SPI1_CLK_DIVISOR)
#endif

#endif
