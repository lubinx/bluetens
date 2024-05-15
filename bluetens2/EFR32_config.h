#ifndef __EFR32_CONFIG_H
#define __EFR32_CONFIG_H

//***************************************************************************
//<<< Use Configuration Wizard in Context Menu >>>
//***************************************************************************
//  <h> CMU Configure
//      <o> SYSCLK / HCLK Selection
//          <1=>FSRCO (no BLE support)
//          <2=>Digital-PLL
//          <3=>HFXO
    #define SYSCLK_SEL                  (2)
//          <n> ---> SYSCLK / HCLK DIV(1 performance) ==> HCLK (CPU)
//          <n> ---> HCLK / PCLK DIV(1/2 calculated) ==> PCLK (Peripherial)
//          <n> ---> PCLK / LSPCLK DIV(2) ==> LSPCLK (Low Speed Peripheral)
//      <o> LF 32768 CLK Source
//          <0=> RC Oscillator (LFRCO)
//          <1=> Crystal Oscillator (LFXO)
    #define LF_32K_SOURCE               (0)
//***************************************************************************
//      <h> CLock Group
//          <o> EM0/1 CLK Group A Selection
//              <1=>Digital-PLL
//              <2=>HFXO
//              <3=>FSRCO
    #define EM01_GRP_A_CLK_SEL          (1)
//          <o> EM0/1 CLK Group B Selection
//              <1=>Digital-PLL
//              <2=>HFXO
//              <3=>FSRCO
    #define EM01_GRP_B_CLK_SEL          (1)
//          <o> EM2/3 CLK Group Selection
//              <0=>LF (LFRCO/LFXO)
//              <3=>ULFRCO
    #define EM23_CLK_SEL                (0)
//          <o> EM4 CLK Group Selection
//              <0=>LF (LFRCO/LFXO)
//              <3=>ULFRCO
    #define EM4_CLK_SEL                 (0)
//      </h>
//***************************************************************************
//      <h> Peripherial Clock Route
//          <o> ADC
//              <1=>EM0/1 CLK Group A
//              <2=>FSRCO (20M internal)
    #define ADC_CLK_SEL                 (1)
//          <o> EUART0
//              <1=>EM0/1 CLK Group A
//              <2=>EM2/3 CLK Group
    #define EUART0_CLK_SEL              (2)
//          <o> WDT
//              <0=>LF (LFRCO/LFXO) CLK
//              <3=>ULFRCO (1000Hz)
//              <4=>HCLK / 1024
    #define WDT_CLK_SEL                 (0)
//  <n>----------------------- FIXED ROUTE ----------------------------------
//          <o> TIMER[n]
//              <1=>EM0/1 CLK Group A
    #define TIMER_CLK_SEL               (1)
//          <o> PDM
//              <1=>EM0/1 CLK Group B
    #define PDM_CLK_SEL                 (1)
//          <o> RTCC
//              <2=>EM2/3 CLK Group
    #define RTCC_CLK_SEL                (2)
//          <o> LETIMER
//              <2=>EM2/3 CLK Group
    #define LETIMER_CLK_SEL             (2)
//      </h>
//***************************************************************************
//  </h>
//
//***************************************************************************
//  <h> Oscillators Configure
//      <h> HXFO
//          <e> External Digital-CLK Mode
    #define HFXO_IS_EXTCLK              (0)
//              <q> Squaring buffer schmitt trigger
    #define HXFO_SQBUFSCHTRGANA         (0)
//              <q> Enable XI Internal DC Bias
    #define HXFO_ENXIDCBIASANA          (0)
//          </e>
//  <n>----------------------- XTALCFG --------------------------------------
//  <i> 9.2.5 HFXO Register Description
//          <o> The core bias LSB change timeout
//          <i> wait duration for the CORE BIAS change to settle out
//              <0=> 8 us
//              <1=> 20 us
//              <2=> 41 us
//              <3=> 62 us
//              <4=> 83 us      (RESET default)
//              <5=> 104 us
//              <6=> 125 us
//              <7=> 166 us
//              <8=> 208 us
//              <9=> 250 us
//              <10=> 333 us
//              <11=> 416 us    (Simplicity IDE default)
//              <12=> 833 us
//              <13=> 1250 us
//              <14=> 2083 us
//              <15=> 3750 us
    #define HFXO_TIMEOUTCBLSB           (11)
//          <o> The steady state timeout
//              <0=> 8 us
//              <1=> 41 us
//              <2=> 83 us      (Simplicity IDE default)
//              <3=> 125 us
//              <4=> 166 us     (RESET default)
//              <5=> 208 us
//              <6=> 250 us
//              <7=> 333 us
//              <8=> 416 us
//              <9=> 500 us
//              <10=> 666 us
//              <11=> 833 us
//              <12=> 1666 us
//              <13=> 2500 us
//              <14=> 4166 us
//              <15=> 7500 us
    #define HFXO_TIMEOUTSTEADY          (2)
//          <o> Startup Tuning Capacitance on XO
    #define HFXO_CTUNEXOSTARTUP         (0)
//          <o> Startup Tuning Capacitance on XI
    #define HFXO_CTUNEXISTARTUP         (0)
//          <o> Startup Core Bias Current
    #define HFXO_COREBIASSTARTUP        (32)
//          <o> Intermediate Startup Core Bias Current
    #define HFXO_COREBIASSTARTUPI       (32)
//  <n>----------------------- XTALCTRL -------------------------------------
//          <o> Core Degeneration
//              <0=> Do not apply core degeneration resistence
//              <1=> Apply 33 ohm core degeneration resistence
//              <2=> Apply 50 ohm core degeneration resistence
//              <3=> Apply 100 ohm core degeneration resistence
    #define HFXO_COREDGENANA            (0)
