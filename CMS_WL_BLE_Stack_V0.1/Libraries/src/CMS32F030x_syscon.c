#include "CMS32F030x_syscon.h"

/** @addtogroup CMS32F030x_StdPeriph_Driver
  * @{
  */

/** @defgroup SYSCON
  * @brief System control modules
  * @{
  */

#define IOCFG ((volatile unsigned long *) (0x50000040))

/**
  * @brief  Get the device identification number.
  * @param  None

  * @retval Identification number.
  */
uint16_t SYS_GetDIDNum(void)
{
    return (SYSCON->DID >> 16);
}

/**
  * @brief  Get the device flash size.
  * @param  None

  * @retval flash size.
  */
SYS_DeviceFlash_TypeDef SYS_GetDevFlashSize(void)
{
   SYS_DeviceFlash_TypeDef flashSize = SYS_DeviceFlash_32K;
   switch(SYSCON->DID & 0xFF)
   {
       case 0x1C :
       {
           flashSize = SYS_DeviceFlash_28K;
       }break;

       default :
       {
           flashSize = SYS_DeviceFlash_32K;
       }break;
   }
   return flashSize;
}

/**
  * @brief  Resets the SYS clock configuration to the default reset state.
  * @param  None.

  * @retval None.
  */
void SYS_CLKDeInit(void)
{
    uint32_t clkCon = 0x00000000;

    clkCon = SYSCON->CLKCON;
    clkCon |= 0x5A690000;
    clkCon |= 1<<3;

    while(SYSCON->CLKSEL & 0x03)
    {
        SYSCON->CLKCON = clkCon;
        while(!(SYSCON->CLKSTAT & 0x01));
        SYSCON->CLKSEL = 0x5A690000;
    }

    clkCon          =    SYSCON->CLKCON;
    clkCon          |=   0x5A690000;
    clkCon          &=   ~(1<<4);
    SYSCON->CLKCON  =    clkCon;
}

/**
  * @brief  System external clock configration.
  * @param  SHS_HSE: external type selection.
  *         This parameter can be one of the following values:
  *             @arg SYS_HSE_HS: 4~24M
  *             @arg SYS_HSE_LS: 32.768k
  * @retval None.
  */
void SYS_HSEConfig(uint8_t SYS_HSE)
{
    uint32_t clkcon = 0x00000000;
    assert_param(IS_SYS_HSE(SYS_HSE));
    clkcon = SYSCON->CLKCON;
    clkcon |= 0x5A690000;
    if(SYS_HSE == SYS_HSE_HS)
    {
       clkcon |= (1<<5);
    }
    else
    {
        clkcon &= ~(1<<5);
    }
    SYSCON->CLKCON = clkcon;
}
/**
  * @brief  System inside clock configration.
  * @param  SYS_HSI: Inside type selection.
  *          This parameter can be one of the following values:
  *             @arg SYS_HSI_8M: 8M
  *             @arg SYS_HSI_22M: 22.1148M
  * @retval None.
  */
void SYS_HSIConfig(uint8_t SYS_HSI)
{
    uint32_t clkCon = 0;
    uint32_t    i=0;
    assert_param(IS_SYS_HSI(SYS_HSI));

    clkCon = SYSCON->CLKCON;
    clkCon |= 0x5A690008;
    SYSCON->CLKCON = clkCon;
    for(i=0;i<10;i++);

    if(SYS_HSI == SYS_HSI_8M)
    {
        clkCon &= ~1;
    }
    else
    {
        clkCon |= 0x01;
    }
    SYSCON->CLKCON = clkCon;
    i=0;
    do{
        i++;
    }while((!(SYSCON->CLKSTAT & 0x01)) && (i<100));
}

/**
  * @brief  Enables or disables the External High Speed oscillator.
  * @param  SYS_HSI: Inside type selection.
  *          This parameter can be one of the following values:
  *             @arg ENABLE : enable external oscillator.
  *             @arg DISABLE: disable external oscillator.
  * @retval None.
  */
void SYS_HSECmd(FunctionalState NewState)
{
    uint32_t tmp=0x5A690000;
    if(NewState == ENABLE)
    {
        //tmp |= (1<<4)+(1<<6);
			  tmp |= (1<<4);
        SYSCON->CLKCON |= tmp;
    }
    else
    {
        tmp = SYSCON->CLKCON;
        tmp &= ~(1<<4);
        SYSCON->CLKCON = 0x5A690000 + tmp;
    }
}
/**
  * @brief  Enables or disables the Internal High Speed oscillator.
  * @param  SYS_HSI: Inside type selection.
  *          This parameter can be one of the following values:
  *             @arg ENABLE : enable internal high speed clock.
  *             @arg DISABLE: disable internal high speed clock.
  * @retval None.
  */
