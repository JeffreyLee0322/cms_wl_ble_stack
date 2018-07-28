#include "CMS32F030x_epwm.h"

/**
* @brief This function config EPWM count type and work mode
* @param[in] pwm: The base address of EPWM module
* @param[in] cntType: EPWM count type .
*          This parameter can be one of the following values:
*             @arg EPWM_CNTTYPE_CENTER   Center aligned
*             @arg EPWM_CNTTYPE_EDGE    edge aligned
* @param[in] mode:EPWM work mode. 
*          This parameter can be one of the following values:
*             @arg EPWM_MODE_INDEPENDENT  independent mode
*             @arg EPWM_MODE_COMPLEMENT    complement mode
*
*/

void EPWM_SelectMode(EPWM_TypeDef *epwm,EPWM_CntTypeDef cntType,EPWM_ModeDef mode)
{
    epwm->LOCK = 0x55;
    
    if(cntType)
        epwm->CON |= EPWM_CON_PWMTYPE_Msk;
    else epwm->CON &= ~EPWM_CON_PWMTYPE_Msk;
        
    if(mode)
        epwm->CON |= EPWM_CON_PWMMOD_Msk;
    else epwm->CON &= ~EPWM_CON_PWMMOD_Msk;
    
    epwm->LOCK = 0x00;
    
}



/**
 * @brief This function config PWM generator and get the nearest frequency in edge aligned auto-reload mode
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. EPWM_Channel_1~5 
 * @param[in] u32Frequncy Target generator frequence
 * @param[in] u32DutyCycle Target generator duty cycle precentage. Valid range are between 0 ~ 100. 10 means 10%, 20 means 20%...
 * @return Nearest frequence clock in nano second
 * @note Since every two channels, (0 & 1), (2 & 3), (4 & 5), shares a prescaler. Call this API to configure PWM frequency may affect
 *       existing frequency of other channel.
 */
uint32_t EPWM_ConfigOutputChannel (EPWM_TypeDef *epwm, 
                                  uint32_t ChannelNum, 
                                  uint32_t Frequncy, 
                                  uint32_t DutyCycle
                                  )
{
    uint32_t i = SystemAPBClock / Frequncy;
    uint8_t  u8Divider = 1, u8Prescale = 0xFF;
    uint16_t u16CNR = 0xFFFF;
    
    if(epwm->CON & EPWM_CON_PWMTYPE_Msk)
    {
        Frequncy *= 2;
        DutyCycle = (100-DutyCycle);
    }

    
    for(; u8Divider < 17; u8Divider <<= 1) 
	{  // clk divider could only be 1, 2, 4, 8, 16
        i = (SystemCoreClock / Frequncy) / u8Divider;
        // If target value is larger than CNR * prescale, need to use a larger divider
        if(i > (0x10000 * 0x100))   
            continue;
        
        // CNR = 0xFFFF + 1, get a prescaler that CNR value is below 0xFFFF
        u8Prescale = (i + 0xFFFF)/ 0x10000; 
        
        // u8Prescale must at least be 2, otherwise the output stop
        if(u8Prescale < 3)
            u8Prescale = 2;
        
        i /= u8Prescale;
        
        if(i <= 0x10000) {
            if(i == 1)
                u16CNR = 1;     // Too fast, and PWM cannot generat expected frequency...
            else
                u16CNR = i;
            break;
        }
        
    }
    // Store return value here 'cos we're gonna change u8Divider & u8Prescale & u16CNR to the real value to fill into register
    i = SystemCoreClock / (u8Prescale * u8Divider * u16CNR);
    
    u8Prescale -= 1;
    u16CNR -= 1;
    // convert to real register value
    if(u8Divider == 1)
        u8Divider = 4;
    else if (u8Divider == 2)
        u8Divider = 0;
    else if (u8Divider == 4)
        u8Divider = 1;
    else if (u8Divider == 8)
        u8Divider = 2;     
    else // 16
        u8Divider = 3;        
    
    if(ChannelNum<6)
    {
        epwm->LOCK = 0x55;
        
            // every two channels share a prescaler
            epwm->CLKPSC = (epwm->CLKPSC & ~(EPWM_CLKPSC_CP01_Msk << ((ChannelNum >> 1) * 8))) | (u8Prescale << ((ChannelNum >> 1) * 8));
            epwm->CLKDIV = (epwm->CLKDIV & ~(EPWM_CLKDIV_CLKDIV0_Msk << (4 * ChannelNum))) | (u8Divider << (4 * ChannelNum));
            epwm->CON |= EPWM_CON_CH0EN_Msk << (4 * ChannelNum);
            epwm->CMPDAT[ChannelNum] = DutyCycle * (u16CNR + 1) / 100 - 1;
            epwm->PERIOD[ChannelNum] = u16CNR;
            epwm->POEN |= (EPWM_POEN_PWM0_Msk << ChannelNum);

        
        epwm->LOCK = 0x00;    
        return(i);
        
    }
    else
        return 0;
    
}
                                  
 
/**
 * @brief This function start PWM module
 * @param[in] pwm The base address of PWM module
* @param[in] u32ChannelNum :EPWM_Channel_1~5
 * @return None
 */ 
