/**
  ******************************************************************************
  * @file    CMS32F030x_gpio.h
  * @author  CMS IC Test Team
  * @version V1.0.0
  * @date    05-December-2016
  * @brief   This file contains all the functions prototypes for the GPIO 
  *          firmware library. 
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 A menber of CMSemicon</center></h2>
  *
  * Licensed under MCD-CMS Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  * 
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
#ifndef __CMS32F030X_GPIO_H
#define __CMS32F030X_GPIO_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "CMS32F030x.h"
#include "config_CMS32F030x.h"     

/** @addtogroup CMS32F030x_StdPeriph_Driver
  * @{
  */
/** @defgroup Configuration_Mode_enumeration 
  * @{
  */

typedef enum
{ 
	GPIO_Mode_IN_FLOATING = 0x00,
  GPIO_Mode_Out_PP      = 0x01,	
  GPIO_Mode_Out_OD      = 0x02,  
  GPIO_Mode_IPU         = 0x03,
  GPIO_Mode_IPD         = 0x04,
}GPIOMode_TypeDef;




typedef enum
{
  GPIO_DrvCur_Large,        /*!< GPIO driving current large   */
  GPIO_DrvCur_Low,          /*!< GPIO driving current low     */
}GPIODrvCur_TypeDef;

typedef enum
{
  GPIO_OutRate_Fast,        /*!< GPIO output rate fast        */
  GPIO_OutRate_Slow,        /*!< GPIO output rate slow        */
}GPIOOutRate_TypeDef;

#define IS_GPIO_MODE(MODE) (((MODE) == GPIO_Mode_INPu)|| ((MODE) == GPIO_Mode_OUTPP) || \
                            ((MODE) == GPIO_Mode_OUTOD)|| ((MODE) == GPIO_Mode_IN))
/**
  * @}
  */

/** @defgroup Output_type_enumeration
  * @{
  */


/** @defgroup Bit_SET_and_Bit_RESET_enumeration
  * @{
  */
typedef enum
{ 
  Bit_RESET = 0,
  Bit_SET
}BitAction;

#define IS_GPIO_BIT_ACTION(ACTION) (((ACTION) == Bit_RESET) || ((ACTION) == Bit_SET))
/**
  * @}
  */

typedef enum
{
    GPIO_IntMode_Level,
    GPIO_IntMode_Edge,
}GPIO_InterruptModeDef;

typedef enum
{
    GPIO_IntVal_HighOrRis,
    GPIO_IntVal_LowOrFall,
}GPIO_InterruptValDef;

typedef enum
{
    GPIO_IntEdge_One,
    GPIO_IntEdge_Any,
}GPIO_InterruptEdgeDef;

/**
  * @brief  GPIO Init structure definition  
  */
typedef struct
{
  uint32_t GPIO_Pin;              /*!< Specifies the GPIO pins to be configured.
                                       This parameter can be any value of @ref GPIO_pins_define */
                                       
  GPIOMode_TypeDef GPIO_Mode;     /*!< Specifies the operating mode for the selected pins.
                                       This parameter can be a value of @ref GPIOMode_TypeDef   */

  GPIODrvCur_TypeDef GPIO_DrvCur; /*!< Specifies the output current for the selected pins.
                                       This parameter can be a value of @ref GPIODrvCur_TypeDef   */
  GPIOOutRate_TypeDef GPIO_OutRate;/*!< Specifies the output rate for the selected pins.
                                       This parameter can be a value of @ref GPIOOutRate_TypeDef   */  
}GPIO_InitTypeDef;

typedef struct
{
    uint8_t IntMode;             /*!< This parameter can be a value of @ref GPIO_InterruptModeDef  */
    uint8_t IntVal;              /*!< This parameter can be a value of @ref GPIO_InterruptValDef  */
    uint8_t IntEdge;             /*!< This parameter can be a value of @ref GPIO_InterruptEdgeDef  */
}GPIO_INTType;


//-----------------------------------------------
/** @defgroup GPIO_pins_define 
  * @{
  */
#define GPIO_Pin_0                 ((uint32_t)(0x0001))  /*!< Pin 0 selected    */
#define GPIO_Pin_1                 ((uint32_t)(0x0002))  /*!< Pin 1 selected    */
#define GPIO_Pin_2                 ((uint32_t)(0x0004))  /*!< Pin 2 selected    */
#define GPIO_Pin_3                 ((uint32_t)(0x0008))  /*!< Pin 3 selected    */
#define GPIO_Pin_4                 ((uint32_t)(0x0010))  /*!< Pin 4 selected    */
#define GPIO_Pin_5                 ((uint32_t)(0x0020))  /*!< Pin 5 selected    */
#define GPIO_Pin_6                 ((uint32_t)(0x0040))  /*!< Pin 6 selected    */
#define GPIO_Pin_7                 ((uint32_t)(0x0080))  /*!< Pin 7 selected    */
#define GPIO_Pin_All               ((uint32_t)(0x00FF))  /*!< Pin 7 selected    */

#define IS_GET_GPIO_PIN(PIN) (((PIN) == GPIO_Pin_0) || \
                              ((PIN) == GPIO_Pin_1) || \
                              ((PIN) == GPIO_Pin_2) || \
                              ((PIN) == GPIO_Pin_3) || \
                              ((PIN) == GPIO_Pin_4) || \
                              ((PIN) == GPIO_Pin_5) || \
                              ((PIN) == GPIO_Pin_6) || \
                              ((PIN) == GPIO_Pin_7) || \
                              ((PIN) == GPIO_Pin_All))
/**
  * @}
  */                                       

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
/* Function used to set the GPIO configuration to the default reset state *****/
void GPIO_DeInit(GPIO_TypeDef* GPIOx);
/* Initialization and Configuration functions *********************************/
void GPIO_Init(GPIO_TypeDef* GPIOx,GPIO_InitTypeDef* GPIO_InitStruct);
/* GPIO Read and Write functions **********************************************/
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct);
void GPIO_InputFit(GPIO_TypeDef* GPIOx,uint8_t GPIO_Pin,FunctionalState NewStatus);
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint8_t GPIO_Pin);
uint8_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx);
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint8_t GPIO_Pin);
uint8_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx);
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint8_t GPIO_Pin);
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint8_t GPIO_Pin);
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint8_t GPIO_Pin, BitAction BitVal);
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal);
/*Interrutp configration functions*/
void GPIO_ITConfig(GPIO_TypeDef* GPIOx,uint8_t GPIO_Pin,GPIO_INTType* GPIO_IntType);
void GPIO_ITCmd(GPIO_TypeDef* GPIOx,uint8_t GPIO_Pin,FunctionalState NewStatus);
BitAction GPIO_GetINTSource(GPIO_TypeDef* GPIOx,uint8_t GPIO_Pin);
void GPIO_ITClear(GPIO_TypeDef* GPIOx,uint8_t GPIO_Pin);

#ifdef __cplusplus
}
#endif

#endif /* __CMS32F030X_GPIO_H */
/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT A menber of CMSemicon *****END OF FILE****/
