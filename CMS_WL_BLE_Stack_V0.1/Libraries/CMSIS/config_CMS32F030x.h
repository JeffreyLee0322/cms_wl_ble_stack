#ifndef  __CONFIG_CMS32F030X_H__
#define __CONFIG_CMS32F030X_H__

/**************************************************************************//**
 *
 * Copyright (C) 2012 CMS Electronic Co., Ltd. All rights reserved.
 *
 ******************************************************************************/

// Define one bit mask
#define BIT0	              0x00000001
#define BIT1	              0x00000002
#define BIT2	              0x00000004
#define BIT3	              0x00000008
#define BIT4	              0x00000010
#define BIT5	              0x00000020
#define BIT6	              0x00000040
#define BIT7	              0x00000080
#define BIT8	              0x00000100
#define BIT9	              0x00000200
#define BIT10	              0x00000400
#define BIT11	              0x00000800
#define BIT12	              0x00001000
#define BIT13	              0x00002000
#define BIT14	              0x00004000
#define BIT15	              0x00008000
#define BIT16	              0x00010000
#define BIT17	              0x00020000
#define BIT18	              0x00040000
#define BIT19	              0x00080000
#define BIT20	              0x00100000
#define BIT21	              0x00200000
#define BIT22	              0x00400000
#define BIT23	              0x00800000
#define BIT24	              0x01000000
#define BIT25	              0x02000000
#define BIT26	              0x04000000
#define BIT27	              0x08000000
#define BIT28	              0x10000000
#define BIT29	              0x20000000
#define BIT30	              0x40000000
#define BIT31	              0x80000000

#define KEYH                0x5A690000
#define KEY1                0x55AA6699
#define KEY2                0x55AA669A

/*------------- General Purpose Input/Output (GPIO) --------------------------*/
// PxPMS
#define PX7IN               (3<<14)
#define PX7OD               (2<<14)
#define PX7OUT              (1<<14)
#define PX7QB               (0<<14)
#define PX6IN               (3<<12)
#define PX6OD               (2<<12)
#define PX6OUT              (1<<12)
#define PX6QB               (0<<12)
#define PX5IN               (3<<10)
#define PX5OD               (2<<10)
#define PX5OUT              (1<<10)
#define PX5QB               (0<<10)
#define PX4IN               (3<<8)
#define PX4OD               (2<<8)
#define PX4OUT              (1<<8)
#define PX4QB               (0<<8)
#define PX3IN               (3<<6)
#define PX3OD               (2<<6)
#define PX3OUT              (1<<6)
#define PX3QB               (0<<6)
#define PX2IN               (3<<4)
#define PX2OD               (2<<4)
#define PX2OUT              (1<<4)
#define PX2QB               (0<<4)
#define PX1IN               (3<<2)
#define PX1OD               (2<<2)
#define PX1OUT              (1<<2)
#define PX1QB               (0<<2)
#define PX0IN               (3<<0)
#define PX0OD               (2<<0)
#define PX0OUT              (1<<0)
#define PX0QB               (0<<0)

/*------------- Capture/PWM (PWM) Controller ---------------------------------*/
// PWMxCON
#define PWMEN               (1<<6)
#define PWMPS64             (3<<4)
#define PWMPS16             (2<<4)
#define PWMPS4              (1<<4)
#define PWMPS1              (0<<4)
#define PWMSPWM             (1<<3)
#define PWMSCAP             (0<<3)
#define PWMCHB              (1<<2)
#define PWMCHA              (0<<2)
#define PWMCMSF2R           (3<<0)
#define PWMCMSR2F           (2<<0)
#define PWMCMSFE            (1<<0)
#define PWMCMSRE            (0<<0)
// PWMLOADx
#define PWMRELOAD           (1<<16)
// PWMDxA/PWMDxB
#define PWMOPH              (1<<16)
#define PWMOPL              (0<<16)