void EPWM_Start (EPWM_TypeDef *epwm, uint32_t ChannelNum)
{
    epwm->LOCK = 0x55;//LOCK OFF   
    
    if(ChannelNum<6)
        epwm->CON |= EPWM_CON_CH0EN_Msk << (ChannelNum*4);
    
    epwm->LOCK = 0x00;//    
}



/**
 * @brief This function stop PWM generation immediately by clear channel enable bit
 * @param[in] pwm The base address of PWM module
* @param[in] u32ChannelNum :EPWM_Channel_1~5.
 *                           
 * @return None
 */
void EPWM_Stop (EPWM_TypeDef *epwm, uint32_t ChannelNum)
{
    epwm->LOCK = 0x55;//LOCK OFF   
    
    if(ChannelNum<6)
        epwm->CON &= ~(EPWM_CON_CH0EN_Msk << ChannelNum*4);
    
    epwm->LOCK = 0x00;//
}

/**
 * @brief This function enables PWM output generation of selected channels
 * @param[in] pwm The base address of PWM module
* @param[in] u32ChannelNum :EPWM_Channel_1~5.
 * @return None
 */
void EPWM_EnableOutput (EPWM_TypeDef *epwm, uint32_t ChannelNum)
{
    epwm->LOCK = 0x55;//LOCK OFF    if(ChannelNum<6)
        epwm->POEN |= (EPWM_POEN_PWM0_Msk << ChannelNum);
    epwm->LOCK = 0x00;//LOCK OFF
}

/**
 * @brief This function disables PWM output generation of selected channels
 * @param[in] pwm The base address of PWM module
* @param[in] u32ChannelNum :EPWM_Channel_1~5.
 * @return None
 */
void EPWM_DisableOutput (EPWM_TypeDef *epwm, uint32_t ChannelNum)
{
    epwm->LOCK = 0x55;//LOCK OFF
    if(ChannelNum<6)
        epwm->POEN &= ~(EPWM_POEN_PWM0_Msk << ChannelNum);
    epwm->LOCK = 0x00;//
}

/**
 * @brief This macro enable output inverter of specified channel(s)
 * @param[in] EPWM The base address of EPWM module
 * @param[in] ChannelNum :EPWM_Channel_1~5
 * @return None
 */
void EPWM_EnableInverse(EPWM_TypeDef *epwm, uint32_t ChannelNum)
{
    epwm->LOCK = 0x55;//LOCK OFF
    if(ChannelNum<6)
        epwm->CON |= (EPWM_CON_CH0INV_Msk << ChannelNum*4);
    epwm->LOCK = 0x00;//
    
}
/**
 * @brief This macro disable output inverter of specified channel(s)
 * @param[in] EPWM The base address of EPWM module
* @param[in] ChannelNum :EPWM_Channel_1~5
 * @return None
 */
void EPWM_DisableInverse(EPWM_TypeDef *epwm, uint32_t ChannelNum)
{
    epwm->LOCK = 0x55;//LOCK OFF
    if(ChannelNum<6)
        epwm->CON &= ~(EPWM_CON_CH0INV_Msk << ChannelNum*4);
    epwm->LOCK = 0x00;//
    
}







/**
 * @brief This function enable Dead zone of selected channel
 * @param[in] pwm The base address of PWM module
* @param[in] ChannelGroup: EPWM_Group_45,EPWM_Group_23,EPWM_Group_01 
 * @param[in] u32Duration Dead Zone length in PWM clock count, valid values are between 0~0xFF, but 0 means there is no
 *                        dead zone.
 * @return None
 */