//          <o> Fixed Tuning Capacitance
//              <0=> Remove fixed capacitance on XI and XO nodes
//              <1=> Adds fixed capacitance on XI node
//              <2=> Adds fixed capacitance on XO node
//              <3=> Adds fixed capacitance on both XI and XO nodes
    #define HFXO_CTUNEFIXANA            (3)
//          <o> Tuning Capacitance on XO (pF)   <0-20400><#/80>
    #define HFXO_CTUNEXOANA             (120)
//          <o> Tuning Capacitance on XI (pF)   <0-20400><#/80>
    #define HFXO_CTUNEXIANA             (120)
//          <o> Core Bias Current (uA)          <1-255><#/10>
    #define HFXO_COREBIASANA            (60)
//      </h>
//***************************************************************************
//      <h> LFXO
//          <o> PPM                 <1-500>
//          <i> this is user provide precision value of LFXO crystal
//          <i> 500ppm is minimum requirement for BLE
    #define LFXO_PRECISION_PPM          (100)
//      </h>
//***************************************************************************
//      <h> Digital-PLL (optional)
//      <i> Digital-PLL is auto enabled if CMU configure to use it
//          <o> Tune Frequency
//              <0 => 32 MHz
//              <1 => 48 MHz
//              <2 => 64 MHz
//              <3 => 80 MHz
    #define DPLL_TUNE_IDX               (3)
//          <o> Operating Mode Control
//              <0=> Frequency Lock
//              <1=> Phase Lock
    #define DPLL_LOCK_MODE              (0)
//          <o> Reference Edge Select
//              <0=> Falling Edge
//              <1=> Raising Edge
    #define DPLL_EDGESEL                (0)
//          <q> Automatic Recovery Control
    #define DPLL_AUTORECOVER            (1)
//          <q> Dither Enable Control
    #define DPLL_DITHEN                 (0)
//      </h>
//  </h>
//***************************************************************************
//  <h> GPIO Port Control
//      <h> PORT A
//          <o.4..6> Slewrate (0~7)
//          <q.12> Disable Data Input
//          <o.20..22> ALT Slewrate (0~7)
//          <q.28> ALT Disable Data Input
    #define GPIOA_CONTROL               (6291552)
//      </h>
//      <h> PORT B
//          <o.4..6> Slewrate (0~7)
//          <q.12> Disable Data Input
//          <o.20..22> ALT Slewrate (0~7)
//          <q.28> ALT Disable Data Input
    #define GPIOB_CONTROL               (6291552)
//      </h>
//      <h> PORT C
//          <o.4..6> Slewrate (0~7)
//          <q.12> Disable Data Input
//          <o.20..22> ALT Slewrate (0~7)
//          <q.28> ALT Disable Data Input
    #define GPIOC_CONTROL               (6291552)
//      </h>
//      <h> PORT D
//          <o.4..6> Slewrate (0~7)
//          <q.12> Disable Data Input
//          <o.20..22> ALT Slewrate (0~7)
//          <q.28> ALT Disable Data Input
    #define GPIOD_CONTROL               (6291552)
//      </h>
//  </h>
//***************************************************************************
//  <h> Peripheral Configure
//      <h> DCDC
//          <q> Bypass
    #define DCDC_BYPASS                 (0)
//          <o> VREGVDD Comparator
//              <0=> 2.0V
//              <1=> 2.1V
//              <2=> 2.1V
//              <3=> 2.3V
    #define DCDC_VREGVDD_CMP            (3)
//          <o> Peak Current Timeout
//              <0 => Off
//              <1 => 0.35us
//              <2 => 0.63us
//              <3 => 0.91us
//              <4 => 1.19us
//              <5 => 1.47us
//              <6 => 1.75us
//              <7 => 2.03us
    #define DCDC_IPEEK_TIMEO            (4)
//          <q> DCM only mode
    #define DCDC_DCM_ONLY               (1)
//          <h> EM 0/1 Control
//              <o.8..9>  Efficiency(Drive Speed)
//                  <0=> Lowest / Best EMI
//                  <1=> Default
//                  <2=> Intermediate
//                  <3=> Best
//              <o.0..3>  EM 0/1 Peak Current
//                  <3=> Peek  90mA / Load 36mA
//                  <4=> Peek 100mA / Load 40mA
//                  <5=> Peek 110mA / Load 44mA
//                  <6=> Peek 120mA / Load 48mA
//                  <7=> Peek 130mA / Load 52mA
//                  <8=> Peek 140mA / Load 56mA
//                  <9=> Peek 150mA / Load 60mA
    #define DCDC_EM01_CTRL              (265)
//          </h>
//          <h> EM 2/3 Control
//              <o.8..9>  Efficiency(Drive Speed)
//                  <0=> Lowest / Best EMI
//                  <1=> Default
//                  <2=> Intermediate
//                  <3=> Best
//              <o.0..3>  EM 0/1 Peak Current
//                  <3=> Peek  90mA / Load  5mA
//                  <9=> Peek 150mA / Load 10mA
    #define DCDC_EM23_CTRL              (771)
//          </h>
//      </h>
//      <h> PMU
//          <q> OS tickless goes EM2
    #define PMU_EM2_EN                  (0)
//      </h>
//      <h> Radio
//          <h> Bluetooth
//              <o0> Minimum advertising interval
//              <o1> Maximum advertising interval
    #define BLUETOOTH_ADV_MIN_INTERVAL  (200)
    #define BLUETOOTH_ADV_MAX_INTERVAL  (300)
//          </h>
//      </h>
//  </h>
//**************************************************************************
//<<< end of configuration section >>>
//**************************************************************************
#endif
