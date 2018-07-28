#include "CMS32F030x_spi.h"

/** @defgroup SPI_Private_Functions
  * @{
  */

/**
  * @brief  Deinitializes the SPIx peripheral registers to their default
  *         reset values.
  * @param  SPIx: where x can be 0 or 1 to select the SPI peripheral.
  * @note   SPI2 is not available for CMS32F030x devices.
  * @retval None
  */
void SPI_DeInit(SSP_TypeDef* SPIx)
{
    if(SPIx == SSP0)
        SYSCON->APBCKEN &= ~(1<<9);
}

/**
  * @brief  Initializes the SPIx peripheral according to the specified 
  *         parameters in the SPI_InitTypeDef.
  * @param  SPIx: where x can be 0 to select the SPI peripheral.
  * @param  SPI_InitStruct: pointer to a SPI_InitTypeDef structure that
  *         contains the configuration information for the specified SPI peripheral.
  * @retval None
  */
void SPI_Init(SSP_TypeDef* SPIx, SPI_InitTypeDef* SPI_InitStruct)
{
    uint32_t spiReg = 0;
    
    assert_param(IS_SPI_MODE(SPI_InitStruct->SPI_Mode));
    
    spiReg = SPI_InitStruct->SPI_Mode | SPI_InitStruct->SPI_CPH | \
             SPI_InitStruct->SPI_CPO | SPI_InitStruct->SPI_DataSize;
    SPIx->CON = spiReg;
}

/*---------------------------------------------------------------------------------------------------------*/
/* Function:                                                                                               */
/*               SPI_SetClockFreq                                                                       */
/* Parameters:                                                                                             */
/*               eSpiPort - [in]  Specify the SPI port                                                     */
/*               u32Clock - [in]  Specify the SPI clock rate in Hz. It's the target clock rate of          */
/*                                SPI base clock and variable clock 1.                                     */
/* Returns:                                                                                                */
/*               The actual clock rate of SPI engine clock is returned.                                    */
/*               SPI engine clock rate = APB clock rate / ((M + 1) * N)  (N is an even value from 2 to 254)*/
/*               The actual clock rate may be different from the target SPI clock rate.                    */
/* Description:                                                                                            */
/*               Configure the SPI clock. Only for master mode.                                            */
/*---------------------------------------------------------------------------------------------------------*/
uint32_t SPI_SetClockFreq(SSP_TypeDef* SPIx, uint32_t u32Clock)
{
  uint32_t M, N, u32Div;

  if (u32Clock!=0)
  {
    if (u32Clock > SystemAPBClock)
    {
      M = 0;
      N = 2;
    }
    else
    {
      if ((SystemAPBClock / u32Clock) > 254)
      {
        M = (SystemAPBClock / u32Clock) / 254;
        N = SystemAPBClock / (u32Clock * (M + 1));
      }
      else
      {
        M = 0;
        N = (SystemAPBClock / u32Clock) & (~0x00000001);
      }
    }
  }
  else
  {
    M = 0xFF;
    N = 0xFF;
  }

  u32Div = (M << 8) | N;
  SPIx->CLK = u32Div;

  return ( SystemAPBClock / ((M + 1) * N));
}

/**
  * @brief  Fills each SPI_InitStruct member with its default value.
  * @param  SPI_InitStruct: pointer to a SPI_InitTypeDef structure which will be initialized.
  * @retval None
  */
void SPI_StructInit(SPI_InitTypeDef* SPI_InitStruct)
{
    SPI_InitStruct->SPI_Mode = SPI_Mode_Master;
    SPI_InitStruct->SPI_DataSize = SPI_DataSize_8b;
    SPI_InitStruct->SPI_CPH = SPI_CPH_1Edge;
    SPI_InitStruct->SPI_CPO = SPI_CPO_High;
    SPI_InitStruct->SPI_NSS = SPI_NSS_Hard;
}

