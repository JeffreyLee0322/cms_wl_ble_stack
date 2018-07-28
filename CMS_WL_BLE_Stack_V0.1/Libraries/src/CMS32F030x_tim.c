#include "CMS32F030x_tim.h"

/**
  * @brief  Deinitializes the TIMx peripheral registers to their default reset values.
  * @param  TIMx: where x can be 0 or 1 to select the TIM peripheral.
  * @retval None
  *   
  */
void TIM_DeInit(TIMER_TypeDef* TIMx)
{
    SYS_APBPeriphClockCmd(SYS_APB_TIMER01CE,DISABLE);
}

/**
  * @brief  Initializes the TIMx Time Base Unit peripheral according to 
  *         the specified parameters in the TIM_TimeBaseInitStruct.
  * @param  TIMx: where x can be 0 or 1 to select the TIM 
  *         peripheral.
  * @param  TIM_TimeBaseInitStruct: pointer to a TIM_TimeBaseInitTypeDef
  *         structure that contains the configuration information for
  *         the specified TIM peripheral.
  * @retval None
  */
void TIM_TimeBaseInit(TIMER_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct)
{
    uint32_t regtmp = 0;
    
    if(TIM_TimeBaseInitStruct->TIM_Mode != TIM_CountMode_FreeRun)
    {
        regtmp |= TIM_CountMode_FreeRun;
    }
    else
    {
        regtmp &= ~TIM_CountMode_FreeRun;
    }
    
    if(TIM_TimeBaseInitStruct->TIM_ContOption == TIM_CountOperation32)
    {
        regtmp |= TIM_CountOperation32;
    }
    else
    {
        regtmp &= ~TIM_CountOperation32;
    }
    
    if(TIM_TimeBaseInitStruct->TIM_OneShotMode == TIM_OneShotMode_OneShot)
    {
        regtmp |= TIM_OneShotMode_OneShot;
    }
    else
    {
        regtmp &= ~TIM_OneShotMode_OneShot;
    }
   
    regtmp |= TIM_TimeBaseInitStruct->TIM_Prsc;
    TIMx->CON =regtmp;
}

/**
  * @brief  Fills each TIM_TimeBaseInitStruct member with its default value.
  * @param  TIM_TimeBaseInitStruct: pointer to a TIM_TimeBaseInitTypeDef structure
  *         which will be initialized.
  * @retval None
  */
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct)
{
    TIM_TimeBaseInitStruct->TIM_ContOption  = TIM_CountOperation16;
    TIM_TimeBaseInitStruct->TIM_Mode        = TIM_CountMode_FreeRun;
    TIM_TimeBaseInitStruct->TIM_OneShotMode = TIM_OneShotMode_Wrapping;
    TIM_TimeBaseInitStruct->TIM_Prsc        = TIM_Prescale_Div1;
}

/**
  * @brief  Configures the TIMx Prescaler.
  * @param  TIMx: where x can be 0 or 1 to select the TIM peripheral.
  * @param  Prescaler: specifies the Prescaler Register value
  *         This parameter can be one of the following values:
  *             @arg TIM_Prescale_Div1:     Clock is divided by 1
  *             @arg TIM_Prescale_Div16:    Clock is divided by 16
  *             @arg TIM_Prescale_Div256:   Clock is divided by 256
  * @retval None
  */
void TIM_PrescalerConfig(TIMER_TypeDef* TIMx, uint32_t Prescaler)
{
    TIMx->CON &= ~(3<<2);
    TIMx->CON |= Prescaler;
}

/**
  * @brief  Sets the TIMx Load Counter Register value
  * @param  TIMx: where x can be 0 or 1 to select the TIM 
  *          peripheral.
  * @param  Counter: specifies the Counter register new value.
  *       @arg 16-bit mode :0-2^16
  *       @arg 32-bit mode :0-2^32
* @retval None
  */
void TIM_SetCounter(TIMER_TypeDef* TIMx, uint32_t Counter)
{
    TIMx->LOAD = Counter;
}

/**
  * @brief  Sets the TIMx Background Load Counter Register value
  * @param  TIMx: where x can be 0 or 1 to select the TIM 
  *          peripheral.
  * @param  Counter: specifies the Counter register new value.
  *       @arg 16-bit mode :0-2^16
  *       @arg 32-bit mode :0-2^32
* @retval None
  */
void TIM_SetBGCounter(TIMER_TypeDef* TIMx, uint32_t Counter)
{
    TIMx->BGLOAD = Counter;
}

/**
  * @brief  Gets the TIMx Counter value.
  * @param  TIMx: where x can be 0 or 1 to select the TIM 
  *         peripheral.
  * @retval Counter Register value.
  */
uint32_t TIM_GetCounter(TIMER_TypeDef* TIMx)
{
    return TIMx->LOAD;
}

/**
  * @brief  Gets the TIMx Background Counter value.
  * @param  TIMx: where x can be 0 or 1 to select the TIM 
  *         peripheral.
  * @retval Counter Register value.
  */
uint32_t TIM_GetBGCounter(TIMER_TypeDef* TIMx)
{
    return TIMx->BGLOAD;
}

/**
  * @brief  Gets the TIMx Prescaler value.
  * @param  TIMx: where x can be 0 or 1 to select the TIM 
  *         peripheral.
  * @retval Prescaler Register value.
  *         @arg TIM_Prescale_Div1  :Clock div 1
  *         @arg TIM_Prescale_Div16 :Clock div 16
  *         @arg TIM_Prescale_Div256:Clock div 256
  */
uint16_t TIM_GetPrescaler(TIMER_TypeDef* TIMx)
{
    return ((TIMx->CON >> 2) &0x03);
}

/**
  * @brief  Enables or disables the specified TIM peripheral.
  * @param  TIMx: where x can be 0 or 1 to select the TIMx
  *         peripheral.
  * @param  NewState: new state of the TIMx peripheral.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_Cmd(TIMER_TypeDef* TIMx, FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        TIMx->CON |= TIM_TMREN_Eable;
    }
    else
    {
        TIMx->CON &= ~TIM_TMREN_Disable;
    }
}

/**
  * @brief  Enables or disables the specified TIM interrupts.
  * @param  TIMx: where x can be 0 or 1 to select the TIMx peripheral.
  * @param  NewState: new state of the TIM interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void TIM_ITConfig(TIMER_TypeDef* TIMx,FunctionalState NewState)
{
    if(NewState != DISABLE)
    {
        TIMx->CON |= 1<<5;
    }
    else
    {
        TIMx->CON &= ~(1<<5);
    }
}

/**
  * @brief  Checks TIM interrupt has occurred or not.
  * @param  TIMx: where x can be 0 or 1 to select the TIM peripheral.
  * @retval The new state of the ITStatus(SET or RESET).
  */
ITStatus TIM_GetITStatus(TIMER_TypeDef* TIMx)
{
    ITStatus status = RESET;
    
    if(TIMx->MIS & 0x01)
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
  * @brief  Clears the TIMx's interrupt pending bits.
  * @param  TIMx: where x can be 0 or 1 to select the TIM peripheral.
  * @retval None
  */
void TIM_ClearITPendingBit(TIMER_TypeDef* TIMx)
{
    TIMx->ICLR = TIMx->MIS;
}
