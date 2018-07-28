#include "CMS32F030x_iic.h"

/**
  * @brief  Deinitializes the I2Cx peripheral registers to their default reset values.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @retval None
  */
void I2C_DeInit(I2C_TypeDef* I2Cx)
{
    I2Cx->RST = I2C_RST_RST;
    
    if(I2Cx == I2C0)
    {
        SYSCON->APBCKEN &= ~(1<<7);
    }
}

/**
  * @brief  Initializes the I2Cx peripheral according to the specified
  *         parameters in the I2C_InitStruct.
  * @param  I2Cx: where x can be 0 to select the I2C peripheral.
  * @param  I2C_InitStruct: pointer to a I2C_InitTypeDef structure that
  *         contains the configuration information for the specified I2C peripheral.
  * @retval None
  */
void I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypeDef* I2C_InitStruct)
{
    if(I2C_InitStruct->I2C_Mode == I2C_Mode_Slave)
    {
        if(I2C_InitStruct->I2C_OwnAddressType == I2C_OwnAddress_10Bit)
        {
            I2Cx->XADR0 = I2C_InitStruct->I2C_Address<<1;
        }
        else
        {
            I2Cx->ADR0 = I2C_InitStruct->I2C_Address<<1;
        }
    }
    if(I2C_InitStruct->I2C_Ack == I2C_ACK_Use)
    {
        I2Cx->CONSET |= I2C_CONSET_AA;
    }
}

/**
  * @brief  Configure the SPI clock. Only for master mode.
  * @param  I2Cx: Specify the I2C0 port.
  * @param  Frequency: Specify the SPI clock rate in Hz. 
  *                    It's the target clock rate of SPI
  *                    base clock and variable clock 1.
  * @retval The actual clock rate of SPI engine clock is returned.
  *         SPI engine clock rate = APB clock rate / ((M + 1) * N)  (N is an even value from 2 to 254)
  *         The actual clock rate may be different from the target SPI clock rate.
  */
uint8_t I2C_ClkSet(I2C_TypeDef* I2Cx,uint32_t Frequency)
{
    uint32_t M, N, u32Div, count, temp;

      u32Div = (SystemAPBClock / 10) / Frequency;

      N = u32Div / 16;

      for (M=0; M<8; M++)
      {
        temp = 1;
        for (count=0; count<M; count++)
        {
          temp *= 2;
        }
        if(temp > N)
          break;
      }

      if (M > 7)
        M = 7;

      N = (u32Div / temp) - 1;
      if (N > 15)
        N = 15;

      if (I2Cx == I2C0)
        SYSCON->APBCKEN |= I2C0CE;

        I2Cx->CLK = (M << 4) | N;

      return SUCCESS;
}

/**
  * @brief  Fills each I2C_InitStruct member with its default value.
  * @param  I2C_InitStruct: pointer to an I2C_InitTypeDef structure which will be initialized.
  * @retval None
  */
void I2C_StructInit(I2C_InitTypeDef* I2C_InitStruct)
{
    I2C_InitStruct->I2C_Mode            = I2C_Mode_Mast;
    I2C_InitStruct->I2C_OwnAddressType  = I2C_OwnAddress_7Bit;
    I2C_InitStruct->I2C_Address         = 0x00;
    I2C_InitStruct->I2C_Ack             = I2C_ACK_Use;
}

/**
  * @brief  Enables or disables the specified I2C peripheral.
  * @param  I2Cx: where x can be 0 to select the I2C peripheral.
  * @param  NewState: new state of the I2Cx peripheral. 
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        I2Cx->CONSET |= I2C_CONSET_I2CEN;
    }
    else
    {
        I2Cx->CONCLR &= ~I2C_CONSET_I2CEN;
    }
}

/**
  * @brief  Enables or disables the specified I2C software reset.
  * @param  I2Cx: where x can be 0 to select the I2C peripheral.
  * @retval None
  */
void I2C_SoftwareResetCmd(I2C_TypeDef* I2Cx)
{
    I2Cx->RST = I2C_RST_RST;
}

/**
  * @brief  Configures the I2C slave own address 0 and mask.
  * @param  I2Cx: where x can be 0 to select the I2C peripheral.
  * @param  Address: specifies the slave address to be programmed.
  * @param  Mask: specifies own address 0 mask to be programmed.
  * @retval None
  */
void I2C_OwnAddress0Config(I2C_TypeDef* I2Cx,I2C_OwnAddress_TypeDef AddrType, uint16_t Address, uint8_t Mask)
{
    if(AddrType == I2C_OwnAddress_7Bit)
    {
        I2Cx->ADR0 = Address << 1;
        I2Cx->ADM0 = Mask << 1;
    }
    else
    {
        I2Cx->XADR0 = Address << 1;
        I2Cx->XADM0 = Mask << 1;
    }
}

/**
  * @brief  Configures the I2C slave own address 1 and mask.
  * @param  I2Cx: where x can be 0 to select the I2C peripheral.
  * @param  Address: specifies the slave address to be programmed.
  * @param  Mask: specifies own address 1 mask to be programmed.
  * @retval None
  */
