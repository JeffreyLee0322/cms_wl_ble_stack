#include "CMS32F030x_adc.h"


/**
  * @brief  Deinitializes ADC1 peripheral registers to their default reset values.
  * @param  ADCx: where x can be 1 to select the ADC peripheral.
  * @retval None
  */
void ADC_DeInit(ADC_TypeDef* ADCx)
{
    SYSCON->APBCKEN &= ~SYS_APB_ADCCE;
}

/**
  * @brief  Initializes the ADC peripheral according to the specified parameters
  *         in the ADC_InitStruct.
  * @note   This function is used to configure the global features of the ADC ( 
  *         ADC clock,continuous mode activation).   
  * @param  ADCx: where ADCx can be ADC to select the ADC peripheral.
  * @param  ADC_InitStruct: pointer to an ADC_InitTypeDef structure that contains 
  *         the configuration information for the specified ADC peripheral.
  * @retval None
  */
void ADC_Init(ADC_TypeDef* ADCx, ADC_InitStructTypeDef* ADC_InitStruct)
{   
    uint32_t conreg = 0;
    conreg = ADC_InitStruct->ADC_ADCMS | ADC_InitStruct->ADC_ADCDIV;
    ADCx->CON = conreg;
}

/**
  * @brief  Fills each ADC_InitStruct member with its default value.
  * @note   This function is used to initialize the global features of the ADC ( 
  *         Resolution, Data Alignment, continuous mode activation, External 
  *         trigger source and edge, Sequence Scan Direction).
  * @param  ADC_InitStruct: pointer to an ADC_InitTypeDef structure which will 
  *         be initialized.
  * @retval None
  */
void ADC_StructInit(ADC_InitStructTypeDef* ADC_InitStruct)
{
    ADC_InitStruct->ADC_ADCDIV = 5;
    ADC_InitStruct->ADC_ADCMS = ADC_CON_ADCMSOne;
}

/**
  * @brief  Enables or disables the specified ADC peripheral.
  * @param  ADCx: where ADCx can be ADC to select the ADC peripheral.
  * @param  NewState: new state of the ADCx peripheral. 
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_Cmd(ADC_TypeDef* ADCx,FunctionalState NewStatus)
{
    if(NewStatus != DISABLE)
    {
        ADCx->CON |= 1<<4;
    }
    else
    {
        ADCx->CON &= ~(1<<4);
    }
}

/**
  * @brief  Configures for the selected ADC.
  * @param  ADCx: where ADCx can be ADC to select the ADC peripheral.
  * @param  ADC_Channel: the ADC channel to configure. 
  *          This parameter can be any combination of the following values:
  *            @arg ADC_Channel_0: ADC Channel0 selected
  *            @arg ADC_Channel_1: ADC Channel1 selected
  *            @arg ADC_Channel_2: ADC Channel2 selected
  *            @arg ADC_Channel_3: ADC Channel3 selected
  *            @arg ADC_Channel_4: ADC Channel4 selected
  *            @arg ADC_Channel_5: ADC Channel5 selected
  *            @arg ADC_Channel_6: ADC Channel6 selected
  *            @arg ADC_Channel_7: ADC Channel7 selected
  *            @arg ADC_Channel_8: ADC Channel8 selected
  *            @arg ADC_Channel_9: ADC Channel9 selected
  *            @arg ADC_Channel_10: ADC Channel10 selected
  *            @arg ADC_Channel_11: ADC Channel11 selected
  *            @arg ADC_Channel_12: ADC Channel12 selected
  *            @arg ADC_Channel_13: ADC Channel13 selected
  *            @arg ADC_Channel_14: ADC Channel14 selected
  *            @arg ADC_Channel_15: ADC Channel15 selected
  * @param  NewState: new state of the ADCx cahnnel. 
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_ChannelConfig(ADC_TypeDef* ADCx,uint32_t ADC_Channel,FunctionalState NewStatus)
{
    if(NewStatus != DISABLE)
    {
        ADCx->SCAN |= 1<<ADC_Channel;
    }
    else
    {
        ADCx->SCAN &= ~(1<<ADC_Channel);
    }
}

/**
  * @brief  Stop the on going conversions for the selected ADC.
  * @note   When ADSTP is set, any on going conversion is aborted, and the ADC 
  *         data register is not updated with current conversion. 
  * @param  ADCx: where ADCx can be ADC to select the ADCx peripheral.
  * @retval None
  */
