#ifndef __EFR32_PIN_CONFIG_H
#define __EFR32_PIN_CONFIG_H

//**************************************************************************
//<<< Use Configuration Wizard in Context Menu >>>
//--------------------------------------------------------------------------
//  <h> Pin Route
//  <n> ---- PORT A ----
//      <o PA00_ALT_FUNC> PA00 / 21
//          <FUNC_DISABLED=> Disabled
//          <FUNC_USART0_CLK=> USART0.CLK   <FUNC_USART0_CS=>USART0.CS  <FUNC_USART0_CTS=> USART0.CTS   <FUNC_USART0_RTS=> USART0.RTS   <FUNC_USART0_RX=> USART0.RX     <FUNC_USART0_TX=> USART0.TX
//          <FUNC_USART1_CLK=> USART1.CLK   <FUNC_USART1_CS=>USART1.CS  <FUNC_USART1_CTS=> USART1.CTS   <FUNC_USART1_RTS=> USART1.RTS   <FUNC_USART1_RX=> USART1.RX     <FUNC_USART1_TX=> USART1.TX
//          <FUNC_EUART0_CTS=> EUART0.CTS   <FUNC_EUART0_RTS=> EUART0.RTS   <FUNC_EUART0_RX=>EUART0.RX  <FUNC_EUART0_TX=>EUART0.TX
//          <FUNC_I2C0_SCL=> I2C0.SCL       <FUNC_I2C0_SDA=> I2C0.SDA
//          <FUNC_PDM_CLK=> PDM.CLK         <FUNC_PDM_DAT0=> PDM.DAT0   <FUNC_PDM_DAT1=> PDM.DAT1
    #define PA00_ALT_FUNC               (FUNC_GPIO | 0x00)
//
//      <o PA01_ALT_FUNC> PA01 / 22
//          <FUNC_DISABLED=> Disabled
//          <FUNC_PA01_SWCLK=> SW.CLK
//          <FUNC_USART0_CLK=> USART0.CLK   <FUNC_USART0_CS=>USART0.CS  <FUNC_USART0_CTS=> USART0.CTS   <FUNC_USART0_RTS=> USART0.RTS   <FUNC_USART0_RX=> USART0.RX     <FUNC_USART0_TX=> USART0.TX
//          <FUNC_USART1_CLK=> USART1.CLK   <FUNC_USART1_CS=>USART1.CS  <FUNC_USART1_CTS=> USART1.CTS   <FUNC_USART1_RTS=> USART1.RTS   <FUNC_USART1_RX=> USART1.RX     <FUNC_USART1_TX=> USART1.TX
//          <FUNC_EUART0_CTS=> EUART0.CTS   <FUNC_EUART0_RTS=> EUART0.RTS   <FUNC_EUART0_RX=>EUART0.RX  <FUNC_EUART0_TX=>EUART0.TX
//          <FUNC_I2C0_SCL=> I2C0.SCL       <FUNC_I2C0_SDA=> I2C0.SDA
//          <FUNC_PDM_CLK=> PDM.CLK         <FUNC_PDM_DAT0=> PDM.DAT0   <FUNC_PDM_DAT1=> PDM.DAT1
    #define PA01_ALT_FUNC               (FUNC_PA01_SWCLK | 0x01)
//      <o PA02_ALT_FUNC> PA02 / 23
//          <FUNC_DISABLED=> Disabled
//          <FUNC_PA02_SWDIO=> SW.DIO
//          <FUNC_USART0_CLK=> USART0.CLK   <FUNC_USART0_CS=>USART0.CS  <FUNC_USART0_CTS=> USART0.CTS   <FUNC_USART0_RTS=> USART0.RTS   <FUNC_USART0_RX=> USART0.RX     <FUNC_USART0_TX=> USART0.TX
//          <FUNC_USART1_CLK=> USART1.CLK   <FUNC_USART1_CS=>USART1.CS  <FUNC_USART1_CTS=> USART1.CTS   <FUNC_USART1_RTS=> USART1.RTS   <FUNC_USART1_RX=> USART1.RX     <FUNC_USART1_TX=> USART1.TX
//          <FUNC_EUART0_CTS=> EUART0.CTS   <FUNC_EUART0_RTS=> EUART0.RTS   <FUNC_EUART0_RX=>EUART0.RX  <FUNC_EUART0_TX=>EUART0.TX
//          <FUNC_I2C0_SCL=> I2C0.SCL       <FUNC_I2C0_SDA=> I2C0.SDA
//          <FUNC_PDM_CLK=> PDM.CLK         <FUNC_PDM_DAT0=> PDM.DAT0   <FUNC_PDM_DAT1=> PDM.DAT1
    #define PA02_ALT_FUNC               (FUNC_PA02_SWDIO | 0x02)
//
//      <o PA03_ALT_FUNC> PA03 / 24
//          <FUNC_DISABLED=> Disabled
//          <FUNC_PA03_TDO=> TDO            <FUNC_PA03_TRACE_DATA0=> TRACE.DATA0
//          <FUNC_USART0_CLK=> USART0.CLK   <FUNC_USART0_CS=>USART0.CS  <FUNC_USART0_CTS=> USART0.CTS   <FUNC_USART0_RTS=> USART0.RTS   <FUNC_USART0_RX=> USART0.RX     <FUNC_USART0_TX=> USART0.TX
//          <FUNC_USART1_CLK=> USART1.CLK   <FUNC_USART1_CS=>USART1.CS  <FUNC_USART1_CTS=> USART1.CTS   <FUNC_USART1_RTS=> USART1.RTS   <FUNC_USART1_RX=> USART1.RX     <FUNC_USART1_TX=> USART1.TX
//          <FUNC_EUART0_CTS=> EUART0.CTS   <FUNC_EUART0_RTS=> EUART0.RTS   <FUNC_EUART0_RX=>EUART0.RX  <FUNC_EUART0_TX=>EUART0.TX
//          <FUNC_I2C0_SCL=> I2C0.SCL       <FUNC_I2C0_SDA=> I2C0.SDA
//          <FUNC_PDM_CLK=> PDM.CLK         <FUNC_PDM_DAT0=> PDM.DAT0   <FUNC_PDM_DAT1=> PDM.DAT1
    #define PA03_ALT_FUNC               (FUNC_GPIO | 0x03)