void SYS_HSICmd(FunctionalState NewState)
{
    if(NewState == ENABLE)
    {
        SYSCON->CLKCON |=0x5A690000+ (1<<3);
    }
    else
    {
        SYSCON->CLKCON &= ~(1<<3);

        SYSCON->CLKCON = 0x5A690000+(SYSCON->CLKCON & (~(1<<3)));
    }
}

/**
  * @brief  Wait HSE is readly.
  * @param  None.
  * @retval HSE start up status(ERROR or SUCCESS).
  */
ErrorStatus SYS_WaitForHSEStartUp(void)
{
    uint16_t StartUpCounter = 0;
    uint8_t HseStatus = 0;
    ErrorStatus status=ERROR;
    do
    {
        HseStatus = (SYSCON->CLKSTAT >> 1) & 0x01;
        StartUpCounter++;
    }while((StartUpCounter < 50000) && (HseStatus != 0x01));

    if(HseStatus)
    {
        status = SUCCESS;
    }
    else
    {
        status = ERROR;
    }
    return (status);
}
/**
  * @brief  Wait HSI is readly.
  * @param  None.
  * @retval HSI start up status(ERROR or SUCCESS).
  */
ErrorStatus SYS_WaitForHSIStartUp(void)
{
    uint16_t StartUpCounter = 0;
    uint8_t HseStatus = 0;
    ErrorStatus status=ERROR;
    do
    {
        HseStatus = SYSCON->CLKSTAT & 0x01;
        StartUpCounter++;
    }while((StartUpCounter < 50000) && (HseStatus != 0x01));

    if(HseStatus)
    {
        status = SUCCESS;
    }
    else
    {
        status = ERROR;
    }
    return (status);
}
/**
  * @brief  System clock out config.
  * @param  SYS_MCOSource:System out clock source config.
  *          @arg : SYS_MCO_HCLK:core clock as out source.
  *          @arg : SYS_MCO_IHRC:interior rc as out source.
  *          @arg : SYS_MCO_PLLCLK:PLL as out source.
  *          @arg : SYS_MCO_XT:XOS as out source.
  * @param  SYS_MCOPrescaler: out clock div value(2 <SYS_MCOPrescaler<512);
  * @retval None
  */
void SYS_MCOConfig(uint32_t SYS_MCOSource,uint32_t SYS_MCOPrescaler)
{
    uint32_t clkMco = 0;
    assert_param(IS_SYS_MCO(SYS_MCOSource));
    assert_param(SYS_MCOPrescaler < 255);

    clkMco = 0x5A690000 + (SYSCON->CLKODIV & 0x100) + SYS_MCOSource + (SYS_MCOPrescaler/2);
    SYSCON->CLKODIV = clkMco;
}
/**
  * @brief  System clock out enabl/disable.
  * @param  NewState:This parameter can be one of the following values:
  *             @arg ENABLE : enable external oscillator.
  *             @arg DISABLE: disable external oscillator.

  * @retval none.
  */
void SYS_MCOCmd(FunctionalState NewState)
{
		uint32_t clkodiv = 0;
		clkodiv = 0x5A690000 + SYSCON->CLKODIV;
    if(NewState == ENABLE)
    {
        clkodiv |= (1<<8);
    }
    else
    {
        clkodiv &= ~(1<<8);
    }
		SYSCON->CLKODIV = clkodiv;
}
/**
  * @brief  Select system core clock source.
  * @param  SYS_SYSCLKSource.
      * @arg SYS_CLK_IRC    : select interior rc.
      * @arg SYS_CLK_XOSC   :select XOSC.
      * @arg SYS_CLK_IRC10K :select rc10K.
      * @arg SYS_CLK_PLLCLK :select PLLCLK.
  * @retval none.
  */
void SYS_SYSCLKConfig(uint32_t SYS_SYSCLKSource)
{
    uint32_t timcount=0;
    assert_param(IS_SYS_CLK(SYS_SYSCLKSource));
    do
    {
        SYSCON->CLKSEL = (0x5A690000 | SYS_SYSCLKSource);
        timcount ++;
    }while((SYSCON->CLKSEL != SYS_SYSCLKSource) && timcount <10);
}

