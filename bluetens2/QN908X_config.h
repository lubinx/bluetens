#ifndef __QN902X_CONFIG_H
#define __QN902X_CONFIG_H               1

///**************************************************************************
// <<< Use Configuration Wizard in Context Menu >>>
//**************************************************************************/
//  <h> Clock Selection
//      <o0> SYS Clock Selection (SYS_CLK_)
//          <i> SYSCON->CLK_CTL [MAIN_CLK_SEL]
///         <0=> RCO 48MHz      (DOC @error?)
//          <1=> XTAL 16/32 MHz
//      <q1> SYS DIV to 16 MHz (this always provide 16MHz SYS clock)
//          <i> SYSCON->XTAL_CTRL [XTAL_DIV]
//          <i> SYSCON->CLK_CTRL  [CLK_OSC32M_DIV]
//      <o2> XTAL Clock Frequency
//          <i> SYSCON->CLK_CTRL [SYS_XTAL_SEL]
//          <0=> 32 MHz
//          <1=> 16 MHz
//      <o3> 32 KHz Clock Source
//          <i> SYSCON->CLK_CTL [SYS_32K_SEL]
//          <0=> XTAL
//          <1=> RCO
//      <o4> BLE Clock Selection
//          <i> SYSCON->CLK_CTL [CLK_BLE_SEL]
//          <i> support 8/16 MHz...but some Phone can't connect to 8 MHz BLE
//          <1=> 16 MHz
//      <o5> WatchDog Clock Selection
//          <i> SYSCON->CLK_CTL [CLK_WDT_SEL]
//          <0=> XTAL/RCO 32 kHz
//          <1=> APB
    #define CLK_SYS_SEL_                (1)
    #define CLK_DIV_TO_16MHZ_           (0)
    #define CLK_XTAL_SEL_               (0)
    #define CLK_32K_SOURCE_             (1)
    #define CLK_BLE_SEL_                (1)
    #define CLK_WDT_SEL_                (0)
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
    #define XTAL_XCUR_BOOST_EN_         (1)
    #define XTAL_BP_XDLY_EN_            (0)
    #define XTAL_BP_HYSRES_EN_          (0)
    #define XTAL_XSMT_EN_               (0)
    #define XTAL_XRDY_EN_               (0)
    #define XTAL_XOUT_DIS_              (0)
    #define XTAL_DIFF_DCLK_DIS_         (1)
    #define XTAL_SU_CB_REG_             (0)
    #define XTAL_SU_CA_REG_             (0)
    #define XTAL_INV_EN_                (0)
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
    #define XTAL32K_ICTRL_              (35)
    #define XTAL32K_INJ_                (0)
    #define XTAL32K_LOAD_CAP_           (48)
    #define XTAL32K_EXTRA_CAP_          (0)