void ADC_StopOfConversion(ADC_TypeDef* ADCx)
{
    ADCx->SCAN &= ~(1<<16);
}

/**
  * @brief  Start Conversion for the selected ADC channels.
  * @param  ADCx: where ADCx can be ADC to select the ADCx peripheral.
  * @retval None
  */
void ADC_StartOfConversion(ADC_TypeDef* ADCx)
{
    ADCx->SCAN |= 1<<16;
}

/**
  * @brief  Returns the conversion status of select channel.
  * @param  ADCx: where ADCx can be ADC to select the ADCx peripheral.
  * @retval The Data conversion status,if complete return SET.
  */
FlagStatus ADC_GetConversionStatus(ADC_TypeDef* ADCx,uint32_t ADC_Channel)
{
    FlagStatus bitstatus = RESET;
    
    if(ADCx->RIS & (1<<ADC_Channel))
    {
        bitstatus = SET;
    }
    else
    {
        bitstatus = RESET;
    }
    return bitstatus;
}

/**
  * @brief  Returns the last ADCx conversion result data for ADC channel.  
  * @param  ADCx: where ADCx can be ADC to select the ADCx peripheral.
  * @param  ADC_Channel:The number of channel you want to get
  *          This parameter can be any combination of the following values:
  *            @arg ADC_Channel_0: ADC Channel0 selected
  *            @arg ADC_Channel_1: ADC Channel1 selected
  *            @arg ADC_Channel_2: ADC Channel2 selected
  *            @arg ADC_Channel_3: ADC Channel3 selected
  *            @arg ADC_Channel_4: ADC Channel4 selected
  *            @arg ADC_Channel_5: ADC Channel5 selected
  *            @arg ADC_Channel_6: ADC Channel6 selected
  *            @arg ADC_Channel_7: ADC Channel7 selected
  *            @arg ADC_Channel_8: ADC Channel8 selected
  *            @arg ADC_Channel_9: ADC Channel9 selected
  *            @arg ADC_Channel_10: ADC Channel10 selected
  *            @arg ADC_Channel_11: ADC Channel11 selected
  *            @arg ADC_Channel_12: ADC Channel12 selected
  *            @arg ADC_Channel_13: ADC Channel13 selected
  *            @arg ADC_Channel_14: ADC Channel14 selected
  *            @arg ADC_Channel_15: ADC Channel15 selected
  * @retval The Data conversion value.
  */
uint16_t ADC_GetConversionValue(ADC_TypeDef* ADCx,uint32_t ADC_Channel)
{
    uint16_t tmp=0;
    tmp = ADCx->DAT[ADC_Channel];
    ADCx->ICLR |= 1<<ADC_Channel;
    return tmp;
}

