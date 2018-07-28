#include "CMS32F030x_gpio.h"


/**
  * @brief  Deinitializes the GPIOx peripheral registers to their default reset 
  *         values.
  * @param  GPIOx: where x can be (0, 1, 2, 3, or 4) to select the GPIO peripheral.
  * @retval None
  */
void GPIO_DeInit(GPIO_TypeDef* GPIOx)
{
   GPIOx->PMS = 0x00000000; 
}

/**
  * @brief  Initializes the GPIOx peripheral according to the specified 
  *         parameters in the GPIO_InitStruct.
  * @param  GPIOx: where x can be (0, 1, 2, 3, or 4) to select the GPIO peripheral.
  * @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure that contains
  *         the configuration information for the specified GPIO peripheral.
  * @retval None
  */
void GPIO_Init(GPIO_TypeDef* GPIOx,GPIO_InitTypeDef* GPIO_InitStruct)
{
    uint8_t i=0;
    
    for(i=0;i<8;i++)
    {
        if(GPIO_InitStruct->GPIO_Pin & (1<<i))
        {
            GPIOx->PMS &= ~(7<<(i* 4));
            GPIOx->PMS |= GPIO_InitStruct->GPIO_Mode << (i* 4);
            if(GPIO_InitStruct->GPIO_DrvCur == GPIO_DrvCur_Large)
                GPIOx->DR &= ~(1<<i);
            else
                GPIOx->DR |= 1<<i;
            
            if(GPIO_InitStruct->GPIO_OutRate == GPIO_OutRate_Fast)
                GPIOx->SR &= ~(1<<i);
            else
                GPIOx->SR |= 1<<i;
        }
    }
}

/**
  * @brief  Fills each GPIO_InitStruct member with its default value.
  * @param  GPIO_InitStruct: pointer to a GPIO_InitTypeDef structure which will 
  *         be initialized.
  * @retval None
  */
void GPIO_StructInit(GPIO_InitTypeDef* GPIO_InitStruct)
{
    GPIO_InitStruct->GPIO_Pin   =   0xFF;
    GPIO_InitStruct->GPIO_Mode  =   GPIO_Mode_IN_FLOATING;   
}

/**
  * @brief  GPIO peripheral input filter enable or disable config.
  * @param  GPIOx: where x can be (0, 1, 2, 3, or 4) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         For CMS32F030x: (0..7) for GPIO0, GPIO1,GPIO2,GPIO3,GPIO4.
  * @param  NewStatus:This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void GPIO_InputFit(GPIO_TypeDef* GPIOx,uint8_t GPIO_Pin,FunctionalState NewStatus)
{
    if(NewStatus == ENABLE)
    {
        GPIOx->DIDB |= GPIO_Pin;
    }else
    {
        GPIOx->DIDB &= ~GPIO_Pin;
    }
}

/**
  * @brief  Reads the specified input port pin.
  * @param  GPIOx: where x can be (0, 1, 2, 3, or 4) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to read.
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         For CMS32F030x: (0..7) for GPIO0, GPIO1,GPIO2,GPIO3,GPIO4.
  * @retval The input port pin value.
  */
uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint8_t GPIO_Pin)
{
    BitAction bit = Bit_RESET;
    if(GPIOx->DI & GPIO_Pin)
    {
        bit = Bit_SET;
    }
    else
    {
        bit = Bit_RESET;
    }
    return bit;
}

/**
  * @brief  Reads the specified input port pin.
  * @param  GPIOx: where x can be (0, 1, 2, 3, or 4) to select the GPIO peripheral.
  * @retval The input port pin value.
  */
uint8_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx)
{
    return (uint8_t)GPIOx->DI;
}

/**
  * @brief  Reads the specified output data port bit.
  * @param  GPIOx: where x can be (0, 1, 2, 3, or 4) to select the GPIO peripheral.
  * @param  GPIO_Pin: Specifies the port bit to read.
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         For CMS32F030x: (0..7) for GPIO0, GPIO1,GPIO2,GPIO3,GPIO4.
  * @retval The output port pin value.
  */
uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint8_t GPIO_Pin)
{
    BitAction bit = Bit_RESET;
    if(GPIOx->DO & GPIO_Pin)
    {
        bit = Bit_SET;
    }
    else
    {
        bit = Bit_RESET;
    }
    return bit;
}

/**
  * @brief  Reads the specified GPIO output data port.
  * @param  GPIOx: where x can be (0, 1, 2, 3, or 4) to select the GPIO peripheral.
  * @retval GPIO output data port value.
  */
uint8_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
{
    return (uint8_t)GPIOx->DO;
}

/**
  * @brief  Sets the selected data port bits.
  * @param  GPIOx: where x can be (0, 1, 2, 3, or 4) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         For CMS32F030x: (0..7) for GPIO0, GPIO1,GPIO2,GPIO3,GPIO4.
  * @retval None
  */
