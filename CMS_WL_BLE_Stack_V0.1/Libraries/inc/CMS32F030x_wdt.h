/**
  ******************************************************************************
  * @file    CMS32F030x_WDT.h
  * @author  CMS IC Test Team
  * @version V1.0.0
  * @date    05-December-2016
  * @brief   This file contains all the functions prototypes for the WDT
  *          firmware library.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 A menmber of CMSemicon</center></h2>
  *
  * Licensed under MCD-CMS Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.mcu.com.cn/about.php
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CMS32F030X_WDT_H
#define __CMS32F030X_WDT_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "CMS32F030x.h"
#include "config_CMS32F030x.h"


/** @addtogroup CMS32F030x_StdPeriph_Driver
  * @{
  */

/** @addtogroup WDT
  * @{
  */
/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/** @defgroup WDT_Exported_Constants
  * @{
  */

/** @defgroup WDT_Prescaler_Set
  * @{
  */
#define WDT_Prescaler_1                 ((uint32_t)0x00000000)
#define WDT_Prescaler_16                ((uint32_t)0x00000004)
#define WDT_Prescaler_256               ((uint32_t)0x00000008)
#define IS_WDT_PRESCALER(PRESCALER)     (((PRESCALER) == WDT_Prescaler_1) || \
                                            ((PRESCALER) == WDT_Prescaler_16) || \
                                            ((PRESCALER) == WDT_Prescaler_256))
/**
  * @}
  */

/** @defgroup WDT_IT_Set
  * @{
  */
#define WDT_IT_Enable                   ((uint32_t)(0x00000001))
#define WDT_IT_Disable                  ((uint32_t)(0x00000000))
/**
  * @}
  */

/** @defgroup WDT_IT_Set
  * @{
  */
typedef struct{
    FunctionalState WDT_Reset;               /*!< Specifies the WDT reset set.
                                        This parameter can be a value of @arg ENABLE/DISABLE */
    uint32_t WDT_PrescleDiv;            /*!< Specifies the WDT Prescale div.
                                        This parameter can be a value of @ref WDT_Prescaler_Set */
    uint32_t WDT_ITEnable;              /*!< Specifies the WDT interrupt.
                                        This parameter can be a value of @ref WDT_IT_Set */
    uint32_t WDT_LoadValue;             /*!< Specifies the WDT LOAD register.
                                        This parameter can be a value of 0-65536 */
}WDT_InitStructTypeDef;
/**
  * @}
  */
/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/*  Function used to set the WDT configuration to the default reset state ****/
void WDT_DeInit(void);
void WDT_Init(WDT_TypeDef* WDTx,WDT_InitStructTypeDef* WDT_InitType);
void WDT_DebugStop(FunctionalState newstatus);

/* Prescaler, Refresh window and Counter configuration functions **************/
void WDT_SetPrescaler(uint32_t WDT_Prescaler);
void WDT_SetEnableReset(FunctionalState newstatus);
void WDT_SetCounter(uint32_t Counter);

/* Interrupts and flags management functions **********************************/
void WDT_ITConfig(FunctionalState newstatus);
ITStatus WDT_GetITStatus(void);
void WDT_ClearITPendingBit(void);
#ifdef __cplusplus
}
#endif

#endif /* __CMS32F030X_WDT_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT A menmber of CMSemicon *****END OF FILE****/