void EPWM_EnableDeadZone (EPWM_TypeDef *epwm, uint32_t ChannelGroup, uint8_t u8Duration)
{
    uint32_t temp=0xff;
    epwm->LOCK = 0x55;
    
    if(ChannelGroup<3)
    {
        // set duration
        temp = ~(temp <<  (8*ChannelGroup));
        epwm->DTCTL &= temp;
        epwm->DTCTL |= (u8Duration<<(8*ChannelGroup));
        epwm->CON |= (EPWM_CON_DZEN01_Msk << ChannelGroup);
        
    }
    // enable dead zone
    
    epwm->LOCK = 0x00;    
}

/**
 * @brief This function disable Dead zone of selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5 
 * @return None
 */
void EPWM_DisableDeadZone (EPWM_TypeDef *epwm, uint32_t ChannelGroup)
{
    // every two channels shares the same setting
    
    epwm->LOCK = 0x55;    
    // enable dead zone
    epwm->CON &= ~(EPWM_CON_DZEN01_Msk << ChannelGroup); 
    epwm->LOCK = 0x00;    
}


/**
* @brief This function config the electric level of 6 channels of EPWM after a brake occured
* @param[in] pwm The base address of PWM module
* @param[in] ch0~ch5  0 or 1
* 
*/
void EPWM_BrakeLevelSelect(EPWM_TypeDef *epwm,uint8_t ch5,uint8_t ch4,uint8_t ch3,uint8_t ch2,uint8_t ch1,uint8_t ch0)
{
    epwm->LOCK=0x55;
    uint32_t temp = 0x3f;
    epwm->BRKCTL &= ~temp;
    temp = ((ch5<<5)+(ch4<<4)+(ch3<<3)+(ch2<<2)+(ch1<<1)+ch0);
    epwm->BRKCTL |= temp;
    epwm->LOCK=0x00;
}




/**
* @brief This function generate software brake immediately
* @param[in] pwm The base address of PWM module
* @param[in] NewState ENABLE or DISABLE
*/
void EPWM_ConfigSWBrake(EPWM_TypeDef *epwm,FunctionalState NewState)
{
    
    epwm->LOCK = 0x55;    
    if(NewState == ENABLE)
        epwm->BRKCTL |= EPWM_BRKCTL_BRKSW_Msk;
    else epwm->BRKCTL &= ~EPWM_BRKCTL_BRKSW_Msk;
    epwm->LOCK = 0x00; 
    
}


/**
* @brief This function ENABLE fault brake 
* @param[in] pwm The base address of PWM module
* @param[in] brksel EPWM_FaultBrake_H or EPWM_FaultBrake_L.it is meaningless when the Newstate is DISABLE
* @param[in] NewState ENABLE or DISABLE
* 
*/
void EPWM_ConfigFaultBrake(EPWM_TypeDef *epwm,uint32_t brksel,FunctionalState NewState)
{
    epwm->LOCK = 0x55;    
    
    if(brksel)
        epwm->BRKCTL |= EPWM_BRKCTL_BRKSEL_Msk;
    else epwm->BRKCTL &= ~EPWM_BRKCTL_BRKSEL_Msk;
    
    if(NewState == ENABLE)
        epwm->BRKCTL |= EPWM_BRKCTL_BRKEN_Msk;
    else epwm->BRKCTL &= ~EPWM_BRKCTL_BRKEN_Msk;
    epwm->LOCK = 0x00;     
}






/**
 * @brief This function enable period interrupt of selected channel
 * @param[in] pwm The base address of PWM module
 * @param[in] u32ChannelNum PWM channel number. Valid values are between 0~5 
 * @param[in] intSourse interrupt type, could be 
* EPWM_INT_BRKIE                              
* EPWM_INT_CMPDIE5 					 //en_cmpdie
* EPWM_INT_CMPDIE4 					 
* EPWM_INT_CMPDIE3 					 
* EPWM_INT_CMPDIE2 					 
* EPWM_INT_CMPDIE1 					 
* EPWM_INT_CMPDIE0 					 
* EPWM_INT_CMPUIE5 					 //en_cmpuie
* EPWM_INT_CMPUIE4 					 
* EPWM_INT_CMPUIE3 					 
* EPWM_INT_CMPUIE2 					 
* EPWM_INT_CMPUIE1 					 
* EPWM_INT_CMPUIE0 					 
* EPWM_INT_PIE5 					 //pie
* EPWM_INT_PIE4 					 
* EPWM_INT_PIE3 					 
* EPWM_INT_PIE2 					 
* EPWM_INT_PIE1 					 
* EPWM_INT_PIE0 					 
* EPWM_INT_ZIE5 					 //zie
* EPWM_INT_ZIE4 					 
* EPWM_INT_ZIE3 					 
* EPWM_INT_ZIE2 					 
* EPWM_INT_ZIE1 					 
* EPWM_INT_ZIE0 					 
* @param[in] NewState ENABLE or DISABLE
 * @return None
*
 */