//      </h>
//  </h>
//****************************************************************
//  <h>Pin MUX (GPIO RST)
//      <i> SYSCON->PIO_FUNC_CFG[0~3]
//      <i> SYSCON->PIO_CFG_MISC
//      <o00>PA00 (ADC0/SCT0_OUT0/CTIMER0_CAP0/FC0_RTS/WLAN_TX)
//          <0=>GPIOA0(I/O)
//          <1=>ADC0(AI)
//          <2=>SCT0_OUT0(O)
//          <3=>CTIMER0_CAP0(I)
//          <4=>FC0_RTS(O)
//          <5=>FC2_SSEL3(I/O)
//          <6=>WLAN_TX(I)
//      <o01>PA01 (ADC1/SCT0_OUT1/CTIMER0_CAP1/FC0_CTS/FC2_SSL2/WLAN_RX)
//          <0=>GPIOA1(I/O)
//          <1=>ADC1(AI)
//          <2=>SCT0_OUT1(O)
//          <3=>CTIMER0_CAP1(I)
//          <4=>FC0_CTS(I)
//          <5=>FC2_SSEL2(I/O)
//          <6=>WLAN_RX(I)
//      <o02>PA02 (QDEC0_A/SCT0_OUT2/CTIMER0_MAT0/FC2_SCL_SSEL1)
//          <0=>GPIOA2(I/O)
//          <1=>QDEC0_A(I)
//          <2=>SCT0_OUT2(O)
//          <3=>CTIMER0_MAT0(O)
//          <4=>RESERVED
//          <5=>FC2_SCL_SSEL1(I/O)
//          <6=>RFE_RX_EN(O)
//      <o03>PA03 (QDEC0_B/SCT0_OUT3/CTIMER0_MAT1/FC2_SDA_SSEL0/RFE_TX_EN)
//          <0=>GPIOA3(I/O)
//          <1=>QDEC0_B(I)
//          <2=>SCT0_OUT3(O)
//          <3=>CTIMER0_MAT1(O)
//          <5=>FC2_SDA_SSEL0(I/O)
//          <6=>RFE_TX_EN(O)
//      <o04>PA04 (ADC2/SCT0_OUT4/CTIMER0_MAT0/FC0_TXD/FC2_SDA_MOSI/SPIFI_IO0)
//          <0=>GPIOA4(I/O)
//          <1=>ADC2(AI)
//          <2=>SCT0_OUT4(O)
//          <3=>CTIMER0_MAT0(O)
//          <4=>FC0_TXD(O)
//          <5=>FC2_SDA_MOSI(I/O)
//          <6=>SPIFI_IO0(I/O)
//      <o05>PA05 (ADC3/SCT0_OUT5/CTIMER0_MAT1/FC0_RXD/FC2_SCL_MISO/SPIFI_IO1)
//          <0=>GPIOA5(I/O)
//          <1=>ADC3(AI)
//          <2=>SCT0_OUT5(O)
//          <3=>CTIMER0_MAT1(O)
//          <4=>FC0_RXD(I/O)
//          <5=>FC2_SCL_MISO(I/O)
//          <6=>SPIFI_IO1(I/O)
//      <o06>PA06 (ADC_EX_CAP/SCT0_OUT3/CTIMER0_MAT2/FC1_RTS_SCL/BLE_PTI0/SPIFI_CLK)
//          <0=>GPIOA6(I/O)
//          <1=>RESERVED
//          <2=>SCT0_OUT3(O)
//          <3=>CTIMER0_MAT2(O)
//          <4=>FC1_RTS_SCL(I/O)
//          <5=>BLE_PTI0(O)
//          <6=>SPIFI_CLK(O)
//      <o07>PA07 (ADC_VREFI/SCT0_OUT2/CTIMER1_CAP0/FC1_CTS_SDA/BLE_PTI1/SPIFI_CSN)
//          <0=>GPIOA7(I/O)
//          <1=>ADC_VREFI(AI)
//          <2=>SCT0_OUT2(O)
//          <3=>CTIMER1_CAP0(I)
//          <4=>FC1_CTS_SDA(I/O)
//          <5=>BLE_PTI1(O)
//          <6=>SPIFI_CSN(O)
//      <o08>PA08 (ADC4/SCT0_IN0/CTIMER1_CAP1/FC1_TXD_SCL/BLE_PTI2/SPIFI_IO2)
//          <0=>GPIOA8(I/O)
//          <1=>ADC4(AI)
//          <2=>SCT0_IN0(I)
//          <3=>CTIMER1_CAP1(I)
//          <4=>FC1_TXD_SCL(I/O)
//          <5=>BLE_PTI2(O)
//          <6=>SPIFI_IO2(I/O)
//      <o09>PA09 (ADC5/SCT0_IN1/CTIMER1_MAT0/FC1_RXD_SDA/BLE_PTI3/SPIFI_IO3)
//          <0=>GPIOA9(I/O)
//          <1=>ADC5(AI)
//          <2=>SCT0_IN1(I)
//          <3=>CTIMER1_MAT0(O)
//          <4=>FC1_RXD_SDA(I/O)
//          <5=>BLE_PTI3(O)
//          <6=>SPIFI_IO3(I/O)
//      <o10>PA10 (ADC6/SCT0_IN2/CTIMER1_MAT1/FC1_SCK/ACMP0_OUT/BLE_TX)
//          <0=>GPIOA10(I/O)
//          <1=>ADC6(AI)
//          <2=>SCT0_IN2(I)
//          <3=>CTIMER1_MAT1(O)
//          <4=>FC1_SCK(I/O)
//          <5=>ACMP0_OUT(O)
//          <6=>BLE_TX(O)
//      <o11>PA11 (ADC7/SCT0_IN3/CTIMER1_MAT2/FC2_SSEL2/ACMP1_OUT/BLE_RX)
//          <0=>GPIOA11(I/O)
//          <1=>ADC7(AI)
//          <2=>SCT0_IN3(I)
//          <3=>CTIMER1_MAT2(O)
//          <4=>FC2_SSEL2(I/O)
//          <5=>ACMP1_OUT(O)
//          <6=>BLE_RX(O)
//      <o12>PA12 (SCT0_OUT5/ACMP0_OUT/FC1_TXD_SCL/SD_DAC/ANT_SW)
//          <0=>GPIOA12(I/O)
//          <2=>SCT0_OUT5(O)
//          <3=>ACMP0_OUT(O)
//          <4=>FC1_TXD_SCL(I/O)
//          <5=>SD_DAC(O)
//          <6=>ANT_SW(O)
//      <o13>PA13 (SCT0_OUT4/ACMP1_OUT/FC1_RXD_SDA/FC3_SSEL1/RFE_EN)
//          <0=>GPIOA13(I/O) CDK(BLUE LED)
//          <1=>RESERVED
//          <2=>SCT0_OUT4(O)
//          <3=>ACMP1_OUT(O)
//          <4=>FC1_RXD_SDA(I/O)
//          <5=>FC3_SSEL1(I/O)
//          <6=>RFE_EN(O)
//      <o14>PA14 (CS0/ANT_SW/CTIMER2_CAP0/FC0_RTS/FC3_SSEL0/QDEC1_A)
//          <0=>GPIOA14(I/O)
//          <1=>CS0(AI)
//          <2=>ANT_SW(O)
//          <3=>CTIMER2_CAP0(I)
//          <4=>FC0_RTS(O)
//          <5=>FC3_SSEL0(I/O)
//          <6=>QDEC1_A(I)
//      <o15>PA15 (CS1/SCT0_OUT0/CTIMER2_CAP1/FC0_CTS/FC3_SCK/QDEC1_B)
//          <0=>GPIOA15(I/O)
//          <1=>CS1(AI)
//          <2=>SCT0_OUT0(O)
//          <3=>CTIMER2_CAP1(I)
//          <4=>FC0_CTS(I)
//          <5=>FC3_SCK(I/O)
//          <6=>QDEC1_B(I)
//      <o16>PA16 CDK(TXD) (CS2/SCT0_OUT1/CTIMER2_MAT0/FC0_TXD/FC3_MOSI/QDEC0_A)
//          <0=>GPIOA16(I/O)
//          <1=>CS2(AI)
//          <2=>SCT0_OUT1(O)
//          <3=>CTIMER2_MAT0(O)
//          <4=>FC0_TXD(O)
//          <5=>FC3_MOSI(I/O)
//          <6=>QDEC0_A(I)
//      <o17>PA17 CDK(RXD) (CS3/SD_DAC/CTIMER2_MAT1/FC0_RXD/FC3_MISO/QDEC0_B)
//          <0=>GPIOA17(I/O)
//          <1=>CS3(AI)
//          <2=>SD_DAC(O)
//          <3=>CTIMER2_MAT1(O)
//          <4=>FC0_RXD(I/O)
//          <5=>FC3_MISO(I/O)
//          <6=>QDEC0_B(I)
//      <o18>PA18 (CS4/SCT0_OUT3/CTIMER2_MAT2/FC0_SCK/FC3_SSEL2/BLE_SYNC)
//          <0=>GPIOA18(I/O)
//          <1=>CS4(AI)
//          <2=>SCT0_OUT3(O)
//          <3=>CTIMER2_MAT2(O)
//          <4=>FC0_SCK(I/O)
//          <5=>FC3_SSEL2(I/O)
//          <6=>BLE_SYNC(O)
//      <o19>PA19 (CS5/SCT0_OUT2/RFE_EN/FC0_SCK/FC3_SSEL3/BLE_IN_PROC)
//          <0=>GPIOA19(I/O) CDK(BUTTON2)
//          <1=>CS5(AI)
//          <2=>SCT0_OUT2(O)
//          <3=>RFE_EN(O)
//          <4=>FC0_SCK(I/O)
//          <5=>FC3_SSEL3(I/O)
//          <6=>BLE_IN_PROC(O)
//      <o20>PA20 (QDEC1_A/SCT0_OUT1/CTIMER2_MAT0/SWO/FC1_RTS_SCL/SPIFI_CLK)
//          <0=>GPIOA20(I/O)
//          <1=>QDEC1_A(I)
//          <2=>SCT0_OUT1(O)
//          <3=>CTIMER2_MAT0(O)
//          <4=>SWO(I/O)
//          <5=>FC1_RTS_SCL(I/O)
//          <6=>SPIFI_CLK(O)
//      <o21>PA21 (QDEC1_B/SCT0_OUT0/CTIMER2_MAT1/FC2_SSEL3/FC1_CTS_SDA/SPIFI_CSN)
//          <0=>GPIOA21(I/O)
//          <1=>QDEC1_B(I)
//          <2=>SCT0_OUT0(O)
//          <3=>CTIMER2_MAT1(O)
//          <4=>FC2_SSEL3(I/O)
//          <5=>FC1_CTS_SDA(I/O)
//          <6=>SPIFI_CSN(O)
//      <o22>PA22 (SWCLK/GPIOA22/SCT0_IN2/CTIMER3_MAT0/FC2_SDA_SSEL0/FC3_SSEL3/QDEC1_A)
//          <0=>SWCLK(I/O)
//          <1=>GPIOA22(I/O)
//          <2=>SCT0_IN2(I)
//          <3=>CTIMER3_MAT0(O)
//          <4=>FC2_SDA_SSEL0(I/O)
//          <5=>FC3_SSEL3(I/O)
//          <6=>QDEC1_A(I)
//      <o23>PA23 (SWDIO/GPIOA23/SCT0_IN3/CTIMER3_MAT1/FC2_SCL_SSEL1/FC3_SSEL2/QDEC1_B)
//          <0=>SWDIO(I/O)
//          <1=>GPIOA23(I/O)
//          <2=>SCT0_IN3(I)
//          <3=>CTIMER3_MAT1(O)
//          <4=>FC2_SCL_SSEL1(I/O)
//          <5=>FC3_SSEL2(I/O)
//          <6=>QDEC1_B(I)
//      <o24>PA24 (ACMP0N/ETM_TRACEDAT0/CTIMER3_CAP0/RFE_RX_EN/FC3_SSEL1/SPIFI_IO0)
//          <0=>GPIOA24(I/O) CDK(BUTTON1)
//          <1=>ACMP0N/CS6(AI)
//          <2=>ETM_TRACEDAT0(O)
//          <3=>CTIMER3_CAP0(I)
//          <4=>RFE_RX_EN(O)
//          <5=>FC3_SSEL1(I/O)
//          <6=>SPIFI_IO0(I/O)
//      <o25>PA25 (ACMP0P/ETM_TRACEDAT1/CTIMER3_CAP1/RFE_TX_EN/FC3_SSEL0/SPIFI_IO1)
//          <0=>GPIOA25(I/O) CDK(GREEN LED)
//          <1=>ACMP0P/CS7(AI)
//          <2=>ETM_TRACEDAT1(O)
//          <3=>CTIMER3_CAP1(I)
//          <4=>RFE_TX_EN(O)
//          <5=>FC3_SSEL0(I/O)
//          <6=>SPIFI_IO1(I/O)
//      <o26>PA26 (USB_DP/SCT0_IN0/CTIMER1_MAT0/FC2_SDA_MOSI/QDEC0_A/BLE_SYNC)
//          <0=>GPIOA26(I/O)
//          <1=>USB_DP(A)
//          <2=>SCT0_IN0(I)
//          <3=>CTIMER1_MAT0(O)
//          <4=>FC2_SDA_MOSI(I/O)
//          <5=>QDEC0_A(I)
//          <6=>BLE_SYNC(O)
//      <o27>PA27 (USB_DM/SCT0_IN1/CTIMER1_MAT2/FC2_SCL_MISO/QDEC0_B/BLE_IN_PROC)
//          <0=>GPIOA27(I/O)
//          <1=>USB_DM(A)
//          <2=>SCT0_IN1(I)
//          <3=>CTIMER1_MAT2(O)
//          <4=>FC2_SCL_MISO(I/O)
//          <5=>QDEC0_B(I)
//          <6=>BLE_IN_PROC(O)
//      <o28>PA28 (CLK_AHB/ETM_TRACECLK/RTC_CAP/FC1_SCK/SD_DAC/SPIFI_CSN)
//          <0=>GPIOA28(I/O)
//          <1=>CLK_AHB(O)
//          <2=>ETM_TRACECLK(O)
//          <3=>RTC_CAP(I)
//          <4=>FC1_SCK(I/O)
//          <5=>SD_DAC(O)
//          <6=>SPIFI_CSN(O)
//      <o29>PA29 (ACMP1N/ETM_TRACEDAT2/CTIMER3_MAT0/FC2_SCK/FC3_MISO/SPIFI_IO2)
//          <0=>GPIOA29(I/O)
//          <1=>ACMP1N(AI)
//          <2=>ETM_TRACEDAT2(O)
//          <3=>CTIMER3_MAT0(O)
//          <4=>FC2_SCK(I/O)
//          <5=>FC3_MISO(I/O)
//          <6=>SPIFI_IO2(I/O)
//      <o30>PA30 (ACMP1P/ETM_TRACEDAT3/CTIMER3_MAT1/FC2_SCK/FC3_MOSI/SPIFI_IO3)
//          <0=>GPIOA30(I/O)
//          <1=>ACMP1P(AI)
//          <2=>ETM_TRACEDAT3(O)
//          <3=>CTIMER3_MAT1(O)
//          <4=>FC2_SCK(I/O)
//          <5=>FC3_MOSI(I/O)
//          <6=>SPIFI_IO3(I/O)
//      <o31>PA31 (DAC/RTC_CAP/CTIMER3_MAT2/SWO/FC3_SCK/SPIFI_CLK)
//          <0=>GPIOA31(I/O) CDK(RED LED)
//          <1=>DAC(AO)
//          <2=>RTC_CAP(I)
//          <3=>CTIMER3_MAT2(O)
//          <4=>SWO(I/O)
//          <5=>FC3_SCK(I/O)
//          <6=>SPIFI_CLK(O)
//      <o32>PB00 (XTAL32_OUT)
//          <0=>GPIOB0(I/O)
//          <1=>XTAL32_OUT(RST)
//      <o33>PB01 (XTAL32_IN)
//          <0=>GPIOB1(I/O)
//          <1=>XTAL32_IN (RST)
//      <o34>PB02 (ANT_SW)
//          <0=>GPIOB2(I/O)
//          <1=>ANT_SW(O)
    #define PA00_MUX_FUNC               (0)
    #define PA01_MUX_FUNC               (0)
    #define PA02_MUX_FUNC               (0)
    #define PA03_MUX_FUNC               (0)
    #define PA04_MUX_FUNC               (0)
    #define PA05_MUX_FUNC               (1)
    #define PA06_MUX_FUNC               (0)
    #define PA07_MUX_FUNC               (0)
    #define PA08_MUX_FUNC               (0)
    #define PA09_MUX_FUNC               (0)
    #define PA10_MUX_FUNC               (0)
    #define PA11_MUX_FUNC               (0)
    #define PA12_MUX_FUNC               (0)
    #define PA13_MUX_FUNC               (0)
    #define PA14_MUX_FUNC               (0)
    #define PA15_MUX_FUNC               (0)
    #define PA16_MUX_FUNC               (4)
    #define PA17_MUX_FUNC               (4)
    #define PA18_MUX_FUNC               (0)
    #define PA19_MUX_FUNC               (0)
    #define PA20_MUX_FUNC               (0)
    #define PA21_MUX_FUNC               (0)
    #define PA22_MUX_FUNC               (0)
    #define PA23_MUX_FUNC               (0)
    #define PA24_MUX_FUNC               (0)
    #define PA25_MUX_FUNC               (0)
    #define PA26_MUX_FUNC               (0)
    #define PA27_MUX_FUNC               (0)
    #define PA28_MUX_FUNC               (0)
    #define PA29_MUX_FUNC               (0)
    #define PA30_MUX_FUNC               (0)
    #define PA31_MUX_FUNC               (0)
    #define PB00_MUX_FUNC               (0)
    #define PB01_MUX_FUNC               (0)
    #define PB02_MUX_FUNC               (0)