//
//      <o PA04_ALT_FUNC> PA04 / 25
//          <FUNC_DISABLED=> Disabled
//          <FUNC_PA04_TDI=> TDI     <FUNC_PA04_TRACE_CLK=> TRACE.CLK
//          <FUNC_USART0_CLK=> USART0.CLK   <FUNC_USART0_CS=>USART0.CS  <FUNC_USART0_CTS=> USART0.CTS   <FUNC_USART0_RTS=> USART0.RTS   <FUNC_USART0_RX=> USART0.RX     <FUNC_USART0_TX=> USART0.TX
//          <FUNC_USART1_CLK=> USART1.CLK   <FUNC_USART1_CS=>USART1.CS  <FUNC_USART1_CTS=> USART1.CTS   <FUNC_USART1_RTS=> USART1.RTS   <FUNC_USART1_RX=> USART1.RX     <FUNC_USART1_TX=> USART1.TX
//          <FUNC_EUART0_CTS=> EUART0.CTS   <FUNC_EUART0_RTS=> EUART0.RTS   <FUNC_EUART0_RX=>EUART0.RX  <FUNC_EUART0_TX=>EUART0.TX
//          <FUNC_I2C0_SCL=> I2C0.SCL       <FUNC_I2C0_SDA=> I2C0.SDA
//          <FUNC_PDM_CLK=> PDM.CLK         <FUNC_PDM_DAT0=> PDM.DAT0   <FUNC_PDM_DAT1=> PDM.DAT1
    #define PA04_ALT_FUNC               (FUNC_GPIO | 0x04)
//
//      <o PA05_ALT_FUNC> PA05 / 26
//          <FUNC_DISABLED=> Disabled
//          <FUNC_USART0_CLK=> USART0.CLK   <FUNC_USART0_CS=>USART0.CS  <FUNC_USART0_CTS=> USART0.CTS   <FUNC_USART0_RTS=> USART0.RTS   <FUNC_USART0_RX=> USART0.RX     <FUNC_USART0_TX=> USART0.TX
//          <FUNC_USART1_CLK=> USART1.CLK   <FUNC_USART1_CS=>USART1.CS  <FUNC_USART1_CTS=> USART1.CTS   <FUNC_USART1_RTS=> USART1.RTS   <FUNC_USART1_RX=> USART1.RX     <FUNC_USART1_TX=> USART1.TX
//          <FUNC_EUART0_CTS=> EUART0.CTS   <FUNC_EUART0_RTS=> EUART0.RTS   <FUNC_EUART0_RX=>EUART0.RX  <FUNC_EUART0_TX=>EUART0.TX
//          <FUNC_I2C0_SCL=> I2C0.SCL       <FUNC_I2C0_SDA=> I2C0.SDA
//          <FUNC_PDM_CLK=> PDM.CLK         <FUNC_PDM_DAT0=> PDM.DAT0   <FUNC_PDM_DAT1=> PDM.DAT1
    #define PA05_ALT_FUNC               (FUNC_DISABLED | 0x05)
//
//      <o PA06_ALT_FUNC> PA06 / 27
//          <FUNC_DISABLED=> Disabled
//          <FUNC_PA05_EM4_WU0=> EM4 Wakeup 0
//          <FUNC_USART0_CLK=> USART0.CLK   <FUNC_USART0_CS=>USART0.CS  <FUNC_USART0_CTS=> USART0.CTS   <FUNC_USART0_RTS=> USART0.RTS   <FUNC_USART0_RX=> USART0.RX     <FUNC_USART0_TX=> USART0.TX
//          <FUNC_USART1_CLK=> USART1.CLK   <FUNC_USART1_CS=>USART1.CS  <FUNC_USART1_CTS=> USART1.CTS   <FUNC_USART1_RTS=> USART1.RTS   <FUNC_USART1_RX=> USART1.RX     <FUNC_USART1_TX=> USART1.TX
//          <FUNC_EUART0_CTS=> EUART0.CTS   <FUNC_EUART0_RTS=> EUART0.RTS   <FUNC_EUART0_RX=>EUART0.RX  <FUNC_EUART0_TX=>EUART0.TX
//          <FUNC_I2C0_SCL=> I2C0.SCL       <FUNC_I2C0_SDA=> I2C0.SDA
//          <FUNC_PDM_CLK=> PDM.CLK         <FUNC_PDM_DAT0=> PDM.DAT0   <FUNC_PDM_DAT1=> PDM.DAT1
    #define PA06_ALT_FUNC               (FUNC_DISABLED | 0x06)