/*------------- Analog-to-Digital Converter (ADC) ----------------------------*/
// ADCCON
#define ADCEN               (1<<4)
#define ADCMS               (1<<3)
// ADCSCAN
#define ADCST               (1<<8)
#define ADCE7               (1<<7)
#define ADCE6               (1<<6)
#define ADCE5               (1<<5)
#define ADCE4               (1<<4)
#define ADCE3               (1<<3)
#define ADCE2               (1<<2)
#define ADCE1               (1<<1)
#define ADCE0               (1<<0)

/*------------- Universal Asynchronous Receiver Transmitter (UART) -----------*/
// UARTxIER
#define CTSIE               (1<<7)
#define RTSIE               (1<<6)
#define XOFIE               (1<<5)
#define MDSIE               (1<<3)
#define RLSIE               (1<<2)
#define THREIE              (1<<1)
#define RBRIE               (1<<0)
// UARTxFCR
#define RXTL14              (3<<6)
#define RXTL8               (2<<6)
#define RXTL4               (1<<6)
#define RXTL1               (0<<6)
#define TXTL14              (3<<4)
#define TXTL8               (2<<4)
#define TXTL4               (1<<4)
#define TXTL1               (0<<4)
#define TXFIFORST           (1<<2)
#define RXFIFORST           (1<<1)
#define FIFOEN              (1<<0)
// UARTxLCR
#define BCON                (1<<6)
#define PSELF0              (3<<4)
#define PSELF1              (2<<4)
#define PSELEP              (1<<4)
#define PSELOP              (0<<4)
#define PEN                 (1<<3)
#define SBS2                (1<<2)
#define SBS1                (0<<2)
#define WLS8                (3<<0)
#define WLS7                (2<<0)
#define WLS6                (1<<0)
#define WLS5                (0<<0)
// UARTxMCR
#define XOFFS               (1<<7)
#define IREN                (1<<6)
#define MLBM                (1<<4)
#define RTSCON              (1<<1)
#define RTSLOW              (1<<1)
#define RTSHIGH             (0<<1)
// UARTxLSR
#define RXFE                (1<<7)
#define TEMT                (1<<6)
#define THRE                (1<<5)
#define BI                  (1<<4)
#define FE                  (1<<3)
#define PE                  (1<<2)
#define OE                  (1<<1)
#define RDR                 (1<<0)
// UARTxMSR
#define CTS                 (1<<4)
#define DCTS                (1<<0)
// UARTxEFR
#define AUTOCTS             (1<<7)
#define AUTORTS             (1<<6)
#define MEEN                (1<<4)
#define TXSWFC3             (3<<2)
#define TXSWFC2             (2<<2)
#define TXSWFC1             (1<<2)
#define TXSWFC0             (0<<2)
#define RXSWFC3             (3<<0)
#define RXSWFC2             (2<<0)
#define RXSWFC1             (1<<0)
#define RXSWFC0             (0<<0)

/*------------- Timer (TMR) --------------------------------------------------*/
// TMRxCON
#define TMREN               (1<<7)
#define TMRMSP              (1<<6)
#define TMRMSFR             (0<<6)
#define TMRIE               (1<<5)
#define TMRPRE256           (2<<2)
#define TMRPRE16            (1<<2)
#define TMRPRE1             (0<<2)
#define TMRSZ32             (1<<1)
#define TMRSZ16             (0<<1)
#define TMROS               (1<<0)

/*------------- Watchdog Timer (WDT) -----------------------------------------*/
// WDTCON
#define WDTPRE256           (2<<2)
#define WDTPRE16            (1<<2)
#define WDTPRE1             (0<<2)
#define WDTRST              (1<<1)
#define WDTIEN              (1<<0)

/*------------- Inter-Integrated Circuit (I2C) -------------------------------*/
// I2CxCON
#define GCF                 (1<<8)
#define I2CIE               (1<<7)
#define I2CEN               (1<<6)
#define STA                 (1<<5)
#define STO                 (1<<4)
#define SI                  (1<<3)
#define AA                  (1<<2)
#define XADRF               (1<<1)
#define ADRF                (1<<0)