void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint8_t GPIO_Pin)
{
    GPIOx->DOSET = GPIO_Pin;
}

/**
  * @brief  Clears the selected data port bits.
  * @param  GPIOx: where x can be (0, 1, 2, 3, or 4) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bits to be written.
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         For CMS32F030x: (0..7) for GPIO0, GPIO1,GPIO2,GPIO3,GPIO4.
  * @retval None
  */
void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint8_t GPIO_Pin)
{
    GPIOx->DOCLR = GPIO_Pin;
}

/**
  * @brief  Sets or clears the selected data port bit.
  * @param  GPIOx: where x can be (0, 1, 2, 3, or 4) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         For CMS32F030x: (0..7) for GPIO0, GPIO1,GPIO2,GPIO3,GPIO4.

  * @param  BitVal: specifies the value to be written to the selected bit.
  *          This parameter can be one of the BitAction enumeration values:
  *            @arg Bit_RESET: to clear the port pin
  *            @arg Bit_SET: to set the port pin
  * @retval None
  */
void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint8_t GPIO_Pin, BitAction BitVal)
{
    if(BitVal == Bit_SET)
    {
        GPIOx->DO |= GPIO_Pin;
    }
    else
    {
        GPIOx->DO &= ~(GPIO_Pin);
    }
}

/**
  * @brief  Writes data to the specified GPIO data port.
  * @param  GPIOx: where x can be (0, 1, 2, 3, or 4) to select the GPIO peripheral.
  * @param  PortVal: specifies the value to be written to the port output data register.
  * @retval None
  */
void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal)
{
    GPIOx->DO = PortVal;
}

/**
  * @brief  GPIO peripheral interrupt config.
  * @param  GPIOx: where x can be (0, 1, 2, 3, or 4) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         For CMS32F030x: (0..7) for GPIO0, GPIO1,GPIO2,GPIO3,GPIO4.
  * @param  GPIO_IntType:pointer to a GPIO_INTType structure that contains
  *         the configuration information for the specified GPIO interrupt peripheral.
  * @retval None
  */
void GPIO_ITConfig(GPIO_TypeDef* GPIOx,uint8_t GPIO_Pin,GPIO_INTType* GPIO_IntType)
{
    if(GPIO_IntType->IntMode == GPIO_IntMode_Level)
    {
        GPIOx->ITYPE |= GPIO_Pin;
    }
    else
    {
        GPIOx->ITYPE &= ~GPIO_Pin;
    }
    if(GPIO_IntType->IntVal == GPIO_IntVal_HighOrRis)
    {
        GPIOx->IVAL |= GPIO_Pin;
    }
    else
    {
        GPIOx->IVAL &= ~GPIO_Pin;
    }
    if(GPIO_IntType->IntEdge == GPIO_IntEdge_Any)
    {
        GPIOx->IANY |= GPIO_Pin;
    }
    else
    {
        GPIOx->IANY &= ~GPIO_Pin;
    }
}

/**
  * @brief  GPIO peripheral interrupt enable or disable config.
  * @param  GPIOx: where x can be (0, 1, 2, 3, or 4) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         For CMS32F030x: (0..7) for GPIO0, GPIO1,GPIO2,GPIO3,GPIO4.
  * @param  NewStatus:This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void GPIO_ITCmd(GPIO_TypeDef* GPIOx,uint8_t GPIO_Pin,FunctionalState NewStatus)
{
    if(NewStatus == ENABLE)
    {
        GPIOx->IMSC |= GPIO_Pin;
    }
    else
    {
        GPIOx->IMSC &= ~GPIO_Pin;
    }
}

/**
  * @brief  Get GPIO peripheral interrupt status value.
  * @param  GPIOx: where x can be (0, 1, 2, 3, or 4) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         For CMS32F030x: (0..7) for GPIO0, GPIO1,GPIO2,GPIO3,GPIO4.
  * @retval BitAction:the pin interrupt statue
  */
BitAction GPIO_GetITSource(GPIO_TypeDef* GPIOx,uint8_t GPIO_Pin)
{
    BitAction status = Bit_RESET;
    
    if(GPIOx->MIS & GPIO_Pin)
    {
        status = Bit_SET;
    }
    else
    {
        status = Bit_RESET;
    }
    return status;
}

/**
  * @brief  Get GPIO peripheral interrupt status value.
  * @param  GPIOx: where x can be (0, 1, 2, 3, or 4) to select the GPIO peripheral.
  * @param  GPIO_Pin: specifies the port bit to be written.
  * @note   This parameter can be GPIO_Pin_x where x can be:
  *         For CMS32F030x: (0..7) for GPIO0, GPIO1,GPIO2,GPIO3,GPIO4.
  * @retval BitAction:the pin interrupt statue
  */
void GPIO_ITClear(GPIO_TypeDef* GPIOx,uint8_t GPIO_Pin)
{
   GPIOx->ICLR = GPIO_Pin; 
}
