#ifndef __QN908X_CONFIG_H
#define __QN908X_CONFIG_H               1

///**************************************************************************
// <<< Use Configuration Wizard in Context Menu >>>
//**************************************************************************/
//  <h> Clock Selection
//      <o0> SYS Clock Selection (SYSCLK_FREQ)
//          <i> SYSCON->CLK_CTL [MAIN_CLK_SEL]
//          <1=> XTAL 16/32 MHz
//      <q1> SYS DIV to 16 MHz (this always provide 16MHz SYS clock)
//          <i> SYSCON->XTAL_CTRL [XTAL_DIV]
//          <i> SYSCON->CLK_CTRL  [CLK_OSC32M_DIV]
//      <o2> XTAL Clock Frequency
//          <i> SYSCON->CLK_CTRL [SYS_XTAL_SEL]
//          <0=> 16 MHz         <1=> 32 MHz
//      <o3> 32 KHz Clock Source
//          <i> SYSCON->CLK_CTL [SYS_32K_SEL]
//          <0=> XTAL           <1=> RCO
//      <o4> BLE Clock Selection
//          <i> SYSCON->CLK_CTL [CLK_BLE_SEL]
//          <i> support 8/16 MHz...but some Phone can't connect to 8 MHz BLE
//          <1=> 16 MHz
//      <o5> WatchDog Clock Selection
//          <i> SYSCON->CLK_CTL [CLK_WDT_SEL]
//          <0=> 32k XTAL/RCO   <1=> APB
    #define CLK_SYS_SEL                 (1)
    #define CLK_DIV_TO_16MHZ            (0)
    #define CLK_XTAL_SEL                (1)
    #define CLK_32K_SEL                 (1)
    #define CLK_BLE_SEL                 (1)
    #define CLK_WDT_SEL                 (0)
//  </h>
//****************************************************************
//  <h> XTAL control
//      <h> 16M / 32M XTAL
//          <i> SYSCON->XTAL_CTRL
//          <q0> Crystal Current Boost Regulator
//              <i> Increase 16/32 MHz Crystal Current
//          <q1> ByPass PowerUp Delay in the Crystal Core
//          <q2> ByPass Degeneration Resistor
//          <q3> Hysteresis Buffer Regulator
//          <q4> XTAL Ready Signal
//          <q5> XTAL Disable Clock Output
//          <q6> Disable Differential Clock of Digital
//          <o7> XTAL_B Load Cap Control        <0-63:1>
//              <i> register controlled load cap of the XTAL_B in speed-up mode
//              <i> CB = 2 pF + 0.35 pF * SU_CB + 5 pF * XADD_C
//          <o8> XTAL_A Load Cap Control        <0-63:1>
//              <i> register controlled load cap of the XTAL_A in speed-up mode
//              <i> CA = 2 pF + 0.35 pF * SU_CA + 5 pF * XADD_C
//          <q9> Inverse XTAL Clock
    #define XTAL_XCUR_BOOST_EN          (1)
    #define XTAL_BP_XDLY_EN             (0)
    #define XTAL_BP_HYSRES_EN           (0)
    #define XTAL_XSMT_EN                (0)
    #define XTAL_XRDY_EN                (0)
    #define XTAL_XOUT_DIS               (0)
    #define XTAL_DIFF_DCLK_DIS          (1)
    #define XTAL_SU_CB_REG              (0)
    #define XTAL_SU_CA_REG              (0)
    #define XTAL_INV_EN                 (0)
//      </h>
//      <h> 32K XTAL
//          <i> SYSCON->XTAL32K_CTRL
//          <o0> XTAL32K_ICTRL          <0-63:1>
//              <i> GM cell current bias Y Default: 0x23
//          <o1> XTAL32K_INJ
//              <i>XTAL 32 kHz clock injection mode Def:on-chip oscillator
//              <0=> OnChip Oscillator
//              <1=> External Digital Clock
//              <2=> External Sine Wave Clock
//          <o2> XTAL32K_LOAD_CAP       <0-63:1>
//              <i> Load CAP Selection
//              <i> XTAL32K Load CAP = 3.6 pF + 0.4 pF * XTAL32K_LOAD_CAP + 6.4pF * XTAL32K_EXTRA_CAP
//          <q3>XTAL32K_EXTRA_CAP
//              <i>add extra XTAL32K load cap or not Def:Not Add
    #define XTAL32K_ICTRL               (35)
    #define XTAL32K_INJ                 (0)
    #define XTAL32K_LOAD_CAP            (48)
    #define XTAL32K_EXTRA_CAP           (0)