/**
  * @brief  Enables or disables the specified ADC channel interrupts.
  * @param  ADCx: where ADCx can be ADC to select the ADC peripheral.
  * @param  ADC_Channel: The number of channel you want set interrupt.
  *          This parameter can be any combination of the following values:
  *            @arg ADC_Channel_0: ADC Channel0 selected
  *            @arg ADC_Channel_1: ADC Channel1 selected
  *            @arg ADC_Channel_2: ADC Channel2 selected
  *            @arg ADC_Channel_3: ADC Channel3 selected
  *            @arg ADC_Channel_4: ADC Channel4 selected
  *            @arg ADC_Channel_5: ADC Channel5 selected
  *            @arg ADC_Channel_6: ADC Channel6 selected
  *            @arg ADC_Channel_7: ADC Channel7 selected
  *            @arg ADC_Channel_8: ADC Channel8 selected
  *            @arg ADC_Channel_9: ADC Channel9 selected
  *            @arg ADC_Channel_10: ADC Channel10 selected
  *            @arg ADC_Channel_11: ADC Channel11 selected
  *            @arg ADC_Channel_12: ADC Channel12 selected
  *            @arg ADC_Channel_13: ADC Channel13 selected
  *            @arg ADC_Channel_14: ADC Channel14 selected
  *            @arg ADC_Channel_15: ADC Channel15 selected
  * @param  NewState: new state of the specified ADC interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void ADC_ITConfig(ADC_TypeDef* ADCx, uint32_t ADC_Channel, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        ADCx->IMSC |= 1<<ADC_Channel;
    }
    else
    {
        ADCx->IMSC &= 1<<ADC_Channel;
    }
}

/**
  * @brief  Checks whether the specified ADC channel interrupt has occurred or not.
  * @param  ADCx: where ADCx can be ADC to select the ADC peripheral
  * @param  ADC_Channel: specifies the ADC channel interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg ADC_Channel_0: ADC Channel0 selected
  *            @arg ADC_Channel_1: ADC Channel1 selected
  *            @arg ADC_Channel_2: ADC Channel2 selected
  *            @arg ADC_Channel_3: ADC Channel3 selected
  *            @arg ADC_Channel_4: ADC Channel4 selected
  *            @arg ADC_Channel_5: ADC Channel5 selected
  *            @arg ADC_Channel_6: ADC Channel6 selected
  *            @arg ADC_Channel_7: ADC Channel7 selected
  *            @arg ADC_Channel_8: ADC Channel8 selected
  *            @arg ADC_Channel_9: ADC Channel9 selected
  *            @arg ADC_Channel_10: ADC Channel10 selected
  *            @arg ADC_Channel_11: ADC Channel11 selected
  *            @arg ADC_Channel_12: ADC Channel12 selected
  *            @arg ADC_Channel_13: ADC Channel13 selected
  *            @arg ADC_Channel_14: ADC Channel14 selected
  *            @arg ADC_Channel_15: ADC Channel15 selected
  * @retval The I state of ITStatus (SET or RESET).
  */
ITStatus ADC_GetITStatus(ADC_TypeDef* ADCx, uint32_t ADC_Channel)
{
    ITStatus itstatus = RESET;
    
    if(ADCx->MIS & (1<<ADC_Channel))
    {
        itstatus = SET;
    }
    else
    {
        itstatus = RESET;
    }
    return itstatus;
}

/**
  * @brief  Clears the ADCx's interrupt pending bits.
  * @param  ADCx: where x can be 1 to select the ADC1 peripheral.
  * @param  ADC_Channel: specifies the ADC channel interrupt source to check.
  *          This parameter can be one of the following values:
  *            @arg ADC_Channel_0: ADC Channel0 selected
  *            @arg ADC_Channel_1: ADC Channel1 selected
  *            @arg ADC_Channel_2: ADC Channel2 selected
  *            @arg ADC_Channel_3: ADC Channel3 selected
  *            @arg ADC_Channel_4: ADC Channel4 selected
  *            @arg ADC_Channel_5: ADC Channel5 selected
  *            @arg ADC_Channel_6: ADC Channel6 selected
  *            @arg ADC_Channel_7: ADC Channel7 selected
  *            @arg ADC_Channel_8: ADC Channel8 selected
  *            @arg ADC_Channel_9: ADC Channel9 selected
  *            @arg ADC_Channel_10: ADC Channel10 selected
  *            @arg ADC_Channel_11: ADC Channel11 selected
  *            @arg ADC_Channel_12: ADC Channel12 selected
  *            @arg ADC_Channel_13: ADC Channel13 selected
  *            @arg ADC_Channel_14: ADC Channel14 selected
  *            @arg ADC_Channel_15: ADC Channel15 selected
  * @retval None
  */
void ADC_ClearITPendingBit(ADC_TypeDef* ADCx, uint32_t ADC_Channel)
{
    ADCx->ICLR |= 1<<ADC_Channel;
}