void I2C_OwnAddress1Config(I2C_TypeDef* I2Cx, uint16_t Address, uint8_t Mask)
{
    I2Cx->ADR1 = Address << 1;
    I2Cx->ADM1 = Mask << 1;
}

/**
  * @brief  Configures the I2C slave own address 2 and mask.
  * @param  I2Cx: where x can be 0 to select the I2C peripheral.
  * @param  Address: specifies the slave address to be programmed.
  * @param  Mask: specifies own address 2 mask to be programmed.
  * @retval None
  */
void I2C_OwnAddress2Config(I2C_TypeDef* I2Cx,uint16_t Address, uint8_t Mask)
{
    I2Cx->ADR2 = Address << 1;
    I2Cx->ADM2 = Address << 1;
}

/**
  * @brief  Configures the I2C slave own address 3 and mask.
  * @param  I2Cx: where x can be 0 to select the I2C peripheral.
  * @param  Address: specifies the slave address to be programmed.
  * @param  Mask: specifies own address 3 mask to be programmed.
  * @retval None
  */
void I2C_OwnAddress3Config(I2C_TypeDef* I2Cx, uint16_t Address, uint8_t Mask)
{
    I2Cx->ADR3 = Address << 1;
    I2Cx->ADM3 = Address << 1;
}

/**
  * @brief  Enables or disables the I2C general0 call mode.
  * @param  I2Cx: where x can be 0 to select the I2C peripheral.
  * @param  NewState: new state of the I2C general call mode.
  *          This parameter can be: ENABLE or DISABLE.  
  * @retval None
  */
void I2C_GeneralCall0Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
    if(NewState == ENABLE)
    {
        I2Cx->ADR0 |= I2C_ADR_GC;
    }
    else
    {
        I2Cx->ADR0 &= ~I2C_ADR_GC;
    }
}

/**
  * @brief  Enables or disables the I2C externAddress0 general call mode.
  * @param  I2Cx: where x can be 0 to select the I2C peripheral.
  * @param  NewState: new state of the I2C general call mode.
  *          This parameter can be: ENABLE or DISABLE.  
  * @retval None
  */
void I2C_GeneralCallEx0Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
    if(NewState == ENABLE)
    {
        I2Cx->XADR0 |= I2C_ADR_GC;
    }
    else
    {
        I2Cx->XADR0 &= ~I2C_ADR_GC;
    }
}

/**
  * @brief  Enables or disables the I2C general1 call mode.
  * @param  I2Cx: where x can be 0 to select the I2C peripheral.
  * @param  NewState: new state of the I2C general call mode.
  *          This parameter can be: ENABLE or DISABLE.  
  * @retval None
  */
void I2C_GeneralCall1Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
    if(NewState == ENABLE)
    {
        I2Cx->ADR1 |= I2C_ADR_GC;
    }
    else
    {
        I2Cx->ADR1 &= ~I2C_ADR_GC;
    }
}

/**
  * @brief  Enables or disables the I2C general2 call mode.
  * @param  I2Cx: where x can be 0 to select the I2C peripheral.
  * @param  NewState: new state of the I2C general call mode.
  *          This parameter can be: ENABLE or DISABLE.  
  * @retval None
  */
void I2C_GeneralCall2Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
    if(NewState == ENABLE)
    {
        I2Cx->ADR2 |= I2C_ADR_GC;
    }
    else
    {
        I2Cx->ADR2 &= ~I2C_ADR_GC;
    }
}

/**
  * @brief  Enables or disables the I2C general3 call mode.
  * @param  I2Cx: where x can be 0 to select the I2C peripheral.
  * @param  NewState: new state of the I2C general call mode.
  *          This parameter can be: ENABLE or DISABLE.  
  * @retval None
  */
void I2C_GeneralCall3Cmd(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
    if(NewState == ENABLE)
    {
        I2Cx->ADR3 |= I2C_ADR_GC;
    }
    else
    {
        I2Cx->ADR3 &= ~I2C_ADR_GC;
    }
}

/**
  * @brief  Generates I2Cx communication START condition.
  * @param  I2Cx: where x can be 0 to select the I2C peripheral.
  * @param  NewState: new state of the I2C START condition generation.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_GenerateSTART(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
    if(NewState == ENABLE)
    {
        I2Cx->CONSET |= I2C_CONSET_STA;
    }
    else
    {
        I2Cx->CONCLR |= I2C_CONCLR_STAC;
    }
}

/**
  * @brief  Generates I2Cx communication STOP condition.
  * @param  I2Cx: where x can be 0 to select the I2C peripheral.
  * @param  NewState: new state of the I2C STOP condition generation.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_GenerateSTOP(I2C_TypeDef* I2Cx)
{
    I2Cx->CONSET |= I2C_CONSET_STO;
}

/**
  * @brief  Generates I2C communication Acknowledge.
  * @param  I2Cx: where x can be 0 to select the I2C peripheral.
  * @param  NewState: new state of the Acknowledge.
  *          This parameter can be: ENABLE or DISABLE.  
  * @retval None
  */