//
//      <o PA07_ALT_FUNC> PA07 / 28
//          <FUNC_DISABLED=> Disabled
//          <FUNC_USART0_CLK=> USART0.CLK   <FUNC_USART0_CS=>USART0.CS  <FUNC_USART0_CTS=> USART0.CTS   <FUNC_USART0_RTS=> USART0.RTS   <FUNC_USART0_RX=> USART0.RX     <FUNC_USART0_TX=> USART0.TX
//          <FUNC_USART1_CLK=> USART1.CLK   <FUNC_USART1_CS=>USART1.CS  <FUNC_USART1_CTS=> USART1.CTS   <FUNC_USART1_RTS=> USART1.RTS   <FUNC_USART1_RX=> USART1.RX     <FUNC_USART1_TX=> USART1.TX
//          <FUNC_EUART0_CTS=> EUART0.CTS   <FUNC_EUART0_RTS=> EUART0.RTS   <FUNC_EUART0_RX=>EUART0.RX  <FUNC_EUART0_TX=>EUART0.TX
//          <FUNC_I2C0_SCL=> I2C0.SCL       <FUNC_I2C0_SDA=> I2C0.SDA
//          <FUNC_PDM_CLK=> PDM.CLK         <FUNC_PDM_DAT0=> PDM.DAT0   <FUNC_PDM_DAT1=> PDM.DAT1
    #define PA07_ALT_FUNC               (FUNC_DISABLED | 0x07)
//
//      <o PA08_ALT_FUNC> PA08 / 29
//          <FUNC_DISABLED=> Disabled
//          <FUNC_USART0_CLK=> USART0.CLK   <FUNC_USART0_CS=>USART0.CS  <FUNC_USART0_CTS=> USART0.CTS   <FUNC_USART0_RTS=> USART0.RTS   <FUNC_USART0_RX=> USART0.RX     <FUNC_USART0_TX=> USART0.TX
//          <FUNC_USART1_CLK=> USART1.CLK   <FUNC_USART1_CS=>USART1.CS  <FUNC_USART1_CTS=> USART1.CTS   <FUNC_USART1_RTS=> USART1.RTS   <FUNC_USART1_RX=> USART1.RX     <FUNC_USART1_TX=> USART1.TX
//          <FUNC_EUART0_CTS=> EUART0.CTS   <FUNC_EUART0_RTS=> EUART0.RTS   <FUNC_EUART0_RX=>EUART0.RX  <FUNC_EUART0_TX=>EUART0.TX
//          <FUNC_I2C0_SCL=> I2C0.SCL       <FUNC_I2C0_SDA=> I2C0.SDA
//          <FUNC_PDM_CLK=> PDM.CLK         <FUNC_PDM_DAT0=> PDM.DAT0   <FUNC_PDM_DAT1=> PDM.DAT1
    #define PA08_ALT_FUNC               (FUNC_DISABLED | 0x08)
//
//  <n> ---- PORT B ----
//      <o PB00_ALT_FUNC> PB00 / 20
//          <FUNC_DISABLED=> Disabled
//          <FUNC_USART0_CLK=> USART0.CLK   <FUNC_USART0_CS=>USART0.CS  <FUNC_USART0_CTS=> USART0.CTS   <FUNC_USART0_RTS=> USART0.RTS   <FUNC_USART0_RX=> USART0.RX     <FUNC_USART0_TX=> USART0.TX
//          <FUNC_USART1_CLK=> USART1.CLK   <FUNC_USART1_CS=>USART1.CS  <FUNC_USART1_CTS=> USART1.CTS   <FUNC_USART1_RTS=> USART1.RTS   <FUNC_USART1_RX=> USART1.RX     <FUNC_USART1_TX=> USART1.TX
//          <FUNC_EUART0_CTS=> EUART0.CTS   <FUNC_EUART0_RTS=> EUART0.RTS   <FUNC_EUART0_RX=>EUART0.RX  <FUNC_EUART0_TX=>EUART0.TX
//          <FUNC_I2C0_SCL=> I2C0.SCL       <FUNC_I2C0_SDA=> I2C0.SDA
//          <FUNC_PDM_CLK=> PDM.CLK         <FUNC_PDM_DAT0=> PDM.DAT0   <FUNC_PDM_DAT1=> PDM.DAT1
    #define PB00_ALT_FUNC               (FUNC_GPIO | 0x10)
//
//      <o PB01_ALT_FUNC> PB01 / 19
//          <FUNC_DISABLED=> Disabled
//          <FUNC_PB01_EM4_WU3=> EM4 Wakeup 3
//          <FUNC_USART0_CLK=> USART0.CLK   <FUNC_USART0_CS=>USART0.CS  <FUNC_USART0_CTS=> USART0.CTS   <FUNC_USART0_RTS=> USART0.RTS   <FUNC_USART0_RX=> USART0.RX     <FUNC_USART0_TX=> USART0.TX
//          <FUNC_USART1_CLK=> USART1.CLK   <FUNC_USART1_CS=>USART1.CS  <FUNC_USART1_CTS=> USART1.CTS   <FUNC_USART1_RTS=> USART1.RTS   <FUNC_USART1_RX=> USART1.RX     <FUNC_USART1_TX=> USART1.TX
//          <FUNC_EUART0_CTS=> EUART0.CTS   <FUNC_EUART0_RTS=> EUART0.RTS   <FUNC_EUART0_RX=>EUART0.RX  <FUNC_EUART0_TX=>EUART0.TX
//          <FUNC_I2C0_SCL=> I2C0.SCL       <FUNC_I2C0_SDA=> I2C0.SDA
//          <FUNC_PDM_CLK=> PDM.CLK         <FUNC_PDM_DAT0=> PDM.DAT0   <FUNC_PDM_DAT1=> PDM.DAT1
    #define PB01_ALT_FUNC               (FUNC_GPIO | 0x11)