void EPWM_ConfigInt (EPWM_TypeDef *epwm, uint32_t intSourse,FunctionalState NewState)
{
    
    epwm->LOCK = 0x55;
    
    if(NewState == ENABLE)
    {
        epwm->IMSC |= (uint32_t)intSourse;
    }
    else epwm->IMSC &= ~(uint32_t)intSourse;

    epwm->LOCK = 0x00;
}


/**
 * @brief This function clear flag interrupt of selected interrupt sourse
 * @param[in] pwm The base address of PWM module
 * @param[in] intSourse interrupt type, could be 
* EPWM_INT_BRKIE                              
* EPWM_INT_CMPDIE5 					 //en_cmpdie
* EPWM_INT_CMPDIE4 					 
* EPWM_INT_CMPDIE3 					 
* EPWM_INT_CMPDIE2 					 
* EPWM_INT_CMPDIE1 					 
* EPWM_INT_CMPDIE0 					 
* EPWM_INT_CMPUIE5 					 //en_cmpuie
* EPWM_INT_CMPUIE4 					 
* EPWM_INT_CMPUIE3 					 
* EPWM_INT_CMPUIE2 					 
* EPWM_INT_CMPUIE1 					 
* EPWM_INT_CMPUIE0 					 
* EPWM_INT_PIE5 					 //pie
* EPWM_INT_PIE4 					 
* EPWM_INT_PIE3 					 
* EPWM_INT_PIE2 					 
* EPWM_INT_PIE1 					 
* EPWM_INT_PIE0 					 
* EPWM_INT_ZIE5 					 //zie
* EPWM_INT_ZIE4 					 
* EPWM_INT_ZIE3 					 
* EPWM_INT_ZIE2 					 
* EPWM_INT_ZIE1 					 
* EPWM_INT_ZIE0 
*
 * @return None
 */
void EPWM_ClearIntFlag (EPWM_TypeDef *epwm, uint32_t intSourse)
{
    
    epwm->LOCK = 0x55;
    
    epwm->ICLR |= (uint32_t)intSourse;

    epwm->LOCK = 0x00;    
}

/**
 * @brief This function get status of interrupt of selected interrupt sourse
 * @param[in] pwm The base address of PWM module
 * @param[in] intSourse interrupt type, could be 
* EPWM_INT_BRKIE                              
* EPWM_INT_CMPDIE5 					 //en_cmpdie
* EPWM_INT_CMPDIE4 					 
* EPWM_INT_CMPDIE3 					 
* EPWM_INT_CMPDIE2 					 
* EPWM_INT_CMPDIE1 					 
* EPWM_INT_CMPDIE0 					 
* EPWM_INT_CMPUIE5 					 //en_cmpuie
* EPWM_INT_CMPUIE4 					 
* EPWM_INT_CMPUIE3 					 
* EPWM_INT_CMPUIE2 					 
* EPWM_INT_CMPUIE1 					 
* EPWM_INT_CMPUIE0 					 
* EPWM_INT_PIE5 					 //pie
* EPWM_INT_PIE4 					 
* EPWM_INT_PIE3 					 
* EPWM_INT_PIE2 					 
* EPWM_INT_PIE1 					 
* EPWM_INT_PIE0 					 
* EPWM_INT_ZIE5 					 //zie
* EPWM_INT_ZIE4 					 
* EPWM_INT_ZIE3 					 
* EPWM_INT_ZIE2 					 
* EPWM_INT_ZIE1 					 
* EPWM_INT_ZIE0 
 */
uint32_t EPWM_GetIntFlag (EPWM_TypeDef *epwm, uint32_t intSourse)
{
    uint32_t temp=0;
    
    epwm->LOCK = 0x55;
    
    temp = ( epwm->MIS & intSourse);
//    temp = epwm->MIS;
    epwm->LOCK = 0x00;    
	return temp;
}






/************************ (C) COPYRIGHT A menmber of CMSemicon *****END OF FILE****/