/**
  * @brief  Enables or disables the specified SPI peripheral.
  * @param  SPIx: where x can be 0 to select the SPI peripheral.
  * @param  NewState: new state of the SPIx peripheral. 
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_Cmd(SSP_TypeDef* SPIx, FunctionalState NewState)
{
    if(NewState == ENABLE)
    {
        SPIx->CON |= 1<<10;
    }
    else
    {
        SPIx->CON &= ~(1<<10);
    }
}

/**
  * @brief  Configures the data size for the selected SPI.
  * @param  SPIx: where x can be 0 to select the SPI peripheral.
  * @param  SPI_DataSize: specifies the SPI data size.
  *         For the SPIx peripheral this parameter can be one of the following values:
  *            @arg SPI_DataSize_4b: Set data size to 4 bits
  *            @arg SPI_DataSize_5b: Set data size to 5 bits
  *            @arg SPI_DataSize_6b: Set data size to 6 bits
  *            @arg SPI_DataSize_7b: Set data size to 7 bits
  *            @arg SPI_DataSize_8b: Set data size to 8 bits
  *            @arg SPI_DataSize_9b: Set data size to 9 bits
  *            @arg SPI_DataSize_10b: Set data size to 10 bits
  *            @arg SPI_DataSize_11b: Set data size to 11 bits
  *            @arg SPI_DataSize_12b: Set data size to 12 bits
  *            @arg SPI_DataSize_13b: Set data size to 13 bits
  *            @arg SPI_DataSize_14b: Set data size to 14 bits
  *            @arg SPI_DataSize_15b: Set data size to 15 bits
  *            @arg SPI_DataSize_16b: Set data size to 16 bits
  * @retval None
  */
void SPI_DataSizeConfig(SSP_TypeDef* SPIx, uint16_t SPI_DataSize)
{
    assert_param(IS_SPI_DATA_SIZE(SPI_DataSize));
    
    SPIx->CON &= ~(0x0F);
    SPIx->CON |= SPI_DataSize;
}

/**
  * @brief  Configures internally by software the NSS pin for the selected SPI.
  * @note   This function can be called only after the SPI_Init() function has 
  *         been called.  
  * @param  SPIx: where x can be 0 to select the SPI peripheral.
  * @param  SPI_NSSInternal: specifies the SPI NSS internal state.
  *          This parameter can be one of the following values:
  *            @arg SPI_NSS_Soft: Set NSS pin internally
  *            @arg SPI_NSS_Hard: Reset NSS pin internally
  * @retval None
  */
void SPI_NSSInternalSoftwareConfig(SSP_TypeDef* SPIx, uint16_t SPI_NSSInternal)
{
    assert_param(IS_SPI_NSS(SPI_NSSInternal));

    if (SPI_NSSInternal != SPI_NSS_Hard)
    {
        SPIx->CSCR |= SPI_NSS_Soft;
    }
    else
    {
        SPIx->CSCR &= ~SPI_NSS_Soft;
    }
}

/**
  * @brief  Enables or disables the SS output for the selected SPI.
  * @note   This function can be called only after the SPI_Init() function has 
  *         been called and the NSS hardware management mode is selected. 
  * @param  SPIx: where x can be 0 to select the SPI peripheral.
  * @param  SPI_NssStatus: new state of the SPIx SS output. 
  *          This parameter can be one of the following values:
  *            @arg SPI_NSSInternalSoft_Low: Set NSS pin internally
  *            @arg SPI_NSSInternalSoft_High: Reset NSS pin internally
  * @retval None
  */
void SPI_SSOutputCmd(SSP_TypeDef* SPIx, uint32_t SPI_NssStatus)
{
    if(SPI_NssStatus == SPI_NSSInternalSoft_Low)
    {
        SPIx->CSCR &= ~SPI_NSSInternalSoft_High;
    }
    else
    {
        SPIx->CSCR |= SPI_NSSInternalSoft_High;
    }
}

/**
  * @brief  Transmits a Data through the SPIx/I2Sx peripheral.
  * @param  SPIx: where x can be 0 in SPI mode to select the SPI peripheral.
  * @param  Data: Data to be transmitted.
  * @retval None
  */
void SPI_SendDataNBit(SSP_TypeDef* SPIx, uint16_t Data)
{
    while(!((SPIx->STAT >> 1) & 0x01));
    SPIx->DAT = Data;
}

/**
  * @brief  Returns the most recent received data by the SPIx/I2Sx peripheral. 
  * @param  SPIx: where x can be 0 in SPI mode to select the SPI peripheral. 
  * @retval The value of the received data.
  */
