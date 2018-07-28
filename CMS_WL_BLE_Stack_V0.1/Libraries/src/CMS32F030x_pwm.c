#include "CMS32F030x_pwm.h"

/**
  * @brief  Deinitializes the PWMx peripheral registers to their default reset values.
  * @param  None;
  * @retval None
  */
void PWM_DeInit(void)
{
    SYSCON->APBCKEN &= ~SYS_APB_PWMCE;
}

/**
  * @brief  Initializes the PWMx peripheral according to 
  *         the specified parameters in the PWM_BaseStructTypeDef.
  * @param  PWMx: where x can be 0 or 1 to select the PWM
  *         peripheral.
  * @param  PWM_BaseStruct: pointer to a PWM_BaseStructTypeDef
  *         structure that contains the configuration information for
  *         the specified TIM peripheral.
  * @retval None
  */
void PWM_Init(uint8_t PWMx,PWM_BaseStructTypeDef* PWM_BaseStruct)
{
    uint32_t conreg = 0;
    
    conreg = PWM_BaseStruct->PWM_Prescale | PWM_BaseStruct->PWM_Select | \
             PWM_BaseStruct->PWM_CaptureModeSelect | PWM_BaseStruct->PWM_CaptureChannelSelect |\
             (1<<6);
    

    switch(PWMx)
    {
        case PWM0 :{
            PWM->CON0 = conreg;
        }break;
        
        case PWM1 :{
            PWM->CON1 = conreg;
        }break;
 /*       
        case PWM2 :{
            PWM->CON2 = conreg;
        }break;
        
        case PWM3 :{
            PWM->CON3 = conreg;
        }break;
*/        
        default :
            break;
    }
}

/**
  * @brief  Initializes the PWMx peripheral according to 
  *         the specified parameters in the PWM_BaseStructTypeDef.
  * @param  PWM_BaseStruct: pointer to a PWM_BaseStructTypeDef
  *         structure that contains the configuration information for
  *         the specified TIM peripheral.
  * @retval None
  */
void PWM_BaseStructInit(PWM_BaseStructTypeDef* PWM_BaseStruct)
{
    PWM_BaseStruct->PWM_Prescale    = PWM_PWMPS_PClkDiv1;
    PWM_BaseStruct->PWM_Select      = PWM_PWMMS_PWM;
    PWM_BaseStruct->PWM_CaptureModeSelect   = PWM_CMS_CMSRis;
    PWM_BaseStruct->PWM_CaptureChannelSelect = PWM_CHS_ChannelA;
}

/**
  * @brief  Sets the PWM LOAD Register value
  * @param  TIMx    : where x can be 0 or 1 to select the TIM peripheral.
  * @param  LoadVal : specifies the LOAD register new value.
  *         @arg    : 0 <= LoadVal <= 2^16
  * @param  ReloadStatus:ENABLE/DISABLE reload
  * @retval None
  */
void PWM_SetLoadVal(uint8_t PWMx,uint16_t LoadVal,FunctionalState ReloadStatus)
{
    switch(PWMx)
    {
        case PWM0 :{
            PWM->LOAD0 = LoadVal;
            if(ReloadStatus != DISABLE)
            {
                PWM->LOAD0 |= 1<<16;
            }
        }break;
        
        case PWM1 :{
            PWM->LOAD1 = LoadVal;
            if(ReloadStatus != DISABLE)
            {
                PWM->LOAD1 |= 1<<16;
            }
        }break;
 /*       
        case PWM2 :{
            PWM->LOAD2 = LoadVal;
            if(ReloadStatus != DISABLE)
            {
                PWM->LOAD2 |= 1<<16;
            }
        }break;
        
        case PWM3 :{
            PWM->LOAD3 = LoadVal;
            if(ReloadStatus != DISABLE)
            {
                PWM->LOAD3 |= 1<<16;
            }
        }break;
 */
    }
}

/**
  * @brief  Sets the PWM DATA_A Register value
  * @param  TIMx: where x can be 0 or 1 to select the TIM peripheral.
  * @param  DataVal: specifies the DATA register new value.
  * @param  PWMOP:PWM Output Polarity Select
  *             @arg PMW_L:PWM leading low output.
  *             @arg PWM_H:PWM leading high output.
  * @retval None
  */
void PWM_SetADataVal(uint8_t PWMx,uint16_t DataVal,PwmLeadStatus PWMOP)
{
    switch(PWMx)
    {
        case PWM0 :{
            PWM->D0A = DataVal;
            if(PWMOP != PWM_L)
            {
                PWM->D0A |= 1<<16;
            }
        }break;
        
        case PWM1 :{
            PWM->D1A = DataVal;
            if(PWMOP != PWM_L)
            {
                PWM->D1A |= 1<<16;
            }
        }break;
 
 /*       
        case PWM2 :{
            PWM->D2A = DataVal;
            if(PWMOP != PWM_L)
            {
                PWM->D2A |= 1<<16;
            }
        }break;
        
        case PWM3 :{
            PWM->D3A = DataVal;
            if(PWMOP != PWM_L)
            {
                PWM->D3A |= 1<<16;
            }
        }break;
 */
    }
}

/**
  * @brief  Sets the PWM DATA_B Register value
  * @param  TIMx: where x can be 0 or 1 to select the TIM peripheral.
  * @param  DataVal: specifies the DATA register new value.
  * @param  PWMOP:PWM Output Polarity Select
  *             @arg 0:PWM leading low output.
  *             @arg 1:PWM leading high output
  * @retval None
  */