/**
  * @brief  System AHB clock divider config.
  * @param  SYS_AHBCLK:(0 <= SYS_AHBCLK < 512).
  * @retval none.
*/
void SYS_AHBConfig(uint8_t SYS_AHBCLK)
{
    assert_param( SYS_AHBCLK <= 255 );
    SYSCON->AHBCKDIV = 0x5A690000 + SYS_AHBCLK/2;
}

/**
  * @brief  APB clock diver config.
  * @param  SYS_APBCLK:(0 <= SYS_APBCLK <512).
  * @retval none.
  */
void SYS_APBConfig(uint8_t SYS_APBCLK)
{
    assert_param( SYS_APBCLK <= 255);
    SYSCON->APBCKDIV = 0x5A690000 + SYS_APBCLK/2;
}

/**
  * @brief  TIM0 and TiM1 clock source select.
  * @param  SYS_TMR01CLK:TIM clock source
    * @arg  SYS_TMR_PCLK:select APC clock.
    * @arg  SYS_TMR_IRC: select IRC clock.
    * @arg  SYS_TMR_XOSC: select XOSC clock.
    * @arg  SYS_TMR_IRC10K:select IRC10 clock.
    * @retval none.
  */
void SYS_TMR01Config(uint8_t SYS_TMR01CLK)
{
    assert_param(IS_TMR_CLK(SYS_TMR01CLK));

    SYSCON->APBCKSEL = 0x5A690000 + SYS_TMR01CLK;
}


/**
  * @brief  Enables or disables the APB peripheral clock.
  * @note   After reset, the peripheral clock (used for registers read/write access)
  *         is enabled and the application software has to enable this clock before
  *         using it.
  * @param  SYS_APBPeriph: specifies the AHB peripheral to gates its clock.
  *          This parameter can be any combination of the following values:
  *             @arg SYS_APB_WDTCE      :WDT clock.
  *             @arg SYS_APB_TIMER01CE  :TIM0,TIM1 clock.
  *             @arg SYS_APB_UART0CE    :UART0 clock.
  *             @arg SYS_APB_UART1CE    :UART1 Clock.
  *             @arg SYS_APB_I2C0CE     :I2C0 clock.
  *             @arg SYS_APB_I2C1CE     :I2c1 clock.
  *             @arg SYS_APB_SSP0CE     :SSP0 clock.
  *             @arg SYS_APB_ADCCE      :ADC clock.
  *             @arg SYS_APB_PWMCE      :PWM clock.
  * @param  NewState: new state of the specified peripheral clock.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYS_APBPeriphClockCmd(uint32_t SYS_APBPeriph, FunctionalState NewState)
{
    uint32_t apbCkEn = 0;

    apbCkEn = SYSCON->APBCKEN;
    if(NewState == ENABLE)
    {
        apbCkEn |= SYS_APBPeriph;
    }
    else
    {
        apbCkEn &= ~(SYS_APBPeriph);
    }
    SYSCON->APBCKEN = apbCkEn;
}

/**
  * @brief  PLL configration.
  * @param  PllClkSource:Pll clock source select.
  *             @arg SYS_PLLCLKSrc_IHRC:IHRC as pll clock source.
  *             @arg SYS_PLLCLKSrc_XT  :XOSC as pll clock source.
  * @param  CLKSourceDiv:pll clock divider value.
  *             @arg SYS_PLLCLKSrcDiv_1: 1 divider clock.
  *             @arg SYS_PLLCLKSrcDiv_2: 2 divider clock.
  *             @arg SYS_PLLCLKSrcDiv_4: 4 divider clock.
  *             @arg SYS_PLLCLKSrcDiv_8: 8 divider clock.
  * @param  M:detale information please look up datasheet,(0<=M<=63).
  * @param  N:detale information please look up datasheet,(0<=N<=63).
  * @retval none.
  */
void SYS_PLLConfig(uint32_t PllClkSource,uint32_t CLKSourceDiv,uint32_t M,uint32_t N)
{
    uint32_t pllcon = 0;

    assert_param(IS_SYS_PLLSrc(PllClkSource));
    assert_param(IS_SYS_PLLDiv(CLKSourceDiv));

    pllcon = 0x5A000000 | PllClkSource | CLKSourceDiv | (N<<8) | (M<<14);
    SYSCON->PLLCON = pllcon;
}

