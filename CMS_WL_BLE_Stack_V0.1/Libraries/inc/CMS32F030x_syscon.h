#ifndef __CMS32F030X_SYSCON_H
#define __CMS32F030X_SYSCON_H

#include "CMS32F030x.h"
#include "config_CMS32F030x.h"

/** @addtogroup CMS32F030x_StdPeriph_Driver
  * @{
  */

/** @addtogroup SYSCON
  * @{
  */

/* Exported types ------------------------------------------------------------*/


typedef enum
{
    SYS_DeviceFlash_28K,                    //Flash rom size is 28k
    SYS_DeviceFlash_32K,                    //Flash rom size is 32k
}SYS_DeviceFlash_TypeDef;

#define SYS_HSE_LS          ((uint32_t)(0x00))
#define SYS_HSE_HS          ((uint32_t)(1<<0))
#define IS_SYS_HSE(HSE)     (((HSE) == SYS_HSE_LS) || ((HSE) == SYS_HSE_HS))

#define SYS_HSI_8M          ((uint32_t)(0<<0))
#define SYS_HSI_48M         ((uint32_t)(1<<0))
#define IS_SYS_HSI(HSI)     (((HSI) == SYS_HSI_22M) || ((HSI) == SYS_HSI_8M))

#define SYS_MCO_HCLK        ((uint32_t)(0x00 << 9))
#define SYS_MCO_IHRC        ((uint32_t)(0x01 << 9))
#define SYS_MCO_XT          ((uint32_t)(0x02 << 9))
#define SYS_MCO_PLLCLK      ((uint32_t)(0x03 << 9))
#define IS_SYS_MCO(MCO)     (((MCO) == SYS_MCO_HCLK) || ((MCO)) )

#define SYS_CLK_IRC         ((uint32_t)(0x00))
#define SYS_CLK_XOSC        ((uint32_t)(0x01))
#define SYS_CLK_IRC10K      ((uint32_t)(0x02))
#define SYS_CLK_PLLCLK      ((uint32_t)(0x03))
#define IS_SYS_CLK(CLK)     (((CLK) == SYS_CLK_IRC) || ((CLK) == SYS_CLK_XOSC) \
                            || ((CLK) == SYS_CLK_IRC10K) || ((CLK) == SYS_CLK_PLLCLK))

#define SYS_TMR_PCLK        ((uint32_t)(0x00))
#define SYS_TMR_IRC         ((uint32_t)(0x01))
#define SYS_TMR_XOSC        ((uint32_t)(0x02))
#define SYS_TMR_IRC10K      ((uint32_t)(0x03))
#define IS_TMR_CLK(CLK)     (((CLK) == SYS_TMR_PCLK) || ((CLK) == SYS_TMR_IRC) \
                            || ((CLK) == SYS_TMR_XOSC) || ((CLK) == SYS_TMR_IRC10K))

#define SYS_APB_WDTCE       ((uint32_t)(1<<0))
#define SYS_APB_TIMER01CE   ((uint32_t)(1<<1))
#define SYS_APB_UART0CE     ((uint32_t)(1<<3))
#define SYS_APB_UART1CE     ((uint32_t)(1<<4))
#define SYS_APB_I2C0CE      ((uint32_t)(1<<7))
#define SYS_APB_I2C1CE      ((uint32_t)(1<<8))
#define SYS_APB_SSP0CE      ((uint32_t)(1<<9))
#define SYS_APB_ADCCE       ((uint32_t)(1<<11))
#define SYS_APB_PWMCE       ((uint32_t)(1<<12))
#define SYS_APB_EPWMCE      ((uint32_t)(1<<13))
#define SYS_APB_WWDTCE      ((uint32_t)(1<<14))

#define SYS_PWR_WFI         ((uint32_t)0x01)
#define SYS_PWR_WFE         ((uint32_t)0x02)
#define IS_PWR_SLEEP_ENTRY(ENTRY) (((ENTRY) == SYS_PWR_WFI) || ((ENTRY) == SYS_PWR_WFE))