//
//      <o PB02_ALT_FUNC> PB02 / 18
//          <FUNC_DISABLED=> Disabled
//          <FUNC_USART0_CLK=> USART0.CLK   <FUNC_USART0_CS=>USART0.CS  <FUNC_USART0_CTS=> USART0.CTS   <FUNC_USART0_RTS=> USART0.RTS   <FUNC_USART0_RX=> USART0.RX     <FUNC_USART0_TX=> USART0.TX
//          <FUNC_USART1_CLK=> USART1.CLK   <FUNC_USART1_CS=>USART1.CS  <FUNC_USART1_CTS=> USART1.CTS   <FUNC_USART1_RTS=> USART1.RTS   <FUNC_USART1_RX=> USART1.RX     <FUNC_USART1_TX=> USART1.TX
//          <FUNC_EUART0_CTS=> EUART0.CTS   <FUNC_EUART0_RTS=> EUART0.RTS   <FUNC_EUART0_RX=>EUART0.RX  <FUNC_EUART0_TX=>EUART0.TX
//          <FUNC_I2C0_SCL=> I2C0.SCL       <FUNC_I2C0_SDA=> I2C0.SDA
//          <FUNC_PDM_CLK=> PDM.CLK         <FUNC_PDM_DAT0=> PDM.DAT0   <FUNC_PDM_DAT1=> PDM.DAT1
    #define PB02_ALT_FUNC               (FUNC_DISABLED | 0x12)
//
//      <o PB03_ALT_FUNC> PB03 / 17
//          <FUNC_DISABLED=> Disabled
//          <FUNC_PB03_EM4_WU4=> EM4 Wakeup 4
//          <FUNC_USART0_CLK=> USART0.CLK   <FUNC_USART0_CS=>USART0.CS  <FUNC_USART0_CTS=> USART0.CTS   <FUNC_USART0_RTS=> USART0.RTS   <FUNC_USART0_RX=> USART0.RX     <FUNC_USART0_TX=> USART0.TX
//          <FUNC_USART1_CLK=> USART1.CLK   <FUNC_USART1_CS=>USART1.CS  <FUNC_USART1_CTS=> USART1.CTS   <FUNC_USART1_RTS=> USART1.RTS   <FUNC_USART1_RX=> USART1.RX     <FUNC_USART1_TX=> USART1.TX
//          <FUNC_EUART0_CTS=> EUART0.CTS   <FUNC_EUART0_RTS=> EUART0.RTS   <FUNC_EUART0_RX=>EUART0.RX  <FUNC_EUART0_TX=>EUART0.TX
//          <FUNC_I2C0_SCL=> I2C0.SCL       <FUNC_I2C0_SDA=> I2C0.SDA
//          <FUNC_PDM_CLK=> PDM.CLK         <FUNC_PDM_DAT0=> PDM.DAT0   <FUNC_PDM_DAT1=> PDM.DAT1
    #define PB03_ALT_FUNC               (FUNC_USART0_TX | 0x13)
//
//      <o PB04_ALT_FUNC> PB04 / 16
//          <FUNC_DISABLED=> Disabled
//          <FUNC_USART0_CLK=> USART0.CLK   <FUNC_USART0_CS=>USART0.CS  <FUNC_USART0_CTS=> USART0.CTS   <FUNC_USART0_RTS=> USART0.RTS   <FUNC_USART0_RX=> USART0.RX     <FUNC_USART0_TX=> USART0.TX
//          <FUNC_USART1_CLK=> USART1.CLK   <FUNC_USART1_CS=>USART1.CS  <FUNC_USART1_CTS=> USART1.CTS   <FUNC_USART1_RTS=> USART1.RTS   <FUNC_USART1_RX=> USART1.RX     <FUNC_USART1_TX=> USART1.TX
//          <FUNC_EUART0_CTS=> EUART0.CTS   <FUNC_EUART0_RTS=> EUART0.RTS   <FUNC_EUART0_RX=>EUART0.RX  <FUNC_EUART0_TX=>EUART0.TX
//          <FUNC_I2C0_SCL=> I2C0.SCL       <FUNC_I2C0_SDA=> I2C0.SDA
//          <FUNC_PDM_CLK=> PDM.CLK         <FUNC_PDM_DAT0=> PDM.DAT0   <FUNC_PDM_DAT1=> PDM.DAT1
    #define PB04_ALT_FUNC               (FUNC_USART0_RX | 0x14)
//
//  <n> ---- PORT C ----
//      <o PC00_ALT_FUNC> PC00 / 01
//          <FUNC_DISABLED=> Disabled
//          <FUNC_PC00_EM4_WU6=> EM4 Wakeup 6    <FUNC_PC00_THMSW_EN=> THMSW_Enable
//          <FUNC_USART0_CLK=> USART0.CLK   <FUNC_USART0_CS=>USART0.CS  <FUNC_USART0_CTS=> USART0.CTS   <FUNC_USART0_RTS=> USART0.RTS   <FUNC_USART0_RX=> USART0.RX     <FUNC_USART0_TX=> USART0.TX
//          <FUNC_EUART0_CTS=> EUART0.CTS   <FUNC_EUART0_RTS=> EUART0.RTS   <FUNC_EUART0_RX=>EUART0.RX  <FUNC_EUART0_TX=>EUART0.TX
//          <FUNC_I2C0_SCL=> I2C0.SCL       <FUNC_I2C0_SDA=> I2C0.SDA   <FUNC_I2C1_SCL=> I2C1.SCL       <FUNC_I2C1_SDA=> I2C1.SDA
//          <FUNC_PDM_CLK=> PDM.CLK         <FUNC_PDM_DAT0=> PDM.DAT0   <FUNC_PDM_DAT1=> PDM.DAT1
    #define PC00_ALT_FUNC               (FUNC_DISABLED | 0x20)