//  </h>
//****************************************************************
//  <h>Pin PAD Pull (Pull-Up RST)
//      <i> SYSCON->PIO_PULL_CFG[0~2]
//      <o00>PA00
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o01>PA01
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o02>PA02
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o03>PA03
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o04>PA04
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o05>PA05
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o06>PA06
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o07>PA07
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o08>PA08
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o08>PA09
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o10>PA10
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o11>PA11
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o12>PA12
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o13>PA13
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o14>PA14
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o15>PA15
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o16>PA16
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o17>PA17
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o18>PA18
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o19>PA19
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o20>PA20
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o21>PA21
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o22>PA22 CDK
//          <0=>High-Z
//          <1=>Pull-Down CDK
//          <2=>Pull-Up
//      <o23>PA23 CDK
//          <0=>High-Z
//          <1=>Pull-Down CDK
//          <2=>Pull-Up
//      <o24>PA24
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o25>PA25
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o26>PA26
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o27>PA27
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o28>PA28
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o29>PA29
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o30>PA30
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o31>PA31
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o32>PB00
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o33>PB01
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
//      <o34>PB02
//          <0=>High-Z
//          <1=>Pull-Down
//          <2=>Pull-Up
    #define PA00_DEF_PAD_PULL           (1)
    #define PA01_DEF_PAD_PULL           (2)
    #define PA02_DEF_PAD_PULL           (2)
    #define PA03_DEF_PAD_PULL           (2)
    #define PA04_DEF_PAD_PULL           (2)
    #define PA05_DEF_PAD_PULL           (0)
    #define PA06_DEF_PAD_PULL           (2)
    #define PA07_DEF_PAD_PULL           (2)
    #define PA08_DEF_PAD_PULL           (2)
    #define PA09_DEF_PAD_PULL           (2)
    #define PA10_DEF_PAD_PULL           (2)
    #define PA11_DEF_PAD_PULL           (2)
    #define PA12_DEF_PAD_PULL           (2)
    #define PA13_DEF_PAD_PULL           (2)
    #define PA14_DEF_PAD_PULL           (2)
    #define PA15_DEF_PAD_PULL           (2)
    #define PA16_DEF_PAD_PULL           (0)
    #define PA17_DEF_PAD_PULL           (0)
    #define PA18_DEF_PAD_PULL           (2)
    #define PA19_DEF_PAD_PULL           (2)
    #define PA20_DEF_PAD_PULL           (2)
    #define PA21_DEF_PAD_PULL           (2)
    #define PA22_DEF_PAD_PULL           (1)
    #define PA23_DEF_PAD_PULL           (1)
    #define PA24_DEF_PAD_PULL           (2)
    #define PA25_DEF_PAD_PULL           (2)
    #define PA26_DEF_PAD_PULL           (2)
    #define PA27_DEF_PAD_PULL           (2)
    #define PA28_DEF_PAD_PULL           (2)
    #define PA29_DEF_PAD_PULL           (2)
    #define PA30_DEF_PAD_PULL           (2)
    #define PA31_DEF_PAD_PULL           (2)
    #define PB00_DEF_PAD_PULL           (2)
    #define PB01_DEF_PAD_PULL           (2)
    #define PB02_DEF_PAD_PULL           (2)
