/**
  ******************************************************************************
  * @file    CMS32F030x.h
  * @author  CMS IC Test Team
  * @version V1.0.0
  * @date    05-December-2016
  * @brief   This file contains all the functions prototypes for the I2C firmware
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
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CMS32F030X_IIC_H
#define __CMS32F030X_IIC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "CMS32F030x.h"
#include "config_CMS32F030x.h"     

/** @addtogroup CMS32F030x_StdPeriph_Driver
  * @{
  */

/** @addtogroup I2C
  * @{
  */
     

          

/* Exported types ------------------------------------------------------------*/

typedef enum
{
    I2C_Mode_Mast,
    I2C_Mode_Slave,
}I2C_Mode_TypeDef;    
     
typedef enum
{
    I2C_ACK_NoUse,
    I2C_ACK_Use,
}I2C_Ack_TypeDef;    
     
typedef enum
{
    I2C_OwnAddress_7Bit,
    I2C_OwnAddress_10Bit,
}I2C_OwnAddress_TypeDef;
     
/**
  * @brief  I2C Init structure definition
  */

typedef struct
{
    uint32_t I2C_Mode;                /*!< Specifies the I2C mode.
                                         This parameter can be a value of @ref I2C_mode*/
    uint32_t I2C_Ack;
    uint32_t I2C_OwnAddressType;
    uint32_t I2C_Address;             
}I2C_InitTypeDef;

/* Exported constants --------------------------------------------------------*/

/** @addtogroup I2C_CONSET
  * @{
  */
#define I2C_CONSET_I2CIE            ((uint32_t)(0x00000080))
#define I2C_CONSET_I2CEN            ((uint32_t)(0x00000040))
#define I2C_CONSET_STA              ((uint32_t)(0x00000020))
#define I2C_CONSET_STO              ((uint32_t)(0x00000010))
#define I2C_CONSET_SI               ((uint32_t)(0x00000008))
#define I2C_CONSET_AA               ((uint32_t)(0x00000004))
#define I2C_CONSET_XADRF            ((uint32_t)(0x00000002))
#define I2C_CONSET_ADRF             ((uint32_t)(0x00000001))
/**
  * @}
  */

/** @addtogroup I2C_CONCLR
  * @{
  */
#define I2C_CONCLR_I2CIEC           ((uint32_t)(0x00000080))
#define I2C_CONCLR_I2CENC           ((uint32_t)(0x00000040))
#define I2C_CONCLR_STAC             ((uint32_t)(0x00000020))
#define I2C_CONCLR_SIC              ((uint32_t)(0x00000008))
#define I2C_CONCLR_AAC              ((uint32_t)(0x00000004))
/**
  * @}
  */

/** @addtogroup I2C_STAT
  * @{
  */
