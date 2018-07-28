/**
  ******************************************************************************
  * @file    CMS32F030x_spi.h
  * @author  CMS IC Test Team
  * @version V1.0.0
  * @date    05-December-2016
  * @brief   This file contains all the functions prototypes for the SPI
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
#ifndef __CMS32F030X_SPI_H
#define __CMS32F030X_SPI_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "CMS32F030x.h"
#include "config_CMS32F030x.h"

/** @addtogroup CMS32F030x_StdPeriph_Driver
  * @{
  */

/** @addtogroup SPI
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/**
  * @brief  SPI Init structure definition
  */

typedef struct
{
  uint16_t SPI_Mode;                /*!< Specifies the SPI mode (Master/Slave).
                                         This parameter can be a value of @ref SPI_mode */

  uint16_t SPI_DataSize;            /*!< Specifies the SPI data size.
                                         This parameter can be a value of @ref SPI_data_size */

  uint16_t SPI_CPO;                /*!< Specifies the serial clock steady state.
                                         This parameter can be a value of @ref SPI_Clock_Polarity */

  uint16_t SPI_CPH;                /*!< Specifies the clock active edge for the bit capture.
                                         This parameter can be a value of @ref SPI_Clock_Phase */

  uint16_t SPI_NSS;                 /*!< Specifies whether the NSS signal is managed by
                                         hardware (NSS pin) or by software using the SSI bit.
                                         This parameter can be a value of @ref SPI_Slave_Select_management */
}SPI_InitTypeDef;


/* Exported constants --------------------------------------------------------*/

/** @defgroup SPI_Exported_Constants
  * @{
  */

#define IS_SPI_ALL_PERIPH(PERIPH) (((PERIPH) == SPP0) || \
                                   ((PERIPH) == SPP1))

#define IS_SPI_0_PERIPH(PERIPH) (((PERIPH) == SPP1))
#define IS_SPI_1_PERIPH(PERIPH) (((PERIPH) == SPP1))

/** @defgroup SPI_mode
  * @{
  */

#define SPI_Mode_Master                 ((uint32_t)0x00000000)
#define SPI_Mode_Slave                  ((uint32_t)0x00000200)
#define IS_SPI_MODE(MODE) (((MODE) == SPI_Mode_Master) || \
                           ((MODE) == SPI_Mode_Slave))
/**
  * @}
  */

/** @defgroup SPI_data_size
  * @{
  */

#define SPI_DataSize_4b                 ((uint32_t)0x00000003)
#define SPI_DataSize_5b                 ((uint32_t)0x00000004)
#define SPI_DataSize_6b                 ((uint32_t)0x00000005)
#define SPI_DataSize_7b                 ((uint32_t)0x00000006)
#define SPI_DataSize_8b                 ((uint32_t)0x00000007)
#define SPI_DataSize_9b                 ((uint32_t)0x00000008)
#define SPI_DataSize_10b                ((uint32_t)0x00000009)
#define SPI_DataSize_11b                ((uint32_t)0x0000000A)
#define SPI_DataSize_12b                ((uint32_t)0x0000000B)
#define SPI_DataSize_13b                ((uint32_t)0x0000000C)
#define SPI_DataSize_14b                ((uint32_t)0x0000000D)
#define SPI_DataSize_15b                ((uint32_t)0x0000000E)
#define SPI_DataSize_16b                ((uint32_t)0x0000000F)
#define IS_SPI_DATA_SIZE(SIZE)  (((SIZE) == SPI_DataSize_4b) || \
                                 ((SIZE) == SPI_DataSize_5b) || \
                                 ((SIZE) == SPI_DataSize_6b) || \
                                 ((SIZE) == SPI_DataSize_7b) || \
                                 ((SIZE) == SPI_DataSize_8b) || \
                                 ((SIZE) == SPI_DataSize_9b) || \
                                 ((SIZE) == SPI_DataSize_10b) || \
                                 ((SIZE) == SPI_DataSize_11b) || \
                                 ((SIZE) == SPI_DataSize_12b) || \
                                 ((SIZE) == SPI_DataSize_13b) || \
                                 ((SIZE) == SPI_DataSize_14b) || \
                                 ((SIZE) == SPI_DataSize_15b) || \
                                 ((SIZE) == SPI_DataSize_16b))
/**
  * @}
  */

/** @defgroup SPI_Clock_Polarity
  * @{
  */