//
//      <o PC01_ALT_FUNC> PC01 / 02
//          <FUNC_DISABLED=> Disabled
//          <FUNC_USART0_CLK=> USART0.CLK   <FUNC_USART0_CS=>USART0.CS  <FUNC_USART0_CTS=> USART0.CTS   <FUNC_USART0_RTS=> USART0.RTS   <FUNC_USART0_RX=> USART0.RX     <FUNC_USART0_TX=> USART0.TX
//          <FUNC_EUART0_CTS=> EUART0.CTS   <FUNC_EUART0_RTS=> EUART0.RTS   <FUNC_EUART0_RX=>EUART0.RX  <FUNC_EUART0_TX=>EUART0.TX
//          <FUNC_I2C0_SCL=> I2C0.SCL       <FUNC_I2C0_SDA=> I2C0.SDA   <FUNC_I2C1_SCL=> I2C1.SCL       <FUNC_I2C1_SDA=> I2C1.SDA
//          <FUNC_PDM_CLK=> PDM.CLK         <FUNC_PDM_DAT0=> PDM.DAT0   <FUNC_PDM_DAT1=> PDM.DAT1
    #define PC01_ALT_FUNC               (FUNC_DISABLED | 0x21)
//
//      <o PC02_ALT_FUNC> PC02 / 03
//          <FUNC_DISABLED=> Disabled
//          <FUNC_USART0_CLK=> USART0.CLK   <FUNC_USART0_CS=>USART0.CS  <FUNC_USART0_CTS=> USART0.CTS   <FUNC_USART0_RTS=> USART0.RTS   <FUNC_USART0_RX=> USART0.RX     <FUNC_USART0_TX=> USART0.TX
//          <FUNC_EUART0_CTS=> EUART0.CTS   <FUNC_EUART0_RTS=> EUART0.RTS   <FUNC_EUART0_RX=>EUART0.RX  <FUNC_EUART0_TX=>EUART0.TX
//          <FUNC_I2C0_SCL=> I2C0.SCL       <FUNC_I2C0_SDA=> I2C0.SDA   <FUNC_I2C1_SCL=> I2C1.SCL       <FUNC_I2C1_SDA=> I2C1.SDA
//          <FUNC_PDM_CLK=> PDM.CLK         <FUNC_PDM_DAT0=> PDM.DAT0   <FUNC_PDM_DAT1=> PDM.DAT1
    #define PC02_ALT_FUNC               (FUNC_DISABLED | 0x22)
//
//      <o PC03_ALT_FUNC> PC03 / 04
//          <FUNC_DISABLED=> Disabled
//          <FUNC_USART0_CLK=> USART0.CLK   <FUNC_USART0_CS=>USART0.CS  <FUNC_USART0_CTS=> USART0.CTS   <FUNC_USART0_RTS=> USART0.RTS   <FUNC_USART0_RX=> USART0.RX     <FUNC_USART0_TX=> USART0.TX
//          <FUNC_EUART0_CTS=> EUART0.CTS   <FUNC_EUART0_RTS=> EUART0.RTS   <FUNC_EUART0_RX=>EUART0.RX  <FUNC_EUART0_TX=>EUART0.TX
//          <FUNC_I2C0_SCL=> I2C0.SCL       <FUNC_I2C0_SDA=> I2C0.SDA   <FUNC_I2C1_SCL=> I2C1.SCL       <FUNC_I2C1_SDA=> I2C1.SDA
//          <FUNC_PDM_CLK=> PDM.CLK         <FUNC_PDM_DAT0=> PDM.DAT0   <FUNC_PDM_DAT1=> PDM.DAT1
    #define PC03_ALT_FUNC               (FUNC_DISABLED | 0x23)
//
//      <o PC04_ALT_FUNC> PC04 / 05
//          <FUNC_DISABLED=> Disabled
//          <FUNC_USART0_CLK=> USART0.CLK   <FUNC_USART0_CS=>USART0.CS  <FUNC_USART0_CTS=> USART0.CTS   <FUNC_USART0_RTS=> USART0.RTS   <FUNC_USART0_RX=> USART0.RX     <FUNC_USART0_TX=> USART0.TX
//          <FUNC_EUART0_CTS=> EUART0.CTS   <FUNC_EUART0_RTS=> EUART0.RTS   <FUNC_EUART0_RX=>EUART0.RX  <FUNC_EUART0_TX=>EUART0.TX
//          <FUNC_I2C0_SCL=> I2C0.SCL       <FUNC_I2C0_SDA=> I2C0.SDA   <FUNC_I2C1_SCL=> I2C1.SCL       <FUNC_I2C1_SDA=> I2C1.SDA
//          <FUNC_PDM_CLK=> PDM.CLK         <FUNC_PDM_DAT0=> PDM.DAT0   <FUNC_PDM_DAT1=> PDM.DAT1
    #define PC04_ALT_FUNC               (FUNC_DISABLED | 0x24)
//
//      <o PC05_ALT_FUNC> PC05 / 06
//          <FUNC_DISABLED=> Disabled
//          <FUNC_PC05_EM4_WU7=> EM4 Wakeup 7
//          <FUNC_USART0_CLK=> USART0.CLK   <FUNC_USART0_CS=>USART0.CS  <FUNC_USART0_CTS=> USART0.CTS   <FUNC_USART0_RTS=> USART0.RTS   <FUNC_USART0_RX=> USART0.RX     <FUNC_USART0_TX=> USART0.TX
//          <FUNC_EUART0_CTS=> EUART0.CTS   <FUNC_EUART0_RTS=> EUART0.RTS   <FUNC_EUART0_RX=>EUART0.RX  <FUNC_EUART0_TX=>EUART0.TX
//          <FUNC_I2C0_SCL=> I2C0.SCL       <FUNC_I2C0_SDA=> I2C0.SDA   <FUNC_I2C1_SCL=> I2C1.SCL       <FUNC_I2C1_SDA=> I2C1.SDA
//          <FUNC_PDM_CLK=> PDM.CLK         <FUNC_PDM_DAT0=> PDM.DAT0   <FUNC_PDM_DAT1=> PDM.DAT1
    #define PC05_ALT_FUNC               (FUNC_DISABLED | 0x25)