//      </h>
//  </h>
//****************************************************************
//  <h>Pin PAD Pull
//      <i> SYSCON->PIO_PULL_CFG[0~2]
//      <o00>PA00           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o01>PA01           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o02>PA02           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o03>PA03           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o04>PA04           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o05>PA05           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o06>PA06           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o07>PA07           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o08>PA08           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o08>PA09           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o10>PA10           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o11>PA11           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o12>PA12           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o13>PA13           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o14>PA14           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o15>PA15           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o16>PA16           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o17>PA17           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o18>PA18           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o19>PA19           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o20>PA20           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o21>PA21           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o22>PA22 CDK SWCLK <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o23>PA23 CDK SWDIO <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o24>PA24           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o25>PA25           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o26>PA26           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o27>PA27           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o28>PA28           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o29>PA29           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o30>PA30           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o31>PA31           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o32>PB00           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o33>PB01           <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
//      <o34>PB02 Boot mode <0=>High-Z  <1=>Pull-Down   <2=>Pull-Up
    #define PA00_DEF_PAD_PULL           (1)
    #define PA01_DEF_PAD_PULL           (0)
    #define PA02_DEF_PAD_PULL           (0)
    #define PA03_DEF_PAD_PULL           (0)
    #define PA04_DEF_PAD_PULL           (0)
    #define PA05_DEF_PAD_PULL           (0)
    #define PA06_DEF_PAD_PULL           (0)
    #define PA07_DEF_PAD_PULL           (0)
    #define PA08_DEF_PAD_PULL           (0)
    #define PA09_DEF_PAD_PULL           (0)
    #define PA10_DEF_PAD_PULL           (0)
    #define PA11_DEF_PAD_PULL           (0)
    #define PA12_DEF_PAD_PULL           (0)
    #define PA13_DEF_PAD_PULL           (0)
    #define PA14_DEF_PAD_PULL           (0)
    #define PA15_DEF_PAD_PULL           (0)
    #define PA16_DEF_PAD_PULL           (0)
    #define PA17_DEF_PAD_PULL           (0)
    #define PA18_DEF_PAD_PULL           (0)
    #define PA19_DEF_PAD_PULL           (0)
    #define PA20_DEF_PAD_PULL           (0)
    #define PA21_DEF_PAD_PULL           (0)
    #define PA22_DEF_PAD_PULL           (1)
    #define PA23_DEF_PAD_PULL           (1)
    #define PA24_DEF_PAD_PULL           (0)
    #define PA25_DEF_PAD_PULL           (0)
    #define PA26_DEF_PAD_PULL           (0)
    #define PA27_DEF_PAD_PULL           (0)
    #define PA28_DEF_PAD_PULL           (0)
    #define PA29_DEF_PAD_PULL           (0)
    #define PA30_DEF_PAD_PULL           (0)
    #define PA31_DEF_PAD_PULL           (0)
    #define PB00_DEF_PAD_PULL           (0)
    #define PB01_DEF_PAD_PULL           (0)
    #define PB02_DEF_PAD_PULL           (0)