#define I2C_STAT_BusErr                 	((uint8_t)(0x00))       //Bus error (Master mode only)
#define I2C_STAT_Start                  	((uint8_t)(0x08))       //START condition transmitted
#define I2C_STAT_ReStart                	((uint8_t)(0x10))		//Repeated START condition transmitted
#define I2C_STAT_AddrWriteAck           	((uint8_t)(0x18))		//Address + Write bit transmitted, ACK received
#define I2C_STAT_AddrWriteNAck          	((uint8_t)(0x20))		//Address + Write bit transmitted, Not ACK received
#define I2C_STAT_MDataTxAck             	((uint8_t)(0x28))		//Data byte transmitted in master mode, ACK received
#define I2C_STAT_MDataTXNAck            	((uint8_t)(0x30))		//Data byte transmitted in master mode, Not ACK received
#define I2C_STAT_ArbLost                	((uint8_t)(0x38))		//Arbitration lost in address or data byte
#define I2C_STAT_AddrReadAck            	((uint8_t)(0x40))		//Address + Read bit transmitted, ACK received
#define I2C_STAT_AddrReadNAck           	((uint8_t)(0x48))		//Address + Read bit transmitted, Not ACK received
#define I2C_STAT_DataRevedAck           	((uint8_t)(0x50))		//Data byte received in master mode, ACK transmitted
#define I2C_STAT_DataRevedNAck          	((uint8_t)(0x58))		//Data byte received in master mode, Not ACK transmitted
#define I2C_STAT_SlveAddrWRevedAck      	((uint8_t)(0x60))		//Slave address + Write bit received, ACK transmitted
#define I2C_STAT_ArbLostInaddrMSAWRA    	((uint8_t)(0x68))		//Arbitration lost in address as master, slave address + Write bit received, ACK transmitted
#define I2C_STAT_GCARevedAck            	((uint8_t)(0x70))		//General Call Address received, ACK transmitted
#define I2C_STAT_ArbLostInaddrMGcaA     	((uint8_t)(0x78))		//Arbitration lost in address as master, General Call Address received, ACK transmitted
#define I2C_STAT_DataRevAftSlvAck       	((uint8_t)(0x80))		//Data byte received after slave address received, ACK transmitted
#define I2C_STAT_DataRevAftSlvNAck      	((uint8_t)(0x88))		//Data byte received after slave address received, Not ACK transmitted
#define I2C_STAT_DataRevAftGcaAck       	((uint8_t)(0x90))		//Data byte received after General Call Address received, ACK transmitted
#define I2C_STAT_DataRevAftGcaNAck      	((uint8_t)(0x98))		//Data byte received after General Call Address received, Not ACK transmitted
#define I2C_STAT_StPReStartRevInSlv     	((uint8_t)(0xA0))		//STOP or repeated START condition received in slave mode
#define I2C_STAT_SlveAddrRRevedAck      	((uint8_t)(0xA8))		//Slave address + Read bit received, ACK transmitted
#define I2C_STAT_ArbLostINAddrMSlvRRevdAck  ((uint8_t)(0xB0))	    //Arbitration lost in address as master, slave address + Read bit received, ACK transmitted
#define I2C_STAT_DataTrsmtedSlvAck      	((uint8_t)(0xB8))		//Data byte transmitted in slave mode, ACK received
#define I2C_STAT_DataTrsmtedSlvNAck     	((uint8_t)(0xC0))		//Data byte transmitted in slave mode, Not ACK received
#define I2C_STAT_LastTrsmtedSlvAck      	((uint8_t)(0xC8))		//Last byte transmitted in slave mode, ACK received
#define I2C_STAT_LastTrsmtedSlvNAck     	((uint8_t)(0xD0))		//Last byte transmitted in slave mode, Not ACK received
#define I2C_STAT_SecondAddrTrsmtedAck   	((uint8_t)(0xE0))		//Second Address byte transmitted, ACK received
#define I2C_STAT_SecondAddrTrsmtedNAck  	((uint8_t)(0xE8))		//Second Address byte transmitted, Not ACK received
#define I2C_STAT_NoRelevant             	((uint8_t)(0xF8))		//No relevant status information, IFLG=0
/**
  * @}
  */
  
/** @addtogroup I2C_ADR
* @{
*/

#define I2C_ADR_GC                     ((uint32_t)(0x000000001))

/**
  * @}
  */ 
  
/** @addtogroup I2C_ADR
* @{
*/

#define I2C_XADR_GC                    ((uint32_t)(0x000000001))

/**
  * @}
  */ 
  
 
/** @addtogroup I2C_RST
  * @{
  */
#define I2C_RST_RST                     ((uint32_t)(0x000000007))
/**
  * @}
  */ 

/** @addtogroup I2C_Register_Map
  * @{
  */