//
//      <o PC06_ALT_FUNC> PC06 / 07
//          <FUNC_DISABLED=> Disabled
//          <FUNC_USART0_CLK=> USART0.CLK   <FUNC_USART0_CS=>USART0.CS  <FUNC_USART0_CTS=> USART0.CTS   <FUNC_USART0_RTS=> USART0.RTS   <FUNC_USART0_RX=> USART0.RX     <FUNC_USART0_TX=> USART0.TX
//          <FUNC_EUART0_CTS=> EUART0.CTS   <FUNC_EUART0_RTS=> EUART0.RTS   <FUNC_EUART0_RX=>EUART0.RX  <FUNC_EUART0_TX=>EUART0.TX
//          <FUNC_I2C0_SCL=> I2C0.SCL       <FUNC_I2C0_SDA=> I2C0.SDA   <FUNC_I2C1_SCL=> I2C1.SCL       <FUNC_I2C1_SDA=> I2C1.SDA
//          <FUNC_PDM_CLK=> PDM.CLK         <FUNC_PDM_DAT0=> PDM.DAT0   <FUNC_PDM_DAT1=> PDM.DAT1
    #define PC06_ALT_FUNC               (FUNC_GPIO | 0x26)
//
//      <o PC07_ALT_FUNC> PC07 / 08
//          <FUNC_DISABLED=> Disabled
//          <FUNC_PC07_EM4_WU8=> EM4 Wakeup 8
//          <FUNC_USART0_CLK=> USART0.CLK   <FUNC_USART0_CS=>USART0.CS  <FUNC_USART0_CTS=> USART0.CTS   <FUNC_USART0_RTS=> USART0.RTS   <FUNC_USART0_RX=> USART0.RX     <FUNC_USART0_TX=> USART0.TX
//          <FUNC_EUART0_CTS=> EUART0.CTS   <FUNC_EUART0_RTS=> EUART0.RTS   <FUNC_EUART0_RX=>EUART0.RX  <FUNC_EUART0_TX=>EUART0.TX
//          <FUNC_I2C0_SCL=> I2C0.SCL       <FUNC_I2C0_SDA=> I2C0.SDA   <FUNC_I2C1_SCL=> I2C1.SCL       <FUNC_I2C1_SDA=> I2C1.SDA
//          <FUNC_PDM_CLK=> PDM.CLK         <FUNC_PDM_DAT0=> PDM.DAT0   <FUNC_PDM_DAT1=> PDM.DAT1
    #define PC07_ALT_FUNC               (FUNC_DISABLED | 0x27)
//
//  <n> ---- PORT D ----
//      <o PD00_ALT_FUNC> PD00 / 40
//          <FUNC_DISABLED=> Disabled
//          <FUNC_USART0_CLK=> USART0.CLK   <FUNC_USART0_CS=>USART0.CS  <FUNC_USART0_CTS=> USART0.CTS   <FUNC_USART0_RTS=> USART0.RTS   <FUNC_USART0_RX=> USART0.RX     <FUNC_USART0_TX=> USART0.TX
//          <FUNC_EUART0_CTS=> EUART0.CTS   <FUNC_EUART0_RTS=> EUART0.RTS   <FUNC_EUART0_RX=>EUART0.RX  <FUNC_EUART0_TX=>EUART0.TX
//          <FUNC_I2C0_SCL=> I2C0.SCL       <FUNC_I2C0_SDA=> I2C0.SDA   <FUNC_I2C1_SCL=> I2C1.SCL       <FUNC_I2C1_SDA=> I2C1.SDA
//          <FUNC_PDM_CLK=> PDM.CLK         <FUNC_PDM_DAT0=> PDM.DAT0   <FUNC_PDM_DAT1=> PDM.DAT1
    #define PD00_ALT_FUNC               (FUNC_DISABLED | 0x30)
//
//      <o PD01_ALT_FUNC> PD01 / 39
//          <FUNC_DISABLED=> Disabled
//          <FUNC_USART0_CLK=> USART0.CLK   <FUNC_USART0_CS=>USART0.CS  <FUNC_USART0_CTS=> USART0.CTS   <FUNC_USART0_RTS=> USART0.RTS   <FUNC_USART0_RX=> USART0.RX     <FUNC_USART0_TX=> USART0.TX
//          <FUNC_EUART0_CTS=> EUART0.CTS   <FUNC_EUART0_RTS=> EUART0.RTS   <FUNC_EUART0_RX=>EUART0.RX  <FUNC_EUART0_TX=>EUART0.TX
//          <FUNC_I2C0_SCL=> I2C0.SCL       <FUNC_I2C0_SDA=> I2C0.SDA   <FUNC_I2C1_SCL=> I2C1.SCL       <FUNC_I2C1_SDA=> I2C1.SDA
//          <FUNC_PDM_CLK=> PDM.CLK         <FUNC_PDM_DAT0=> PDM.DAT0   <FUNC_PDM_DAT1=> PDM.DAT1
    #define PD01_ALT_FUNC               (FUNC_DISABLED | 0x31)