void PWM_SetBDataVal(uint8_t PWMx,uint16_t DataVal,PwmLeadStatus PWMOP)
{
    switch(PWMx)
    {
        case PWM0 :{
            PWM->D0B = DataVal;
            if(PWMOP != 0)
            {
                PWM->D0B |= 1<<16;
            }
        }break;
        
        case PWM1 :{
            PWM->D1B = DataVal;
            if(PWMOP != 0)
            {
                PWM->D1B |= 1<<16;
            }
        }break;
 
 /*       
        case PWM2 :{
            PWM->D2B = DataVal;
            if(PWMOP != 0)
            {
                PWM->D2B |= 1<<16;
            }
        }break;
        
        case PWM3 :{
            PWM->D3B = DataVal;
            if(PWMOP != 0)
            {
                PWM->D3B |= 1<<16;
            }
        }break;
 */
    }
}

/**
  * @brief  Enables or disables the PWM peripheral.
  * @param  PWMx: where x can be 0,1,2,3 to select the TIMx
  *         peripheramnl.
  * @param  NewState:Start or Stop PWM count.
  *          This parameter can be: PWM_RUN or PWM_STOP.
  * @retval None
  */
void PWM_Cmd(uint8_t PWMx,PwmRunStatus NewStatus)
{
    if(NewStatus != PWM_STOP)
    {
        
        PWM->RUN |= 1 << PWMx;
    }
    else
    {
        PWM->RUN &= ~(1<<PWMx);
    }
}

/**
  * @brief  Enables or disables the specified PWM interrupts.
  * @param  PwmITSource: specifies the PWM interrupts sources to be enabled or disabled.
  *          This parameter can be any combination of the following values:
  *            @arg PWM_IMSC0: PWM Group 0 Raw Compare/Capture interrupt
  *            @arg PWM_IMSC1: PWM Group 1 Raw Compare/Capture interrupt
  *            @arg PWM_IMSC2: PWM Group 2 Raw Compare/Capture interrupt
  *            @arg PWM_IMSC3: PWM Group 3 Raw Compare/Capture interrupt
  *            @arg PWM_IMSC4: PWM Group 0 Raw Overflow interrupt Status
  *            @arg PWM_IMSC5: PWM Group 1 Raw Overflow interrupt Status
  *            @arg PWM_IMSC6: PWM Group 2 Raw Overflow interrupt Status
  *            @arg PWM_IMSC7: PWM Group 3 Raw Overflow interrupt Status
  * @param  NewState: new state of the TIM interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void PWM_ITConfig(uint32_t PwmITSource,FunctionalState NewStatus)
{
    if(NewStatus != DISABLE)
    {
        PWM->IMSC |= PwmITSource;
    }
    else
    {
        PWM->IMSC &= ~PwmITSource;
    }
}

/**
  * @brief  get the PWM interrupts flag.
  * @param  PwmITSource: specifies the PWM interrupts sources to be enabled or disabled.
  *          This parameter can be any combination of the following values:
  *            @arg PWM_IMSC0: PWM Group 0 Raw Compare/Capture interrupt
  *            @arg PWM_IMSC1: PWM Group 1 Raw Compare/Capture interrupt
  *            @arg PWM_IMSC2: PWM Group 2 Raw Compare/Capture interrupt
  *            @arg PWM_IMSC3: PWM Group 3 Raw Compare/Capture interrupt
  *            @arg PWM_IMSC4: PWM Group 0 Raw Overflow interrupt Status
  *            @arg PWM_IMSC5: PWM Group 1 Raw Overflow interrupt Status
  *            @arg PWM_IMSC6: PWM Group 2 Raw Overflow interrupt Status
  *            @arg PWM_IMSC7: PWM Group 3 Raw Overflow interrupt Status
  * @retval The new state of the ITStatus(SET or RESET).
  */
ITStatus PWM_GetITStatus(uint32_t PwmITSource)
{
    ITStatus status = RESET;
    
    if(PWM->MIS & PwmITSource)
    {
        status = SET;
    }
    return status;
}

/**
  * @brief  Clears the PWM interrupt pending bits.
  * @param  PwmITSource: specifies the PWM interrupts sources to be enabled or disabled.
  *          This parameter can be any combination of the following values:
  *            @arg PWM_IMSC0: PWM Group 0 Raw Compare/Capture interrupt
  *            @arg PWM_IMSC1: PWM Group 1 Raw Compare/Capture interrupt
  *            @arg PWM_IMSC2: PWM Group 2 Raw Compare/Capture interrupt
  *            @arg PWM_IMSC3: PWM Group 3 Raw Compare/Capture interrupt
  *            @arg PWM_IMSC4: PWM Group 0 Raw Overflow interrupt Status
  *            @arg PWM_IMSC5: PWM Group 1 Raw Overflow interrupt Status
  *            @arg PWM_IMSC6: PWM Group 2 Raw Overflow interrupt Status
  *            @arg PWM_IMSC7: PWM Group 3 Raw Overflow interrupt Status
  * @retval None
  */
void PWM_ClearITPendingBit(uint32_t PwmITSource)
{
    PWM->ICLR |= PwmITSource;
}