/*------------- Synchronous Serial Communication (SSP) -----------------------*/
// SSPxCON
#define LBM                 (1<<11)
#define SSPEN               (1<<10)
#define SLAVE               (1<<9)
#define MASTER              (0<<9)
#define SOD                 (1<<8)
#define CPHSE               (1<<7)
#define CPHFE               (0<<7)
#define CPOH                (1<<6)
#define CPOL                (0<<6)
#define FRFMICROWIRE        (2<<4)
#define FRFTI               (1<<4)
#define FRFSPI              (0<<4)
#define DSS16               (15<<0)
#define DSS15               (14<<0)
#define DSS14               (13<<0)
#define DSS13               (12<<0)
#define DSS12               (11<<0)
#define DSS11               (10<<0)
#define DSS10               (9<<0)
#define DSS9                (8<<0)
#define DSS8                (7<<0)
#define DSS7                (6<<0)
#define DSS6                (5<<0)
#define DSS5                (4<<0)
#define DSS4                (3<<0)
// SSPxSTAT
#define BSY                 (1<<4)
#define RFF                 (1<<3)
#define RNE                 (1<<2)
#define TNF                 (1<<1)
#define TFE                 (1<<0)
// SSPxIMSC
#define TXIM                (1<<3)
#define RXIM                (1<<2)
#define RTIM                (1<<1)
#define RORIM               (1<<0)
// SSPxRIS
#define TXRIS               (1<<3)
#define RXRIS               (1<<2)
#define RTRIS               (1<<1)
#define RORRIS              (1<<0)
// SSPxMIS
#define TXMIS               (1<<3)
#define RXMIS               (1<<2)
#define RTMIS               (1<<1)
#define RORMIS              (1<<0)
// SSPxICLR
#define RTIC                (1<<1)
#define RORIC               (1<<0)
// SSPxCSCR
#define SPHDC               (1<<4)
#define SWCSH               (1<<3)
#define SWCSL               (0<<3)
#define SWSEL               (1<<2)
#define SS3                 (3<<0)
#define SS2                 (2<<0)
#define SS1                 (1<<0)
#define SS0                 (0<<0)

/*------------- System Control (SYSCON) --------------------------------------*/
// APBCKEN
#define WWDTCE      		(1<<14)
#define EPWMCE      		(1<<13)
#define PWMCE               (1<<12)
#define ADCCE               (1<<11)
#define SSP0CE              (1<<9)
#define I2C0CE              (1<<7)
#define UART2CE             (1<<5)
#define UART1CE             (1<<4)
#define UART0CE             (1<<3)
#define TIMER01CE           (1<<1)
#define WDTCE               (1<<0)
// CLKODIV
#define CLKOEN              (1<<8)
// RSTSTAT
#define CPURS               (1<<2)
#define MCURS               (1<<1)
#define WDTRS               (1<<0)
//CLKCON
#define XOSCEN              (1<<4)
#define IRCEN               (1<<3)
#define IRC1M               (0<<0)
#define IRC2M               (1<<0)
#define IRC4M               (2<<0)
#define IRC8M               (3<<0)
#define IRC12M              (4<<0)
#define IRC16M              (5<<0)
#define IRC20M              (6<<0)
#define IRC22M              (7<<0)
//CLKSEL
#define IRC                 (0<<0)
#define XOSC                (1<<0)
#define IRC10K              (2<<0)
//CLKSTAT
#define XOSCSTB             (1<<1)
#define IRCSTB              (1<<0)
//APBCKSEL
#define TMR01PCLK           (0<<0)
#define TMR01IRC            (1<<0)
#define TMR01XOSC           (2<<0)
#define TMR01IRC10K         (3<<0)
//LVDCFG
#define LVDEN               (1<<4)
#define LVDIMSC             (1<<3)
#define LVDRIS              (1<<2)
#define LVDMIS              (1<<1)
#define LVDICLR             (1<<0)
/*---------------------------------------------------------------------------------------------------------*/
/* Define GPIO                                                                                        */
/*---------------------------------------------------------------------------------------------------------*/
typedef enum
{
  E_P00                 = 0,
  E_P01                 = 1,
  E_P02                 = 2,
  E_P03                 = 3,
  E_P04                 = 4,
  E_P05                 = 5,
  E_P06                 = 6,
  E_P07                 = 7,
  E_P10                 = 8,
  E_P11                 = 9,
  E_P12                 = 10,
  E_P13                 = 11,
  E_P14                 = 12,
  E_P15                 = 13,
  E_P16                 = 14,
  E_P17                 = 15,
  E_P20                 = 16,
  E_P21                 = 17,
  E_P22                 = 18,
  E_P23                 = 19,
  E_P24                 = 20,
  E_P25                 = 21,
  E_P26                 = 22,
  E_P27                 = 23,
  E_P30                 = 24,
  E_P31                 = 25,
  E_P32                 = 26,
  E_P33                 = 27,
  E_P34                 = 28,
  E_P35                 = 29,
  E_P36                 = 30,
  E_P37                 = 31,
  E_P40                 = 32,
  E_P41                 = 33,
  E_P42                 = 34,
  E_P43                 = 35,
  E_P44                 = 36,
  E_P45                 = 37,
  E_P46                 = 38,
  E_P47                 = 39,
}GPIO_Num;