//  </h>
//****************************************************************
//  <h>Pin Driven Strength (Source 0.9mA / Sink 0.5mA RST)
//      <i> SYSCON->PIO_DRV_CFG0[0~2]
//      <o00>PA00
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//      <o01>PA01
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//      <o02>PA02
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//      <o03>PA03
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//      <o04>PA04
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//      <o05>PA05
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//      <o06>PA06 (EXTRA)
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//          <2=>Source 9.4mA / Sink 0.5mA
//          <3=>Source 12.2mA / Sink 2.1mA
//      <o07>PA07
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//      <o08>PA08
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//      <o09>PA09
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//      <o10>PA10
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//      <o11>PA11 (EXTRA)
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//          <2=>Source 9.4mA / Sink 0.5mA
//          <3=>Source 12.2mA / Sink 2.1mA
//      <o12>PA12
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//      <o13>PA13
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//      <o14>PA14
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//      <o15>PA15
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//      <o16>PA16
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//      <o17>PA17
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//      <o18>PA18
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//      <o19>PA19 (EXTRA)
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//          <2=>Source 9.4mA / Sink 0.5mA
//          <3=>Source 12.2mA / Sink 2.1mA
//      <o20>PA20
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//      <o21>PA21
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//      <o22>PA22
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//      <o23>PA23
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//      <o24>PA24
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//      <o25>PA25
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//      <o26>PA26 (EXTRA)
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//          <2=>Source 9.4mA / Sink 0.5mA
//          <3=>Source 12.2mA / Sink 2.1mA
//      <o27>PA27 (EXTRA)
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//          <2=>Source 9.4mA / Sink 0.5mA
//          <3=>Source 12.2mA / Sink 2.1mA
//      <o28>PA28
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//      <o29>PA29
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//      <o30>PA30
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//      <o31>PA31
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//      <o32>PB00
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//      <o33>PB01
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
//      <o34>PB02
//          <0=>Source 0.9mA / Sink 0.5mA
//          <1=>Source 3.7mA / Sink 2.1mA
    #define PA00_DRV_STR_               (1)
    #define PA01_DRV_STR_               (0)
    #define PA02_DRV_STR_               (0)
    #define PA03_DRV_STR_               (0)
    #define PA04_DRV_STR_               (0)
    #define PA05_DRV_STR_               (0)
    #define PA06_DRV_STR_               (0)
    #define PA07_DRV_STR_               (0)
    #define PA08_DRV_STR_               (0)
    #define PA09_DRV_STR_               (0)
    #define PA10_DRV_STR_               (0)
    #define PA11_DRV_STR_               (0)
    #define PA12_DRV_STR_               (0)
    #define PA13_DRV_STR_               (0)
    #define PA14_DRV_STR_               (0)
    #define PA15_DRV_STR_               (0)
    #define PA16_DRV_STR_               (0)
    #define PA17_DRV_STR_               (0)
    #define PA18_DRV_STR_               (0)
    #define PA19_DRV_STR_               (0)
    #define PA20_DRV_STR_               (0)
    #define PA21_DRV_STR_               (0)
    #define PA22_DRV_STR_               (0)
    #define PA23_DRV_STR_               (0)
    #define PA24_DRV_STR_               (0)
    #define PA25_DRV_STR_               (0)
    #define PA26_DRV_STR_               (0)
    #define PA27_DRV_STR_               (0)
    #define PA28_DRV_STR_               (0)
    #define PA29_DRV_STR_               (0)
    #define PA30_DRV_STR_               (0)
    #define PA31_DRV_STR_               (0)
    #define PB00_DRV_STR_               (0)
    #define PB01_DRV_STR_               (0)
    #define PB02_DRV_STR_               (0)
