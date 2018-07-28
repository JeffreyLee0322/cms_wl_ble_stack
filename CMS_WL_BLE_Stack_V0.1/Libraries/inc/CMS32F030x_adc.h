/**
  ******************************************************************************
  * @file    CMS32F030x_adc.h
  * @author  CMS IC Test Team
  * @version V1.0.0
  * @date    05-December-2016
  * @brief   This file contains all the functions prototypes for the ADC firmware
  *          library
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
#ifndef __CMS32F030X_ADC_H
#define __CMS32F030X_ADC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "CMS32F030x.h"
#include "config_CMS32F030x.h"

/** @addtogroup CMS32F030x_StdPeriph_Driver
  * @{
  */

/** @addtogroup ADC
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  ADC Init structure definition
  */

/** @defgroup ADC_Conversion_Mode
  * @{
  */
#define ADC_CON_ADCMSOne                ((uint32_t)(0x00000000))
#define ADC_CON_ADCMSContinuous         ((uint32_t)(0x00000008))
/**
  * @}
  */

/** @defgroup ADC_Div_Mode
  * @{
  */

#define ADC_Div_1             	    ((uint32_t)(0))
#define ADC_Div_2                   ((uint32_t)(1))
#define ADC_Div_4                   ((uint32_t)(2))
#define ADC_Div_8                   ((uint32_t)(3))
#define ADC_Div_16                  ((uint32_t)(4))
#define ADC_Div_32                  ((uint32_t)(5))
#define ADC_Div_64                  ((uint32_t)(6))
#define ADC_Div_128                 ((uint32_t)(7))
/**
  * @}
  */

/** @defgroup ADC_Exported_Constants
  * @{
  */

#define ADC_Channel_0                   (0)
#define ADC_Channel_1                   (1)
#define ADC_Channel_2                   (2)
#define ADC_Channel_3                   (3)
#define ADC_Channel_4                   (4)
#define ADC_Channel_5                   (5)
#define ADC_Channel_6                   (6)
#define ADC_Channel_7                   (7)
#define ADC_Channel_8                   (8)
#define ADC_Channel_9                   (9)
#define ADC_Channel_10                  (10)
#define ADC_Channel_11                  (11)
#define ADC_Channel_12                  (12)
#define ADC_Channel_13                  (13)
#define ADC_Channel_14                  (14)
#define ADC_Channel_15                  (15)
/**
  * @}
  */

/** @defgroup Configuration_Mode_enumeration
  * @{
  */
typedef struct
{
    uint32_t ADC_ADCMS;             /*!< Specifies the ADC conversion mode to be configured.
                                       This parameter can be any value of @ref ADC_Conversion_Mode */
    uint32_t ADC_ADCDIV;            /*!< Specifies the ADC clock div to be configured.
                                       This parameter can be any value of @ref ADC_Div_Mode */
}ADC_InitStructTypeDef;
/**
  * @}
  */

/* Exported constants --------------------------------------------------------*/

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/*  Function used to set the ADC configuration to the default reset state *****/
void ADC_DeInit(ADC_TypeDef* ADCx);

/* Initialization and Configuration functions *********************************/
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitStructTypeDef* ADC_InitStruct);
void ADC_StructInit(ADC_InitStructTypeDef* ADC_InitStruct);
void ADC_Cmd(ADC_TypeDef* ADCx,FunctionalState NewStatus);

void ADC_ChannelConfig(ADC_TypeDef* ADCx,uint32_t ADC_Channel,FunctionalState NewStatus);
void ADC_StopOfConversion(ADC_TypeDef* ADCx);
void ADC_StartOfConversion(ADC_TypeDef* ADCx);
FlagStatus ADC_GetConversionStatus(ADC_TypeDef* ADCx,uint32_t ADC_Channel);
uint16_t ADC_GetConversionValue(ADC_TypeDef* ADCx,uint32_t ADC_Channel);

/* Interrupts and flags management functions **********************************/
void ADC_ITConfig(ADC_TypeDef* ADCx, uint32_t ADC_Channel, FunctionalState NewState);
void ADC_ClearFlag(ADC_TypeDef* ADCx, uint32_t ADC_FLAG);
ITStatus ADC_GetITStatus(ADC_TypeDef* ADCx, uint32_t ADC_Channel);
void ADC_ClearITPendingBit(ADC_TypeDef* ADCx, uint32_t ADC_Channel);

#ifdef __cplusplus
}
#endif

#endif /*__CMS32F030X_ADC_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT A menmber of CMSemicon *****END OF FILE****/