void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
    if(NewState == ENABLE)
    {
        I2Cx->CONSET |= I2C_CONSET_AA;
    }
    else
    {
        I2Cx->CONCLR |= I2C_CONCLR_AAC;
    }
}

/**
  * @brief  Returns the I2C slave matched address .
  * @param  I2Cx: where x can be 0 to select the I2C peripheral.
  * @retval The value of the slave matched address .
  */
uint8_t I2C_GetAddressMatched(I2C_TypeDef* I2Cx)
{
    uint8_t status = 0;
    if(I2Cx->CONSET & I2C_CONSET_ADRF)
    {
        status = 1;
    }else if (I2Cx->CONSET & I2C_CONSET_XADRF)
    {
        status = 2;
    }
    return status;
}

/**
* @brief  Reads the specified I2C register and returns its value.
* @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
* @param  I2C_Register: specifies the register to read.
*          This parameter can be one of the following values:
*            @arg I2C_Register_CONSET  I2C Control Set Register
*            @arg I2C_Register_CONCLR  I2C Control Clear Register
*            @arg I2C_Register_STAT    I2C Status Register
*            @arg I2C_Register_DAT     I2C Data Register
*            @arg I2C_Register_CLK     I2C Clock Control Register
*            @arg I2C_Register_ADR0    I2C Slave Address Register 0.
*            @arg I2C_Register_ADM0    I2C Slave Address Mask Register 0.
*            @arg I2C_Register_XADR0   I2C Extended Slave Address Register 0.
*            @arg I2C_Register_XADM0   I2C Extended Slave Address Mask Register 0.
*            @arg I2C_Register_RST     I2C Software Reset Register 
*            @arg I2C_Register_ADR1    I2C Slave Address Register 1.
*            @arg I2C_Register_ADM1    I2C Slave Address Mask Register 1.
*            @arg I2C_Register_ADR2    I2C Slave Address Register 2.
*            @arg I2C_Register_ADM2    I2C Slave Address Mask Register 2.
*            @arg I2C_Register_ADR3    I2C Slave Address Register 3.
*            @arg I2C_Register_ADM3    I2C Slave Address Mask Register 3.
* @retval The value of the read register.
*/
uint32_t I2C_ReadRegister(I2C_TypeDef* I2Cx, uint8_t I2C_Register)
{
    __IO uint32_t tmp = 0;

    /* Check the parameters */
    assert_param( IS_I2C_REGISTER(I2C_Register) );

    tmp = (uint32_t)I2Cx;
    tmp += I2C_Register;

    /* Return the selected register value */
    return (*(__IO uint32_t *) tmp);
}

/**
  * @brief  Sends a data byte through the I2Cx peripheral.
  * @param  I2Cx: where x can be 0 to select the I2C peripheral.
  * @param  Data: Byte to be transmitted..
  * @retval None
  */
void I2C_SendData(I2C_TypeDef* I2Cx, uint8_t Data)
{
    I2Cx->DAT = Data;
    I2Cx->CONCLR |= I2C_CONCLR_SIC;
}

/**
  * @brief  Get Status register value.
  * @param  I2Cx: where x can be 0 to select the I2C peripheral.
  * @param  Data: Byte to be transmitted..
  * @retval None
  */
uint8_t I2C_GetStatusFlag(I2C_TypeDef* I2Cx)
{
    return I2Cx->STAT;
}
/**
  * @brief  Returns the most recent received data by the I2Cx peripheral.
  * @param  I2Cx: where x can be 0 to select the I2C peripheral.
  * @retval The value of the received data.
  */
uint8_t I2C_ReceiveData(I2C_TypeDef* I2Cx)
{
    uint8_t data=0;
    data = I2Cx->DAT;
    I2Cx->CONCLR |= I2C_CONCLR_SIC;
    return data;
}

/**
  * @brief  Enables or disables the specified I2C interrupts.
  * @param  I2Cx: where x can be 0 to select the I2C peripheral.
  * @param  NewState:This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void I2C_ITConfig(I2C_TypeDef* I2Cx,FunctionalState NewState)
{
    if(NewState == ENABLE)
    {
        I2Cx->CONSET |= I2C_CONSET_I2CIE;
    }
    else
    {
        I2Cx->CONCLR |= I2C_CONCLR_I2CIEC;
    }
}

/**
  * @brief  Checks whether the specified I2C interrupt has occurred or not.
  * @param  I2Cx: where x can be 0 to select the I2C peripheral.
  * @retval The new state of I2C_IT (SET or RESET).
  */
ITStatus I2C_GetITStatus(I2C_TypeDef* I2Cx)
{
    ITStatus status = RESET;
    if(I2Cx->CONSET & I2C_CONSET_SI)
    {
        status = SET;
    }
    else
    {
        status = RESET;
    }
    return status;
}

/**
  * @brief  Clears the I2Cx's interrupt pending bits.
  * @param  I2Cx: where x can be 1 or 2 to select the I2C peripheral.
  * @retval none.
  */
void I2C_ITClear(I2C_TypeDef* I2Cx)
{
    I2Cx->CONCLR |= 1<<3;
}