/**
  * @brief  Waits for PLL start-up.
  * @note   This function waits on PLLSTB flag to be set and return SUCCESS if
  *         this flag is set, otherwise returns ERROR if the timeout is reached
  *         and this flag is not set.
  * @param  None
  * @retval An ErrorStatus enumeration value:
  *          - SUCCESS: PLL clock is stable and ready to use
  *          - ERROR: PLL clock not yet ready
  */
ErrorStatus SYS_WaitForPLLStartUp(void)
{
    uint16_t StartUpCounter = 0;
    uint8_t PllStatus = 0;
    ErrorStatus status=ERROR;

    do
    {
        PllStatus = (SYSCON->PLLCON >> 4) & 0x01;
        StartUpCounter++;
    }while((StartUpCounter < 50000) && (PllStatus != 0x01));

    if(PllStatus)
    {
        status = SUCCESS;
    }
    else
    {
        status = ERROR;
    }
    return (status);
}

/**
  * @brief  Enables or disables the PLL.
  * @note   After enabling the PLL, the application software should wait on
  *         PLLSTB flag to be set indicating that PLL clock is stable and can
  *         be used as system clock source.
  * @param  NewState: new state of the PLL.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYS_PLLCmd(FunctionalState NewState)
{
    if(NewState == ENABLE)
    {
        SYSCON->PLLCON |= 0x5A000001;
    }
    else
    {
        SYSCON->PLLCON = (SYSCON->PLLCON & (~(1<<0)));
    }
}

/**
  * @brief  Enters Sleep mode.
  * @note   In Sleep mode, all I/O pins keep the same state as in sleep mode.
  * @param  PWR_Entry: specifies if SLEEP mode in entered with WFI or WFE instruction.
  *          This parameter can be one of the following values:
  *             @arg SYS_PWR_WFI: enter SLEEP mode with WFI instruction
  *             @arg SYS_PWR_WFE: enter SLEEP mode with WFE instruction
  * @retval None
  */
void SYS_EnterSleepMode(uint8_t PWR_Entry)
{
    assert_param(IS_PWR_SLEEP_ENTRY(PWR_Entry));

    if(PWR_Entry == SYS_PWR_WFE)
    {
        SYSCON->PCON = 0x5A690001;
        __wfe();
    }
    else
    {
        SYSCON->PCON = 0x5A690001;
        __wfi();
    }
}

/**
  * @brief  Enters Deep Sleep mode.
  * @note   In Deep Sleep mode, all I/O pins keep the same state as in deep sleep mode.
  * @param  PWR_Entry: specifies if STOP mode in entered with WFI or WFE instruction.
  *         This parameter can be one of the following values:
  *             @arg SYS_PWR_WFI: enter Deep Sleep mode with WFI instruction
  *             @arg SYS_PWR_WFE: enter Deep Sleep mode with WFE instruction
  * @retval None
  */
void SYS_ENterDeepSleepMode(uint8_t PWR_Entry)
{
    assert_param(IS_PWR_SLEEP_ENTRY(PWR_Entry));

    if(PWR_Entry == SYS_PWR_WFE)
    {
        SYSCON->PCON = 0x5A690002;
        __wfe();
    }
    else
    {
        SYSCON->PCON = 0x5A690002;
        __wfi();
    }
}

/**
  * @brief  Enters stop mode.
  * @note   In stop mode, all I/O pins keep the same state as in stop mode.
  * @param  PWR_Entry: specifies if STOP mode in entered with WFI or WFE instruction.
  *         This parameter can be one of the following values:
  *             @arg SYS_PWR_WFI: enter Deep Sleep mode with WFI instruction
  *             @arg SYS_PWR_WFE: enter Deep Sleep mode with WFE instruction
  * @retval None
  */
void SYS_EnterSTOPMode(uint8_t PWR_Entry)
{
    assert_param(IS_PWR_SLEEP_ENTRY(PWR_Entry));

    if(PWR_Entry == SYS_PWR_WFE)
    {
        SYSCON->PCON = 0x5A690004;
        __wfe();
    }
    else
    {
        SYSCON->PCON = 0x5A690004;
        __wfi();
    }
}

/**
  * @brief  Reset the MCU.
  * @param  None
  * @retval None
  */
void SYS_ResetMCU(void)
{
    SYSCON->RSTCON = (0x156A99A6 << 2) | 1;
}

/**
  * @brief  Reset the CPU.
  * @param  None
  * @retval None
  */
void SYS_ResetCPU(void)
{
    SYSCON->RSTCON = (0x156A99A6 << 2) | 2;
}

