/**
  ******************************************************************************
  * @file    CMS32F030x_UART.h
  * @author  CMS IC Test Team
  * @version V1.0.0
  * @date    05-December-2016
  * @brief   This file contains all the functions prototypes for the UART
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
#ifndef __CMS32F030X_UART_H
#define __CMS32F030X_UART_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "CMS32F030x.h"
#include "config_CMS32F030x.h"

/** @addtogroup CMS32F030x_StdPeriph_Driver
  * @{
  */

/** @addtogroup UART
  * @{
  */

/* Exported types ------------------------------------------------------------*/



/**
  * @brief  UART Init Structure definition
  */

typedef struct
{
  uint32_t UART_BaudRate;            /*!< This member configures the UART communication baud rate.
                                           The baud rate is computed using the following formula:
                                            - IntegerDivider = ((PCLKx) / (16 * (UART_InitStruct->UART_BaudRate)))
                                            - FractionalDivider = ((IntegerDivider - ((uint32_t) IntegerDivider)) * 16) + 0.5 */

  uint32_t UART_WordLength;          /*!< Specifies the number of data bits transmitted or received in a frame.
                                           This parameter can be a value of @ref UART_Word_Length */

  uint32_t UART_StopBits;            /*!< Specifies the number of stop bits transmitted.
                                           This parameter can be a value of @ref UART_Stop_Bits */

  uint32_t UART_Parity;              /*!< Specifies the parity mode.
                                           This parameter can be a value of @ref UART_Parity
                                           @note When parity is enabled, the computed parity is inserted
                                                 at the MSB position of the transmitted data (9th bit when
                                                 the word length is set to 9 data bits; 8th bit when the
                                                 word length is set to 8 data bits). */
  uint32_t UART_ParityType;
} UART_InitTypeDef;

typedef struct
{
    uint32_t UART_FCR_RXTL;
    uint32_t UART_FCR_TXTL;
}UART_InitFifoTypeDef;

typedef enum
{
    IT_UART_RecLine         = 3,
    IT_UART_RecData         = 2,
    IT_UART_ReceiveFifo     = 6,
    IT_UART_TXEmpt          = 1,
    IT_UART_ModemStachange  = 0,
    IT_UART_No              = 8,
}IT_UART_StatusType;

/* Exported constants --------------------------------------------------------*/

/** @defgroup UART_Exported_Constants
  * @{
  */

/** @defgroup UART_Word_Length
  * @{
  */

#define UART_WordLength_8b          ((uint32_t)0x00000003)
#define UART_WordLength_7b          ((uint32_t)0x00000002)
#define UART_WordLength_6b          ((uint32_t)0x00000001)
#define UART_WordLength_5b          ((uint32_t)0x00000000)
#define IS_UART_WORD_LENGTH(LENGTH) (((LENGTH) == UART_WordLength_8b) || \
                                     ((LENGTH) == UART_WordLength_7b) || \
                                     ((LENGTH) == UART_WordLength_6b) || \
                                     ((LENGTH) == UART_WordLength_5b))
/**
  * @}
  */

/** @defgroup UART_Stop_Bits
  * @{
  */

#define UART_StopBits_1                     ((uint32_t)0x00000000)
#define UART_StopBits_2                     ((uint32_t)0x00000004)
#define IS_UART_STOPBITS(STOPBITS)          (((STOPBITS) == UART_StopBits_1) || \
                                            ((STOPBITS) == UART_StopBits_2))
/**
  * @}
  */

/** @defgroup UART_Parity Enable
  * @{
  */
#define UART_Parity_Enable                  ((uint32_t)(0x00000008))
#define UART_Parity_Disable                 ((uint32_t)(0x00000000))
#define IS_UART_PARITY_ENABLE(PARITY)       (((PARITY) == UART_Parity_Enable) || \
                                            ((PARITY) == UART_Parity_Disable))

/**
  * @}
  */

/** @defgroup UART_Parity Type
  * @{
  */
#define UART_Parity_Odd                      ((uint32_t)(0x00000000))
#define UART_Parity_Even                     ((uint32_t)(0x00000010))
#define UART_Parity_Forced1                  ((uint32_t)(0x00000020))
#define UART_Parity_Forced0                  ((uint32_t)(0x00000030))
#define IS_UART_PARITY(PARITY)              (((PARITY) == UART_Parity_Odd) || \
                                             ((PARITY) == UART_Parity_Even) || \
                                             ((PARITY) == UART_Parity_Forced0 || \
                                             ((PARITY) == )
/**
  * @}
  */

/** @defgroup UART_IER Type
* @{
*/
#define UART_IER_RBRIE              ((uint32_t)(0x00000001))
#define UART_IER_THREIE             ((uint32_t)(0x00000002))
#define UART_IER_RLSIE              ((uint32_t)(0x00000004))
#define UART_IER_MDSIE              ((uint32_t)(0x00000008))
#define UART_IER_XOFIE              ((uint32_t)(0x00000002))
#define UART_IER_RTSIE              ((uint32_t)(0x00000004))
#define UART_IER_CTSIE              ((uint32_t)(0x00000008))
/**
  * @}
  */

/** @defgroup UART_FIFO Type
  * @{
  */
#define UART_FCR_RXTL1Byte      ((uint32_t)(0x00000000))
#define UART_FCR_RXTL4Byte      ((uint32_t)(0x00000040))
#define UART_FCR_RXTL8Byte      ((uint32_t)(0x00000080))
#define UART_FCR_RXTL14Byte     ((uint32_t)(0x000000C0))

#define UART_FCR_TXTL1Byte      ((uint32_t)(0x00000000))
#define UART_FCR_TXTL4Byte      ((uint32_t)(0x00000010))
#define UART_FCR_TXTL8Byte      ((uint32_t)(0x00000020))
#define UART_FCR_TXTL14Byte     ((uint32_t)(0x00000030))

/**
  * @}
  */

/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Initialization and Configuration functions *********************************/
void UART_DeInit(UART_TypeDef* UARTx);
void UART_Init(UART_TypeDef* UARTx, UART_InitTypeDef* UART_InitStruct);
void UART_StructInit(UART_InitTypeDef* UART_InitStruct);

/* Data transfers functions ***************************************************/
void UART_SendData(UART_TypeDef* UARTx, uint16_t Data);
uint8_t UART_ReceiveData(UART_TypeDef* UARTx);

/* FIFO Control functions *****************************************************/
void UART_FIFOControl(UART_TypeDef* UARTx,UART_InitFifoTypeDef* UART_FIFOInitStruct);
void UART_FIFORstTx(UART_TypeDef* UARTx);
void UART_FIFORstRx(UART_TypeDef* UARTx);
void UART_FIFOCmd(UART_TypeDef* UARTx,FunctionalState NewStatus);

/* Interrupts flags management functions **********************************/
void UART_ITConfig(UART_TypeDef* UARTx, uint32_t UART_IT, FunctionalState NewState);
IT_UART_StatusType UART_GetITStatus(UART_TypeDef* UARTx);

#ifdef __cplusplus
}
#endif

#endif /* __CMS32F030X_UART_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT A menmber of CMSemicon *****END OF FILE****/