//IOP00CFG
#define P00                 (0<<0)
#define P00XT               (1<<0)
#define P00TXD0             (2<<0)
#define P00CTS0             (3<<0)
#define P00SPI0_CLK         (4<<0)
#define P00PWM0A			(5<<0)
#define P00EPWM2			(6<<0)

//IOP01CFG
#define P01                 (0<<0)
#define P01XT               (1<<0)
#define P01RXD0             (2<<0)
#define P01RTS0             (3<<0)
#define P01SPI0_SS          (4<<0)
#define P01PWM0B			(5<<0)
#define P01EPWM3			(6<<0)

//IOP02CFG
#define P02                 (0<<0)
//IOP03CFG
#define P03                 (0<<0)

//IOP04CFG
#define P04                 (0<<0)
#define P04RXD1             (2<<0)
#define P04CTS1             (3<<0)
#define P04SPI0_SS          (4<<0)
#define P04PWM0A			(5<<0)
#define P04EPWM5			(6<<0)
#define P04SPI0_CLK         (7<<0)

//IOP05CFG
#define P05                 (0<<0)
#define P05TXD1             (2<<0)
#define P05RTS1             (3<<0)
#define P05SPI0_MOSI        (4<<0)
#define P05PWM0B			(5<<0)
#define P05EPWM4			(6<<0)

//IOP06CFG
#define P06                 (0<<0)
#define P06RXD1             (2<<0)
#define P06SDA0             (3<<0)
#define P06SPI0_MISO        (4<<0)
#define P06PWM1A			(5<<0)
#define P06EPWM1			(6<<0)
#define P06CTS1             (7<<0)

//IOP07CFG
#define P07                 (0<<0)
#define P07TXD1             (2<<0)
#define P07SCL0             (3<<0)
#define P07SPI0_CLK         (4<<0)
#define P07PWM1B			(5<<0)
#define P07EPWM0			(6<<0)

//IOP10CFG
#define P10                 (0<<0)
#define P10AN1              (1<<0)
#define P10TXD0             (2<<0)
#define P10PWM0A			(5<<0)
#define P10EPWM1			(6<<0)

//IOP11CFG
#define P11                 (0<<0)

//IOP12CFG
#define P12                 (0<<0)
#define P12AN2              (1<<0)
#define P12RXD0             (2<<0)
#define P12SDA0             (3<<0)
#define P12SPI0_CLK         (4<<0)
#define P12PWM1B			(5<<0)
#define P12EPWM0			(6<<0)
#define P12RTS1             (7<<0)

//IOP13CFG
#define P13                 (0<<0)
#define P13AN3              (1<<0)
#define P13TXD0             (2<<0)
#define P13SCL0             (3<<0)
#define P13SPI0_MISO        (4<<0)
#define P13PWM1A			(5<<0)
#define P13EPWM1			(6<<0)