#define SYS_IT_PLL          ((uint32_t)0x02)
#define SYS_IT_XT           ((uint32_t)0x01)
#define IS_SYS_IT(IT)       (((IT)==SYS_IT_PLL) || ((IT)==SYS_IT_XT))

//--------------------PLL Config
#define SYS_PLLCLKSrc_IHRC   ((uint32_t)(0x00000000))
#define SYS_PLLCLKSrc_XT     ((uint32_t)(0x00000002))
#define IS_SYS_PLLSrc(PLL)     (((PLL) == SYS_PLLCLKSrc_IHRC) || ((PLL) == SYS_PLLCLKSrc_XT))

#define SYS_PLLCLKSrcDiv_1   ((uint32_t)(0x00000000))
#define SYS_PLLCLKSrcDiv_2   ((uint32_t)(0x00000004))
#define SYS_PLLCLKSrcDiv_4   ((uint32_t)(0x00000008))
#define SYS_PLLCLKSrcDiv_8   ((uint32_t)(0x0000000C))
#define IS_SYS_PLLDiv(DIV)   (((DIV) == SYS_PLLCLKSrcDiv_1) || ((DIV) == SYS_PLLCLKSrcDiv_2) || \
                                ((DIV) == SYS_PLLCLKSrcDiv_4) || ((DIV) == SYS_PLLCLKSrcDiv_8))




/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Function used to set the RCC clock configuration to the default reset state */
uint16_t SYS_GetDIDNum(void);
SYS_DeviceFlash_TypeDef SYS_GetDevFlashSize(void);

/* Internal/external clocks, PLL, CSS and MCO configuration functions *********/
void SYS_CLKDeInit(void);
void SYS_HSEConfig(uint8_t SYS_HSE);
void SYS_HSIConfig(uint8_t SYS_HSI);
void SYS_HSECmd(FunctionalState NewState);
void SYS_HSICmd(FunctionalState NewState);
ErrorStatus SYS_WaitForHSEStartUp(void);
ErrorStatus SYS_WaitForHSIStartUp(void);
void SYS_MCOConfig(uint32_t SYS_MCOSource,uint32_t SYS_MCOPrescaler);
void SYS_MCOCmd(FunctionalState NewState);

/* System, AHB and APB busses clocks configuration functions ******************/
void SYS_SYSCLKConfig(uint32_t SYS_SYSCLKSource);
void SYS_AHBConfig(uint8_t SYS_AHBCLK);
void SYS_APBConfig(uint8_t SYS_APBCLK);
void SYS_TMR01Config(uint8_t SYS_TMR01CLK);
void SYS_APBPeriphClockCmd(uint32_t SYS_APBPeriph, FunctionalState NewState);
//void SYS_PLLConfig(uint8_t SYS_PLLSource,uint8_t SYS_PLLDiv,uint8_t SYSPLLMul);
void SYS_PLLConfig(uint32_t PllClkSource,uint32_t CLKSourceDiv,uint32_t M,uint32_t N);
void SYS_PLLCmd(FunctionalState NewState);
ErrorStatus SYS_WaitForPLLStartUp(void);


/* Power,Reset configuration functions*****************************************/
void SYS_EnterSleepMode(uint8_t PWR_Entry);
void SYS_ENterDeepSleepMode(uint8_t PWR_Entry);
void SYS_EnterSTOPMode(uint8_t PWR_Entry);
void SYS_ResetMCU(void);
void SYS_ResetCPU(void);

/*GPIO function configuration functions*/
void SYS_IOPConfig(GPIO_Num GPIOx,uint8_t SYS_IOPFunc);

/* Interrupts and flags management functions **********************************/
void SYS_CLKITConfig(uint8_t SYS_CLKIT, FunctionalState NewState);
FlagStatus SYS_GetFlagStatus(uint8_t SYS_CLKIT);
void SYS_ClearFlag(uint8_t SYS_CLKIT);
ITStatus SYS_GetITStatus(uint8_t SYS_CLKIT);
/**
  * @}
  */

/**
  * @}
  */

#endif