//  </h>
//  <e> Deep Sleep
    #define DEEP_SLEEP_ENABLED          (1)
//      <o0> Wakeup behavior
//          <0=> NVIC_SystemReset()
    #define DEEP_SLEEP_WAKEUP_BEHAVIOR  (1)
//      <e>RTC
    #define DEEP_SLEEP_RTC_WAKEUP_BY_EN (0)
//          <o0> Milliseconds
    #define DEEP_SLEEP_WAKEUP_INTV      (500)
//      </e>
//      <h>Wakeup by GPIO
//          <o00>PA00       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o01>PA01       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o02>PA02       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o03>PA03       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o04>PA04       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o05>PA05       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o06>PA06       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o07>PA07       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o08>PA08       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o08>PA09       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o10>PA10       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o11>PA11       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o12>PA12       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o13>PA13       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o14>PA14       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o15>PA15       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o16>PA16       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o17>PA17       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o18>PA18       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o19>PA19       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o20>PA20       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o21>PA21       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o22>PA22       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o23>PA23       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o24>PA24       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o25>PA25       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o26>PA26       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o27>PA27       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o28>PA28       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o29>PA29       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o30>PA30       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o31>PA31       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o32>PB00       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o33>PB01       <0=>Disabled    <1=>High-level    <2=>Low-level
//          <o34>PB02       <0=>Disabled    <1=>High-level    <2=>Low-level
//      </h>
    #define PA00_WAKEUP_CFG             (0)
    #define PA01_WAKEUP_CFG             (0)
    #define PA02_WAKEUP_CFG             (0)
    #define PA03_WAKEUP_CFG             (0)
    #define PA04_WAKEUP_CFG             (0)
    #define PA05_WAKEUP_CFG             (0)
    #define PA06_WAKEUP_CFG             (0)
    #define PA07_WAKEUP_CFG             (0)
    #define PA08_WAKEUP_CFG             (0)
    #define PA09_WAKEUP_CFG             (0)
    #define PA10_WAKEUP_CFG             (0)
    #define PA11_WAKEUP_CFG             (0)
    #define PA12_WAKEUP_CFG             (0)
    #define PA13_WAKEUP_CFG             (0)
    #define PA14_WAKEUP_CFG             (0)
    #define PA15_WAKEUP_CFG             (0)
    #define PA16_WAKEUP_CFG             (0)
    #define PA17_WAKEUP_CFG             (0)
    #define PA18_WAKEUP_CFG             (0)
    #define PA19_WAKEUP_CFG             (0)
    #define PA20_WAKEUP_CFG             (0)
    #define PA21_WAKEUP_CFG             (0)
    #define PA22_WAKEUP_CFG             (0)
    #define PA23_WAKEUP_CFG             (0)
    #define PA24_WAKEUP_CFG             (0)
    #define PA25_WAKEUP_CFG             (0)
    #define PA26_WAKEUP_CFG             (0)
    #define PA27_WAKEUP_CFG             (0)
    #define PA28_WAKEUP_CFG             (0)
    #define PA29_WAKEUP_CFG             (0)
    #define PA30_WAKEUP_CFG             (0)
    #define PA31_WAKEUP_CFG             (0)
    #define PB00_WAKEUP_CFG             (0)
    #define PB01_WAKEUP_CFG             (0)
    #define PB02_WAKEUP_CFG             (0)
//  </e>
//  <h> BLE configuration
//      <h> Advertising
//          <o0> Minimum adv interval  * 1.25ms     <10-3200>
//          <o1> Maximum adv interval  * 1.25ms     <10-3200>
    #define BLUETOOTH_ADV_MIN_INTERVAL  (50)
    #define BLUETOOTH_ADV_MAX_INTERVAL  (80)
//      </h>
//      <h> Peripheral Preferred Connection Parameters
//          <o0> Minimum connection interval *1.25ms
//          <o1> Maximum connection interval *1.25ms
//          <o2> Slave latency
//          <o3> Connection Supervision Timeout
    #define GAP_PPCP_CONN_INTV_MIN      (10)
    #define GAP_PPCP_CONN_INTV_MAX      (16)
    #define GAP_PPCP_CONN_LATENCY       (0)
    #define GAP_PPCP_CONN_TIMEOUT       (1600)
//      </h>
//<<< end of configuration section >>>
///**************************************************************************
#endif