/**
  * @brief  GPIO port function config.
  * @param  GPIOx: pointer to a GPIO_Num structure that contains
  *         the port information for the specified GPIO port.
  * @param  SYS_IOPFunc:this parameter contains specified function for gpio port.
  *         This parameter can be any combination of the following values:
  *         (for detail value please check for config_CMS32F030x.h)
  *         @arg    P00
  *         @arg    P00AN11
  *         @arg    P00TXD0
  *         @arg    P00CTS0
  *         @arg    P01
  *         @arg    P01AN12
  *         @arg    P01RXD0
  *         @arg    P01RTS0
  *         @arg    P01SPI0_SS
  *         @arg    P02
  *         @arg    P02AN13
  *         @arg    P03
  *         @arg    P04
  *         @arg    P04PWM3B
  *         @arg    P04SPI0_SS
  *         ...................
  *         ...................
  *         ...................
  *         @arg    P44
  *         @arg    P45
  *         @arg    P46
  *         @arg    P46RXD1
  *         @arg    P47
  *         @arg    P47TXD1
  * @retval none.
  */
void SYS_IOPConfig(GPIO_Num gpio,uint8_t SYS_IOPFunc)
{
    IOCFG[gpio] = SYS_IOPFunc;
}


/**
  * @brief  Enables or disables the specified System clock interrupts.
  * @param  SYS_CLKIT: specifies the system clock interrupt sources to be enabled or disabled.
  *          This parameter can be any combination of the following values:
  *              @arg SYS_IT_PLL: PLL exception interrupt
  *              @arg SYS_IT_XT: XT OSC exception interrupt
  * @param  NewState: new state of the specified system clock interrupts.
  *          This parameter can be: ENABLE or DISABLE.
  * @retval None
  */
void SYS_CLKITConfig(uint8_t SYS_CLKIT, FunctionalState NewState)
{
    assert_param(IS_SYS_IT(SYS_CLKIT));

    if(NewState == ENABLE)
    {
        SYSCON->SYS_IMSC |= (0x5A690000+SYS_CLKIT);
    }
    else
    {
        SYSCON->SYS_IMSC &= ((SYSCON->SYS_IMSC | 0x5A690000) & (~(SYS_CLKIT)));
    }
}

/**
  * @brief  Checks whether the specified system clock flag is set or not.
  * @param  SYS_CLKIT: specifies the system clock interrupt sources to check.
  *          This parameter can be any combination of the following values:
  *              @arg SYS_IT_PLL: PLL exception interrupt
  *              @arg SYS_IT_XT: XT OSC exception interrupt
  * @retval The new state of RCC_FLAG (SET or RESET).
  */
FlagStatus SYS_GetFlagStatus(uint8_t SYS_CLKIT)
{
    FlagStatus itStatus = RESET;
    assert_param(IS_SYS_IT(SYS_CLKIT));
    if(SYSCON->SYS_RIS & SYS_CLKIT)
    {
        itStatus = SET;
    }
    else
    {
        itStatus = RESET;
    }
    return itStatus;
}

/**
  * @brief  Clears the system clock interrupt flags.
  * @param  SYS_CLKIT: specifies the system clock interrupt sources to be clear.
  *          This parameter can be any combination of the following values:
  *              @arg SYS_IT_PLL: PLL exception interrupt
  *              @arg SYS_IT_XT: XT OSC exception interrupt

  * @retval None
  */
void SYS_ClearFlag(uint8_t SYS_CLKIT)
{
    assert_param(IS_SYS_IT(SYS_CLKIT));

    SYSCON->SYS_ICLR |= (0x5A690000+SYS_CLKIT);
}

/**
  * @brief  Get the system clock intertupt status.
  * @param  SYS_CLKIT: specifies the system clock interrupt sources to check.
  *          This parameter can be any combination of the following values:
  *              @arg SYS_IT_PLL: PLL exception interrupt
  *              @arg SYS_IT_XT : XT OSC exception interrupt
  * @retval The new state of ITStatus (SET or RESET).
  */
ITStatus SYS_GetITStatus(uint8_t SYS_CLKIT)
{
    FlagStatus itStatus = RESET;

    assert_param(IS_SYS_IT(SYS_CLKIT));
    if(SYSCON->SYS_MIS & SYS_CLKIT)
    {
        itStatus = SET;
    }
    else
    {
        itStatus = RESET;
    }
    return itStatus;
}


/**
  * @}
  */

/**
  * @}
  */