//
//      <o PD02_ALT_FUNC> PD02 / 38 (LED1)
//          <FUNC_DISABLED=> Disabled
//          <FUNC_PD02_EM4_WU9=> EM4 Wakeup 7
//          <FUNC_USART0_CLK=> USART0.CLK   <FUNC_USART0_CS=>USART0.CS  <FUNC_USART0_CTS=> USART0.CTS   <FUNC_USART0_RTS=> USART0.RTS   <FUNC_USART0_RX=> USART0.RX     <FUNC_USART0_TX=> USART0.TX
//          <FUNC_EUART0_CTS=> EUART0.CTS   <FUNC_EUART0_RTS=> EUART0.RTS   <FUNC_EUART0_RX=>EUART0.RX  <FUNC_EUART0_TX=>EUART0.TX
//          <FUNC_I2C0_SCL=> I2C0.SCL       <FUNC_I2C0_SDA=> I2C0.SDA   <FUNC_I2C1_SCL=> I2C1.SCL       <FUNC_I2C1_SDA=> I2C1.SDA
//          <FUNC_PDM_CLK=> PDM.CLK         <FUNC_PDM_DAT0=> PDM.DAT0   <FUNC_PDM_DAT1=> PDM.DAT1
    #define PD02_ALT_FUNC               (FUNC_DISABLED | 0x32)
//
//      <o PD03_ALT_FUNC> PD03 / 37 (LED0)
//          <FUNC_DISABLED=> Disabled
//          <FUNC_USART0_CLK=> USART0.CLK   <FUNC_USART0_CS=>USART0.CS  <FUNC_USART0_CTS=> USART0.CTS   <FUNC_USART0_RTS=> USART0.RTS   <FUNC_USART0_RX=> USART0.RX     <FUNC_USART0_TX=> USART0.TX
//          <FUNC_EUART0_CTS=> EUART0.CTS   <FUNC_EUART0_RTS=> EUART0.RTS   <FUNC_EUART0_RX=>EUART0.RX  <FUNC_EUART0_TX=>EUART0.TX
//          <FUNC_I2C0_SCL=> I2C0.SCL       <FUNC_I2C0_SDA=> I2C0.SDA   <FUNC_I2C1_SCL=> I2C1.SCL       <FUNC_I2C1_SDA=> I2C1.SDA
//          <FUNC_PDM_CLK=> PDM.CLK         <FUNC_PDM_DAT0=> PDM.DAT0   <FUNC_PDM_DAT1=> PDM.DAT1
    #define PD03_ALT_FUNC               (FUNC_DISABLED | 0x33)
//  </h>
//
//  <h> Pin Default Gatting
//  <n> ---- PORT A ----
//      <o PA00_GATTING> PA00 / 21
//      <HIGH_Z=> High-Z    <PULL_DOWN=> Pull-Down      <PULL_UP=> Pull-Up
    #define PA00_GATTING                (PULL_UP)
//      <o PA01_GATTING> PA01 / 22
//      <HIGH_Z=> High-Z    <PULL_DOWN=> Pull-Down      <PULL_UP=> Pull-Up
    #define PA01_GATTING                (HIGH_Z)
//      <o PA02_GATTING> PA02 / 23
//      <HIGH_Z=> High-Z    <PULL_DOWN=> Pull-Down      <PULL_UP=> Pull-Up
    #define PA02_GATTING                (HIGH_Z)
//      <o PA03_GATTING> PA03 / 24
//      <HIGH_Z=> High-Z    <PULL_DOWN=> Pull-Down      <PULL_UP=> Pull-Up
    #define PA03_GATTING                (PULL_UP)
//      <o PA04_GATTING> PA04 / 25 (BRD4183A: Disabled + Pull-Up for VCOM)
//      <HIGH_Z=> High-Z    <PULL_DOWN=> Pull-Down      <PULL_UP=> Pull-Up
    #define PA04_GATTING                (PULL_UP)
//      <o PA05_GATTING> PA05 / 26
//      <HIGH_Z=> High-Z    <PULL_DOWN=> Pull-Down      <PULL_UP=> Pull-Up
    #define PA05_GATTING                (PULL_DOWN)
//      <o PA06_GATTING> PA06 / 27
//      <HIGH_Z=> High-Z    <PULL_DOWN=> Pull-Down      <PULL_UP=> Pull-Up
    #define PA06_GATTING                (PULL_UP)
//      <o PA07_GATTING> PA07 / 28
//      <HIGH_Z=> High-Z    <PULL_DOWN=> Pull-Down      <PULL_UP=> Pull-Up
    #define PA07_GATTING                (PULL_UP)
//      <o PA08_GATTING> PA08 / 29
//      <HIGH_Z=> High-Z    <PULL_DOWN=> Pull-Down      <PULL_UP=> Pull-Up
    #define PA08_GATTING                (PULL_UP)
//  <n> ---- PORT B ----
//      <o PB00_GATTING> PB00 / 20
//      <HIGH_Z=> High-Z    <PULL_DOWN=> Pull-Down      <PULL_UP=> Pull-Up
    #define PB00_GATTING                (HIGH_Z)
//      <o PB01_GATTING> PB01 / 19
//      <HIGH_Z=> High-Z    <PULL_DOWN=> Pull-Down      <PULL_UP=> Pull-Up
    #define PB01_GATTING                (HIGH_Z)
//      <o PB02_GATTING> PB02 / 18
//      <HIGH_Z=> High-Z    <PULL_DOWN=> Pull-Down      <PULL_UP=> Pull-Up
    #define PB02_GATTING                (HIGH_Z)
//      <o PB03_GATTING> PB03/ 17
//      <HIGH_Z=> High-Z    <PULL_DOWN=> Pull-Down      <PULL_UP=> Pull-Up
    #define PB03_GATTING                (HIGH_Z)
//      <o PB04_GATTING> PB04/ 16 (BRD4182A: Disabled + Pull-Up for VCOM)
//      <HIGH_Z=> High-Z    <PULL_DOWN=> Pull-Down      <PULL_UP=> Pull-Up
    #define PB04_GATTING                (HIGH_Z)