#define I2C_Register_CONSET            ((uint8_t)0x00)
#define I2C_Register_CONCLR            ((uint8_t)0x04)
#define I2C_Register_STAT              ((uint8_t)0x08)
#define I2C_Register_DAT               ((uint8_t)0x0C)
#define I2C_Register_CLK               ((uint8_t)0x10)
#define I2C_Register_ADR0              ((uint8_t)0x14)
#define I2C_Register_ADM0              ((uint8_t)0x18)
#define I2C_Register_XADR0             ((uint8_t)0x1C)
#define I2C_Register_XADM0             ((uint8_t)0x20)
#define I2C_Register_RST               ((uint8_t)0x24)
#define I2C_Register_ADR1              ((uint8_t)0x28)
#define I2C_Register_ADM1              ((uint8_t)0x2C)
#define I2C_Register_ADR2              ((uint8_t)0x30)
#define I2C_Register_ADM2              ((uint8_t)0x34)
#define I2C_Register_ADR3              ((uint8_t)0x38)
#define I2C_Register_ADM3              ((uint8_t)0x3C)

#define IS_I2C_REGISTER(REGISTER)       (((REGISTER) == I2C_Register_CONSET) || \
                                         ((REGISTER) == I2C_Register_CONCLR) || \
                                         ((REGISTER) == I2C_Register_STAT)   || \
                                         ((REGISTER) == I2C_Register_DAT)    || \
                                         ((REGISTER) == I2C_Register_CLK)    || \
                                         ((REGISTER) == I2C_Register_ADR0)   || \
                                         ((REGISTER) == I2C_Register_ADM0)   || \
                                         ((REGISTER) == I2C_Register_XADR0)  || \
                                         ((REGISTER) == I2C_Register_XADM0)  || \
                                         ((REGISTER) == I2C_Register_RST)    || \
                                         ((REGISTER) == I2C_Register_ADR1)   || \
                                         ((REGISTER) == I2C_Register_ADM1)   || \
                                         ((REGISTER) == I2C_Register_ADR2)   || \
                                         ((REGISTER) == I2C_Register_ADM2)   || \
                                         ((REGISTER) == I2C_Register_ADR3)   || \
                                         ((REGISTER) == I2C_Register_ADM3))



/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */


/* Initialization and Configuration functions *********************************/
void I2C_DeInit(I2C_TypeDef* I2Cx);
void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct);
uint8_t I2C_ClkSet(I2C_TypeDef* I2Cx,uint32_t Frequency);
void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct);
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_SoftwareResetCmd(I2C_TypeDef* I2Cx);
void I2C_OwnAddress0Config(I2C_TypeDef* I2Cx, I2C_OwnAddress_TypeDef AddrType, uint16_t Address, uint8_t Mask);
void I2C_OwnAddress1Config(I2C_TypeDef* I2Cx, uint16_t Address, uint8_t Mask);
void I2C_OwnAddress2Config(I2C_TypeDef* I2Cx, uint16_t Address, uint8_t Mask);
void I2C_OwnAddress3Config(I2C_TypeDef* I2Cx, uint16_t Address, uint8_t Mask);
void I2C_GeneralCall0Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GeneralCallEx0Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GeneralCall1Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GeneralCall2Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GeneralCall3Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState);

/* Communications handling functions ******************************************/
void I2C_GenerateSTART(I2C_TypeDef* I2Cx, FunctionalState NewState);
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx);
uint8_t I2C_GetAddressMatched(I2C_TypeDef* I2Cx);
uint16_t I2C_GetTransferDirection(I2C_TypeDef* I2Cx);
/* I2C registers management functions *****************************************/
uint32_t I2C_ReadRegister(I2C_TypeDef* I2Cx, uint8_t I2C_Register);

/* Data transfers management functions ****************************************/
void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data);
uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx);

/* Interrupts and flags management functions **********************************/
uint8_t I2C_GetStatusFlag(I2C_TypeDef* I2Cx);
void I2C_ITConfig(I2C_TypeDef* I2Cx,FunctionalState NewState);
ITStatus I2C_GetITStatus(I2C_TypeDef* I2Cx);
void I2C_ITClear(I2C_TypeDef* I2Cx);

#ifdef __cplusplus
}
#endif

#endif /*__CMS32F030X_IIC_H */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT A menmber of CMSemicon *****END OF FILE****/