//IOP14CFG
#define P14                 (0<<0)
#define P14AN4              (1<<0)
#define P14RXD1             (2<<0)
#define P14SDA0             (3<<0)
#define P14SPI0_MOSI        (4<<0)
#define P14PWM0A			(5<<0)
#define P14EPWM4			(6<<0)

//IOP15CFG
#define P15                 (0<<0)
#define P15AN5              (1<<0)
#define P15TXD1             (2<<0)
#define P15SCL0             (3<<0)
#define P15SPI0_SS          (4<<0)
#define P15PWM0A			(5<<0)
#define P15EPWM5			(6<<0)

//IOP16CFG
#define P16                 (0<<0)
#define P16XT               (1<<0)
#define P16RXD0             (2<<0)
#define P16SCL0             (3<<0)
#define P16CTS0             (4<<0)
#define P16PWM0B			(5<<0)
#define P16EPWM2			(6<<0)
#define P16TXD1    			(7<<0)

//IOP17CFG
#define P17                 (0<<0)
#define P17XT               (1<<0)
#define P17TXD0             (2<<0)
#define P17SDA0             (3<<0)
#define P17RTS0             (4<<0)
#define P17PWM1A			(5<<0)
#define P17EPWM4			(6<<0)
#define P17RXD1    			(7<<0)

//IOP20CFG
#define P20                 (0<<0)

//IOP21CFG
#define P21                 (0<<0)
#define P21RXD0             (2<<0)
#define P21SCL0             (3<<0)
#define P21PWM1B			(5<<0)
#define P21EPWM5			(6<<0)
#define P21BKIN    			(7<<0)

//IOP22CFG
#define P22                 (0<<0)
#define P22AN11             (1<<0)
#define P22TXD0             (2<<0)
#define P22SCL0             (3<<0)
#define P22CTS1             (4<<0)
#define P22PWM0A			(5<<0)
#define P22EPWM0			(6<<0)
#define P22SDA0   			(7<<0)

//IOP23CFG
#define P23                 (0<<0)
#define P23TXD1             (2<<0)
#define P23SDA0             (3<<0)
#define P23RTS1             (4<<0)
#define P23PWM0B			(5<<0)
#define P23EPWM1			(6<<0)
#define P23SWDDAT  			(7<<0)

//IOP24CFG
#define P24                 (0<<0)
#define P24RXD1             (2<<0)
#define P24SDA0             (3<<0)
#define P24PWM1A			(5<<0)
#define P24EPWM2			(6<<0)
#define P24SWDCLK  			(7<<0)

//IOP25CFG
#define P25                 (0<<0)
#define P25AN12             (1<<0)
#define P25TXD1             (2<<0)
#define P25SCL0             (3<<0)
#define P25SPI0_SS          (4<<0)
#define P25PWM1B			(5<<0)
#define P25EPWM3			(6<<0)

//IOP26CFG
#define P26                 (0<<0)
#define P26AN13             (1<<0)
#define P26SPI0_CLK         (4<<0)
#define P26PWM0A			(5<<0)
#define P26EPWM4			(6<<0)

//IOP27CFG
#define P27                 (0<<0)

//IOP30CFG
#define P30                 (0<<0)
#define P30AN6              (1<<0)
#define P30RXD0             (2<<0)
#define P30SPI0_CLK         (4<<0)
#define P30PWM0B			(5<<0)
#define P30EPWM0			(6<<0)

//IOP31CFG
#define P31                 (0<<0)
#define P31AN7              (1<<0)
#define P31CTS0             (2<<0)
#define P31SCL0             (3<<0)
#define P31SPI0_MISO        (4<<0)
#define P31PWM1A			(5<<0)
#define P31EPWM4			(6<<0)
#define P31BKIN  			(7<<0)