//  </h>
//****************************************************************
//  <h>Pin Driven Strength
//      <i> SYSCON->PIO_DRV_CFG0[0~2]
//      <o00>PA00
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//      <o01>PA01
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//      <o02>PA02
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//      <o03>PA03
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//      <o04>PA04
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//      <o05>PA05
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//      <o06>PA06 (EXTRA)
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//          <2=>Source 9.4mA / Sink 0.5mA   <3=>Source 12.2mA / Sink 2.1mA
//      <o07>PA07
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//      <o08>PA08
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//      <o09>PA09
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//      <o10>PA10
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//      <o11>PA11 (EXTRA)
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//          <2=>Source 9.4mA / Sink 0.5mA   <3=>Source 12.2mA / Sink 2.1mA
//      <o12>PA12
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//      <o13>PA13
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//      <o14>PA14
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//      <o15>PA15
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//      <o16>PA16
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//      <o17>PA17
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//      <o18>PA18
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//      <o19>PA19 (EXTRA)
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//          <2=>Source 9.4mA / Sink 0.5mA   <3=>Source 12.2mA / Sink 2.1mA
//      <o20>PA20
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//      <o21>PA21
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//      <o22>PA22
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//      <o23>PA23
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//      <o24>PA24
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//      <o25>PA25
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//      <o26>PA26 (EXTRA)
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//          <2=>Source 9.4mA / Sink 0.5mA   <3=>Source 12.2mA / Sink 2.1mA
//      <o27>PA27 (EXTRA)
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//          <2=>Source 9.4mA / Sink 0.5mA   <3=>Source 12.2mA / Sink 2.1mA
//      <o28>PA28
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//      <o29>PA29
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//      <o30>PA30
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//      <o31>PA31
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//      <o32>PB00
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//      <o33>PB01
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
//      <o34>PB02
//          <0=>Source 0.9mA / Sink 0.5mA   <1=>Source 3.7mA / Sink 2.1mA
    #define PA00_DEF_DRV_STR            (0)
    #define PA01_DEF_DRV_STR            (1)
    #define PA02_DEF_DRV_STR            (1)
    #define PA03_DEF_DRV_STR            (1)
    #define PA04_DEF_DRV_STR            (1)
    #define PA05_DEF_DRV_STR            (1)
    #define PA06_DEF_DRV_STR            (0)
    #define PA07_DEF_DRV_STR            (0)
    #define PA08_DEF_DRV_STR            (0)
    #define PA09_DEF_DRV_STR            (0)
    #define PA10_DEF_DRV_STR            (0)
    #define PA11_DEF_DRV_STR            (0)
    #define PA12_DEF_DRV_STR            (0)
    #define PA13_DEF_DRV_STR            (0)
    #define PA14_DEF_DRV_STR            (0)
    #define PA15_DEF_DRV_STR            (0)
    #define PA16_DEF_DRV_STR            (0)
    #define PA17_DEF_DRV_STR            (0)
    #define PA18_DEF_DRV_STR            (0)
    #define PA19_DEF_DRV_STR            (0)
    #define PA20_DEF_DRV_STR            (0)
    #define PA21_DEF_DRV_STR            (0)
    #define PA22_DEF_DRV_STR            (0)
    #define PA23_DEF_DRV_STR            (0)
    #define PA24_DEF_DRV_STR            (0)
    #define PA25_DEF_DRV_STR            (0)
    #define PA26_DEF_DRV_STR            (0)
    #define PA27_DEF_DRV_STR            (0)
    #define PA28_DEF_DRV_STR            (0)
    #define PA29_DEF_DRV_STR            (0)
    #define PA30_DEF_DRV_STR            (0)
    #define PA31_DEF_DRV_STR            (0)
    #define PB00_DEF_DRV_STR            (0)
    #define PB01_DEF_DRV_STR            (0)
    #define PB02_DEF_DRV_STR            (0)
//  </h>
//****************************************************************
//  <h> Peripheral Configure
//      <h> PMU
//          <q> Deep Sleep
    #define DEEP_SLEEP_ENABLED          (1)
//      </h>
//      <h> BLE configuration
//          <h> Advertising
//              <o0> Minimum adv interval  * 1.25ms     <10-3200>
//              <o1> Maximum adv interval  * 1.25ms     <10-3200>
    #define BLUETOOTH_ADV_MIN_INTERVAL  (120)
    #define BLUETOOTH_ADV_MAX_INTERVAL  (150)
//          </h>
//          <h> Peripheral Preferred Connection Parameters
//              <o0> Minimum connection interval *1.25ms
//              <o1> Maximum connection interval *1.25ms
//              <o2> Slave latency
//              <o3> Connection Supervision Timeout
    #define GAP_PPCP_CONN_INTV_MIN      (10)
    #define GAP_PPCP_CONN_INTV_MAX      (16)
    #define GAP_PPCP_CONN_LATENCY       (0)
    #define GAP_PPCP_CONN_TIMEOUT       (1600)
//          </h>
//      </h>
//  </h>
//<<< end of configuration section >>>
//****************************************************************
#endif
