#include "CMS32F030x_wdt.h"

void WDT_Unlock(void)
{
		while(WDT->LOCK!=0X01)
		{
    	WDT->LOCK = 0x55aa6699;
  	}	
}

void WDT_Lock(void)
{
    WDT->LOCK = ((0x2AD5334C << 1) + 0); 
}

/**
  * @brief  Deinitializes the WDT peripheral registers to their default reset values.
  * @param  None
  * @retval None
  */
void WDT_DeInit(void)
{
	WDT_Unlock();
    WDT->CON = 0x5A00;
    WDT_Lock();
}


void WDT_Init(WDT_TypeDef* WDTx,WDT_InitStructTypeDef* WDT_InitType)
{
    WDT_Unlock();
    if(WDT_InitType->WDT_Reset == ENABLE)
    {
        WDTx->CON = WDT_InitType->WDT_PrescleDiv | WDT_InitType->WDT_ITEnable;
    }else
    {
        WDTx->CON = WDT_InitType->WDT_PrescleDiv | WDT_InitType->WDT_ITEnable | 0x5A00;
    }
    WDTx->LOAD = WDT_InitType->WDT_LoadValue;
    WDT_Lock();
}

/**
  * @brief  Enables or disables WDT reset CPU.
  * @param  NewState: new state of the TIMx peripheral.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void WDT_SetEnableReset(FunctionalState newstatus)
{
    WDT_Unlock();
    if(newstatus == ENABLE)
        WDT->CON &= ~(0xFF << 8);
    else
        WDT->CON |= 0x5A << 8;
    WDT_Lock();  
}

/**
  * @brief  Configures the WDT Prescaler.
  * @param  WDT_Prescaler: specifies the Prescaler Register value
  *           @arg WDT_Prescaler_1:Clock is divided by 1
  *           @arg WDT_Prescaler_16:Clock is divided by 16
  *           @arg WDT_Prescaler_256:Clock is divided by 256
  * @retval None
  */
void WDT_SetPrescaler(uint32_t WDT_Prescaler)
{
    WDT_Unlock();
    WDT->CON &= (3<<2);
    WDT->CON |= WDT_Prescaler;
    WDT_Lock(); 
}
/**
  * @brief  Configures the WDT LOAD value.
  * @param  Counter: specifies the LOAD Register value
  * @retval None
  */
void WDT_SetCounter(uint32_t Counter)
{
    WDT_Unlock();
    WDT->LOAD = Counter;
    WDT_Lock(); 
}


/**
  * @brief  Enables or disables the specified WDT interrupts.
  * @param  NewState: new state of the WDT interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void WDT_ITConfig(FunctionalState newstatus)
{
    WDT_Unlock();
    if(newstatus == ENABLE)
        WDT->CON |= 0x01;
    else
        WDT->CON &= ~(1<<0);
    WDT_Lock(); 
}


/**
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */

void WDT_DebugStop(FunctionalState newstatus)
{
    WDT_Unlock();
    if(newstatus == ENABLE)
				WDT->CON &= ~(1<<16);
    else
        WDT->CON |= (1<<16);
    WDT_Lock(); 
}


/**
  * @brief  Checks WDT interrupt has occurred or not.
  * @retval The new state of the ITStatus(SET or RESET).
  */
ITStatus WDT_GetITStatus(void)
{
    ITStatus status = RESET;
    if(WDT->MIS & 0x01)
        status = SET;
    else
        status = RESET;
    return status;
}

/**
  * @brief  Clears the WDT interrupt pending bits.
  * @retval None
  */
void WDT_ClearITPendingBit(void)
{
    WDT_Unlock();
    WDT->ICLR = 0x55AA55AA;
    WDT_Lock(); 
}