uint16_t SPI_ReceiveDataNBit(SSP_TypeDef* SPIx)
{
    while(!((SPIx->STAT>>2) & 0x01));
    return SPIx->DAT;
}

/**
  * @brief  Enables or disables the specified SPI/I2S interrupts.
  * @param  SPIx: where x can be 0 in SPI mode or 1 in I2S mode to select 
  *         the SPI peripheral.  
  * @param  SPI_IT: this parameter can be one of the following values:
  *            @arg SPI_IT_TxHalfEmpt: Transmit FIFO Interrupt 
  *            @arg SPI_IT_RxHalfFull: Receive FIFO Interrupt
  *            @arg SPI_IT_OverTim   : Receive Timeout Interrupt
  *            @arg SPI_IT_OverRun   : Receive Overrun Interrupt
  * @param  NewState: new state of the SPIx peripheral. 
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SPI_ITConfig(SSP_TypeDef* SPIx, uint8_t SPI_IT, FunctionalState NewState)
{
    if(NewState == ENABLE)
    {
        SPIx->IMSC |= SPI_IT;
    }
    else
    {
        SPIx->IMSC &= ~(SPI_IT);
    }
}

/**
  * @brief  Checks whether the specified SPI flag is set or not.
  * @param  SPIx: where x can be 0 in SPI mode to select 
  *         the SPI peripheral.    
  * @param  SPI_FLAG: specifies the SPI flag to check. 
  *          This parameter can be one of the following values:
  *            @arg SPI_STAT_TFE: Transmit FIFO Empty flag.
  *            @arg SPI_STAT_TNF: Transmit FIFO Not Full flag.
  *            @arg SPI_STAT_RNE: Receive FIFO Not Empty flag.
  *            @arg SPI_STAT_RFF: Receive FIFO Full flag.
  *            @arg SPI_STAT_BSY: Busy flag.
  * @retval The new state of SPI_I2S_FLAG (SET or RESET).
  */
FlagStatus SPI_GetFlagStatus(SSP_TypeDef* SPIx, uint16_t SPI_FLAG)
{
    FlagStatus bitStatus = RESET;
    if((SPIx->STAT & SPI_FLAG) != RESET)
    {
        bitStatus = SET;
    }
    else
    {
        bitStatus = RESET;
    }
    return bitStatus;
}

/**
  * @brief  Clears the SPIx MIS flag.
  * @param  SPIx  : where x can be 0 to select the SPI peripheral.
  * @param  SPI_IT: specifies the SPI flag to clear. 
  *         This function clears only CRCERR flag.

  * @param  SPI_IT: specifies the SPI flag to check. 
  *          This parameter can be one of the following values:
  *            @arg SPI_ICLR_RORIC: frame was received when Rx FIFO was full” interrupt
  *            @arg SPI_ICLR_RTIC : clears the Rx FIFO was not 
  *                 empty and has not been read for a timeout 
  *                 period interrupt
  * @retval None
  */
void SPI_ClearITFlag(SSP_TypeDef* SPIx, uint16_t SPI_IT)
{
    SPIx->ICLR |= SPI_IT;
}

/**
  * @brief  Checks whether the specified SPI interrupt has occurred or not.
  * @param  SPIx: where x can be 0 in SPI mode to select 
  *         the SPI peripheral.
  * @param  SPI_IT: specifies the SPI interrupt source to check. 
  *          This parameter can be one of the following values:
  *            @arg SPI_IT_TxHalfEmpt: Transmit FIFO Interrupt 
  *            @arg SPI_IT_RxHalfFull: Receive FIFO Interrupt
  *            @arg SPI_IT_OverTim   : Receive Timeout Interrupt
  *            @arg SPI_IT_OverRun   : Receive Overrun Interrupt
  * @retval The new state of SPI_I2S_IT (SET or RESET).
  */
ITStatus SPI_GetITStatus(SSP_TypeDef* SPIx, uint8_t SPI_IT)
{
    FlagStatus bitStatus = RESET;
    if((SPIx->MIS & SPI_IT) != RESET)
    {
        bitStatus = SET;
    }
    else
    {
        bitStatus = RESET;
    }
    return bitStatus;
}

/**
  * @}
  */