//  <n> ---- PORT C ----
//      <o PC00_GATTING> PC00 / 01
//      <HIGH_Z=> High-Z    <PULL_DOWN=> Pull-Down      <PULL_UP=> Pull-Up
    #define PC00_GATTING                (HIGH_Z)
//      <o PC01_GATTING> PC01 / 02
//      <HIGH_Z=> High-Z    <PULL_DOWN=> Pull-Down      <PULL_UP=> Pull-Up
    #define PC01_GATTING                (HIGH_Z)
//      <o PC02_GATTING> PC02 / 03
//      <HIGH_Z=> High-Z    <PULL_DOWN=> Pull-Down      <PULL_UP=> Pull-Up
    #define PC02_GATTING                (HIGH_Z)
//      <o PC03_GATTING> PC03 / 04
//      <HIGH_Z=> High-Z    <PULL_DOWN=> Pull-Down      <PULL_UP=> Pull-Up
    #define PC03_GATTING                (HIGH_Z)
//      <o PC04_GATTING> PC04 / 05
//      <HIGH_Z=> High-Z    <PULL_DOWN=> Pull-Down      <PULL_UP=> Pull-Up
    #define PC04_GATTING                (HIGH_Z)
//      <o PC05_GATTING> PC05 / 06
//      <HIGH_Z=> High-Z    <PULL_DOWN=> Pull-Down      <PULL_UP=> Pull-Up
    #define PC05_GATTING                (HIGH_Z)
//      <o PC06_GATTING> PC06 / 07
//      <HIGH_Z=> High-Z    <PULL_DOWN=> Pull-Down      <PULL_UP=> Pull-Up
    #define PC06_GATTING                (PULL_UP)
//      <o PC07_GATTING> PC07 / 08
//      <HIGH_Z=> High-Z    <PULL_DOWN=> Pull-Down      <PULL_UP=> Pull-Up
    #define PC07_GATTING                (HIGH_Z)
//  <n> ---- PORT D ----
//      <o PD00_GATTING> PD00 / 40
//      <HIGH_Z=> High-Z    <PULL_DOWN=> Pull-Down      <PULL_UP=> Pull-Up
    #define PD00_GATTING                (HIGH_Z)
//      <o PD01_GATTING> PD01 / 39
//      <HIGH_Z=> High-Z    <PULL_DOWN=> Pull-Down      <PULL_UP=> Pull-Up
    #define PD01_GATTING                (HIGH_Z)
//      <o PD02_GATTING> PD02 / 38
//      <HIGH_Z=> High-Z    <PULL_DOWN=> Pull-Down      <PULL_UP=> Pull-Up
    #define PD02_GATTING                (HIGH_Z)
//      <o PD03_GATTING> PD03 / 37
//      <HIGH_Z=> High-Z    <PULL_DOWN=> Pull-Down      <PULL_UP=> Pull-Up
    #define PD03_GATTING                (HIGH_Z)
//  </h>

//  <h> GPIO.IN Glitch Suppression Filter
//  <n> ---- PORT A ----
//      <q> PA00 / 21
    #define PA00_GLITCH_FILTER_EN       (0)
//      <q> PA01 / 22
    #define PA01_GLITCH_FILTER_EN       (0)
//      <q> PA02 / 23
    #define PA02_GLITCH_FILTER_EN       (0)
//      <q> PA03 / 24
    #define PA03_GLITCH_FILTER_EN       (0)
//      <q> PA04 / 25
    #define PA04_GLITCH_FILTER_EN       (0)
//      <q> PA05 / 26
    #define PA05_GLITCH_FILTER_EN       (0)
//      <q> PA06 / 27
    #define PA06_GLITCH_FILTER_EN       (0)
//      <q> PA07 / 28
    #define PA07_GLITCH_FILTER_EN       (0)
//      <q> PA08 / 29
    #define PA08_GLITCH_FILTER_EN       (0)
//  <n> ---- PORT B ----
//      <q> PB00 / 20
    #define PB00_GLITCH_FILTER_EN       (0)
//      <q> PB01 / 19
    #define PB01_GLITCH_FILTER_EN       (0)
//      <q> PB02 / 18
    #define PB02_GLITCH_FILTER_EN       (0)
//      <q> PB03/ 17
    #define PB03_GLITCH_FILTER_EN       (0)
//      <q> PB04/ 16
    #define PB04_GLITCH_FILTER_EN       (0)
//  <n> ---- PORT C ----
//      <q> PC00 / 01
    #define PC00_GLITCH_FILTER_EN       (0)
//      <q> PC01 / 02
    #define PC01_GLITCH_FILTER_EN       (0)
//      <q> PC02 / 03
    #define PC02_GLITCH_FILTER_EN       (0)
//      <q> PC03 / 04
    #define PC03_GLITCH_FILTER_EN       (0)
//      <q> PC04 / 05
    #define PC04_GLITCH_FILTER_EN       (0)
//      <q> PC05 / 06
    #define PC05_GLITCH_FILTER_EN       (0)
//      <q> PC06 / 07
    #define PC06_GLITCH_FILTER_EN       (0)
//      <q> PC07 / 08
    #define PC07_GLITCH_FILTER_EN       (0)
//  <n> ---- PORT D ----
//      <q> PD00 / 40
    #define PD00_GLITCH_FILTER_EN       (0)
//      <q> PD01 / 39
    #define PD01_GLITCH_FILTER_EN       (0)
//      <q> PD02 / 38
    #define PD02_GLITCH_FILTER_EN       (0)
//      <q> PD03 / 37
    #define PD03_GLITCH_FILTER_EN       (0)
//  </h>
//--------------------------------------------------------------------------
//<<< end of configuration section >>>
//**************************************************************************

#endif