#define SPI_CPO_Low                    ((uint32_t)0x00000000)
#define SPI_CPO_High                   ((uint32_t)0x00000040)
#define IS_SPI_CPO(CPOL) (((CPO) == SPI_CPO_Low) || \
                           ((CPO) == SPI_CPO_High))
/**
  * @}
  */

/** @defgroup SPI_Clock_Phase
  * @{
  */

#define SPI_CPH_1Edge                  ((uint32_t)0x00000000)
#define SPI_CPH_2Edge                  ((uint32_t)0x00000080)
#define IS_SPI_CPH(CPH) (((CPH) == SPI_CPH_1Edge) || \
                           ((CPH) == SPI_CPH_2Edge))
/**
  * @}
  */

/** @defgroup SPI_STAT Bit.
  * @{
  */
#define SPI_STAT_TFE                ((uint32_t)(0x00000001))
#define SPI_STAT_TNF                ((uint32_t)(0x00000002))
#define SPI_STAT_RNE                ((uint32_t)(0x00000004))
#define SPI_STAT_RFF                ((uint32_t)(0x00000008))
#define SPI_STAT_BSY                ((uint32_t)(0x00000010))
/**
  * @}
  */

/** @defgroup SPI_Slave_Select_management
  * @{
  */

#define SPI_NSS_Soft                    ((uint32_t)0x00000004)
#define SPI_NSS_Hard                    ((uint32_t)0x00000000)
#define IS_SPI_NSS(NSS)                 (((NSS) == SPI_NSS_Soft) || \
                                         ((NSS) == SPI_NSS_Hard))
/**
  * @}
  */

/** @defgroup SPI_NSS_internal_software_management
  * @{
  */

#define SPI_NSSInternalSoft_Low         ((uint32_t)0x00000000)
#define SPI_NSSInternalSoft_High        ((uint32_t)0x00000008)
#define IS_SPI_NSS_INTERNAL(INTERNAL)   (((INTERNAL) == SPI_NSSInternalSoft_Low) || \
                                         ((INTERNAL) == SPI_NSSInternalSoft_High))
/**
  * @}
  */
/** @defgroup SPI_IT configration.
  * @{
  */
#define SPI_IT_TxHalfEmpt               ((uint32_t)(0x00000008))
#define SPI_IT_RxHalfFull               ((uint32_t)(0x00000004))
#define SPI_IT_OverTim                  ((uint32_t)(0x00000002))
#define SPI_IT_OverRun                  ((uint32_t)(0x00000001))

/**
  * @}
  */

/** @defgroup SPI_IT configration.
  * @{
  */
#define SPI_ICLR_RORIC                 ((uint32_t)(0x00000001))
#define SPI_ICLR_RTIC                  ((uint32_t)(0x00000002))

/**
  * @}
  */



/**
  * @}
  */

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

/* Initialization and Configuration functions *********************************/
void SPI_DeInit(SSP_TypeDef* SPIx);
void SPI_Init(SSP_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct);
uint32_t SPI_SetClockFreq(SSP_TypeDef* SPIx, uint32_t u32Clock);
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct);
void SPI_Cmd(SSP_TypeDef* SPIx, FunctionalState NewState);
void SPI_DataSizeConfig(SSP_TypeDef* SPIx, uint16_t SPI_DataSize);
void SPI_NSSInternalSoftwareConfig(SSP_TypeDef* SPIx, uint16_t SPI_NSSInternal);
void SPI_SSOutputCmd(SSP_TypeDef* SPIx, uint32_t SPI_NssStatus);

/* Data transfers functions ***************************************************/
void SPI_SendDataNBit(SSP_TypeDef* SPIx, uint16_t Data);
uint16_t SPI_ReceiveDataNBit(SSP_TypeDef* SPIx);

/* Interrupts and flags management functions **********************************/
void SPI_ITConfig(SSP_TypeDef* SPIx, uint8_t SPI_IT, FunctionalState NewState);
FlagStatus SPI_GetFlagStatus(SSP_TypeDef* SPIx, uint16_t SPI_FLAG);
void SPI_ClearITFlag(SSP_TypeDef* SPIx, uint16_t SPI_IT);
ITStatus SPI_GetITStatus(SSP_TypeDef* SPIx, uint8_t SPI_IT);

#ifdef __cplusplus
}
#endif

#endif /*__CMS32F030X_SPI_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT A menmber of CMSemicon *****END OF FILE****/