//IOP32CFG
#define P32                 (0<<0)
#define P32AN8              (1<<0)
#define P32RXD0             (2<<0)
#define P32SDA0             (3<<0)
#define P32SPI0_MOSI        (4<<0)
#define P32PWM1B			(5<<0)
#define P32EPWM1			(6<<0)
#define P32BKIN  			(7<<0)

//IOP33CFG
#define P33                 (0<<0)

//IOP34CFG
#define P34                 (0<<0)
#define P34AN9              (1<<0)
#define P34TXD0             (2<<0)
#define P34SDA0             (3<<0)
#define P34SPI0_CLK         (4<<0)
#define P34PWM0A			(5<<0)
#define P34EPWM3			(6<<0)

//IOP35CFG
#define P35                 (0<<0)
#define P35AN10             (1<<0)
#define P35RTS0             (2<<0)
#define P35SCL0             (3<<0)
#define P35SPI0_SS          (4<<0)
#define P35PWM0B			(5<<0)
#define P35EPWM5			(6<<0)
#define P35CLKO    			(7<<0)

//IOP36CFG
#define P36                 (0<<0)
#define P36PWM1A			(5<<0)
#define P36EPWM0			(6<<0)
#define P36CLKO             (7<<0)

//IOP37CFG
#define P37                 (0<<0)

//IOP40CFG
#define P40                 (0<<0)
//IOP41CFG
#define P41                 (0<<0)
//IOP42CFG
#define P42                 (0<<0)

//IOP43CFG
#define P43                 (0<<0)
#define P43PWM0A			(5<<0)

//IOP44CFG
#define P44                 (0<<0)
#define P44TXD0             (2<<0)
#define P44PWM0B			(5<<0)
#define P44EPWM1			(6<<0)

//IOP45CFG
#define P45                 (0<<0)

//IOP46CFG
#define P46                 (0<<0)
#define P46AN14             (1<<0)
#define P46RXD1             (2<<0)
#define P46SPI0_MISO        (4<<0)
#define P46PWM1A			(5<<0)
#define P46EPWM2			(6<<0)
#define P46SWDCLK  			(7<<0)

//IOP47CFG
#define P47                 (0<<0)
#define P47TXD1             (2<<0)
#define P47RTS1             (3<<0)
#define P47SPI0_MOSI        (4<<0)
#define P47PWM1B			(5<<0)
#define P47EPWM3			(6<<0)
#define P47SWDDAT  			(7<<0)


/*------------- Flash Memory Controller (FMC) --------------------------------*/
// FMCCMD
#define FMCREAD             0x1
#define FMCPROGRAM          0x2
#define FMCPAGEERASE        0x3
#define FMCCODEERASE        0x6
#define FMCMASEERASE        0x7

/*------------- System timer (SysTick) ---------------------------------------*/
// SysTickCTRL
#define SysTickEN           (1<<0)
#define SysTickINT          (1<<1)
#define SysTickCLKSOURCE    (1<<2)
#define SysTickCOUNTFLAG    (1<<16)

#include "CMS32F030x.h"
#include "CMS32F030x_gpio.h"
#include "CMS32F030x_iic.h"
#include "CMS32F030x_spi.h"
#include "CMS32F030x_syscon.h"
#include "CMS32F030x_uart.h"
#include "CMS32F030x_tim.h"
#include "CMS32F030x_wdt.h"
#include "CMS32F030x_pwm.h"
#include "CMS32F030x_adc.h"
#include "CMS32F030x_fmc.h"
#include "CMS32F030x_epwm.h"

#ifdef  USE_FULL_ASSERT

/**
  * @brief  The assert_param macro is used for function's parameters check.
  * @param  expr: If expr is false, it calls assert_failed function which reports 
  *         the name of the source file and the source line number of the call 
  *         that failed. If expr is true, it returns no value.
  * @retval None
  */
  #define assert_param(expr) ((expr) ? (void)0 : assert_failed((uint8_t *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
  void assert_failed(uint8_t* file, uint32_t line);
#else
  #define assert_param(expr) ((void)0)
#endif /* USE_FULL_ASSERT */


#endif
