#ifndef __CMS32F030X_EEPWM_H
#define __CMS32F030X_EEPWM_H

#include "CMS32F030x.h"

#ifdef __cplusplus
extern "C"
{
#endif
    


typedef enum 
{
    EPWM_CNTTYPE_EDGE,
    EPWM_CNTTYPE_CENTER,
}EPWM_CntTypeDef;

typedef enum
{
    EPWM_MODE_INDEPENDENT,
    EPWM_MODE_COMPLEMENT,
}EPWM_ModeDef;

#define EPWM_Channel_5                 5
#define EPWM_Channel_4                 4
#define EPWM_Channel_3                 3
#define EPWM_Channel_2                 2
#define EPWM_Channel_1                 1
#define EPWM_Channel_0                 0


#define EPWM_Group_45                  2
#define EPWM_Group_23                  1
#define EPWM_Group_01                  0

#define EPWM_FaultBrake_H                 1
#define EPWM_FaultBrake_L                 0

/* PWM INT sourse */
#define EPWM_INT_BRKIE                       (1ul << 31)         /*!< PWM IMSC: BRKIE Mask       */
#define EPWM_INT_CMPDIE5 					 (1ul << 29)//en_cmpdie
#define EPWM_INT_CMPDIE4 					 (1ul << 28)
#define EPWM_INT_CMPDIE3 					 (1ul << 27)
#define EPWM_INT_CMPDIE2 					 (1ul << 26)
#define EPWM_INT_CMPDIE1 					 (1ul << 25)
#define EPWM_INT_CMPDIE0 					 (1ul << 24)
#define EPWM_INT_CMPUIE5 					 (1ul << 21)//en_cmpuie
#define EPWM_INT_CMPUIE4 					 (1ul << 20)
#define EPWM_INT_CMPUIE3 					 (1ul << 19)
#define EPWM_INT_CMPUIE2 					 (1ul << 18)
#define EPWM_INT_CMPUIE1 					 (1ul << 17)
#define EPWM_INT_CMPUIE0 					 (1ul << 16)
#define EPWM_INT_PIE5 					 (1ul << 13)//pie
#define EPWM_INT_PIE4 					 (1ul << 12)
#define EPWM_INT_PIE3 					 (1ul << 11)
#define EPWM_INT_PIE2 					 (1ul << 10)
#define EPWM_INT_PIE1 					 (1ul << 9)
#define EPWM_INT_PIE0 					 (1ul << 8)
#define EPWM_INT_ZIE5 					 (1ul << 5)//zie
#define EPWM_INT_ZIE4 					 (1ul << 4)
#define EPWM_INT_ZIE3 					 (1ul << 3)
#define EPWM_INT_ZIE2 					 (1ul << 2)
#define EPWM_INT_ZIE1 					 (1ul << 1)
#define EPWM_INT_ZIE0 					 (1ul << 0)




void EPWM_SelectMode(EPWM_TypeDef *epwm,EPWM_CntTypeDef cntType,EPWM_ModeDef mode);
uint32_t EPWM_ConfigOutputChannel(EPWM_TypeDef *epwm,uint32_t ChannelNum, uint32_t Frequncy, uint32_t DutyCycle);
                                  
void EPWM_Start(EPWM_TypeDef *epwm, uint32_t ChannelNum);
void EPWM_Stop(EPWM_TypeDef *epwm, uint32_t ChannelNum);

void EPWM_EnableOutput(EPWM_TypeDef *epwm, uint32_t ChannelNum);
void EPWM_DisableOutput(EPWM_TypeDef *epwm, uint32_t ChannelNum);

void EPWM_EnableInverse(EPWM_TypeDef *epwm, uint32_t ChannelNum);
void EPWM_DisableInverse(EPWM_TypeDef *epwm, uint32_t ChannelNum);

void EPWM_BrakeLevelSelect(EPWM_TypeDef *epwm,uint8_t ch0,uint8_t ch1,uint8_t ch2,uint8_t ch3,uint8_t ch4,uint8_t ch5);
void EPWM_ConfigSWBrake(EPWM_TypeDef *epwm,FunctionalState NewState);
void EPWM_ConfigFaultBrake(EPWM_TypeDef *epwm,uint32_t brksel,FunctionalState NewState);

void EPWM_EnableFaultBreak(EPWM_TypeDef *epwm, uint32_t u32ChannelMask,uint32_t u32LevelMask,uint32_t u32BreakSource);
void EPWM_DisableFaultBrakeFlag(EPWM_TypeDef *epwm, uint32_t u32ChannelMask,uint32_t u32LevelMask,uint32_t u32BreakSource);

void EPWM_EnableDeadZone (EPWM_TypeDef *epwm, uint32_t ChannelGroup, uint8_t u8Duration);
void EPWM_DisableDeadZone(EPWM_TypeDef *epwm, uint32_t ChannelGroup);

void EPWM_ConfigInt (EPWM_TypeDef *epwm, uint32_t intSourse,FunctionalState NewState);
void EPWM_ClearIntFlag(EPWM_TypeDef *epwm, uint32_t intSourse);
uint32_t EPWM_GetIntFlag (EPWM_TypeDef *epwm, uint32_t intSourse);



/* PWM CLKPSC Bit Field Definitions */
#define EPWM_CLKPSC_CP45_Msk                        (0xFFul << 16)        /*!< PWM CLKPSC: CP45 Mask         */
#define EPWM_CLKPSC_CP23_Msk                        (0xFFul << 8)        /*!< PWM CLKPSC: CP23 Mask         */
#define EPWM_CLKPSC_CP01_Msk                        (0xFFul << 0)        /*!< PWM CLKPSC: CP01 Mask         */

/* PWM CLKDIV Bit Field Definitions */
#define EPWM_CLKDIV_CLKDIV5_Msk                        (7ul << 20)           /*!< PWM CLKDIV: CLKDIV5 Mask         */
#define EPWM_CLKDIV_CLKDIV4_Msk                        (7ul << 16)           /*!< PWM CLKDIV: CLKDIV4 Mask         */
#define EPWM_CLKDIV_CLKDIV3_Msk                        (7ul << 12)           /*!< PWM CLKDIV: CLKDIV3 Mask         */
#define EPWM_CLKDIV_CLKDIV2_Msk                        (7ul << 8)           /*!< PWM CLKDIV: CLKDIV2 Mask         */
#define EPWM_CLKDIV_CLKDIV1_Msk                        (7ul << 4)           /*!< PWM CLKDIV: CLKDIV1 Mask         */
#define EPWM_CLKDIV_CLKDIV0_Msk                        (7ul << 0)           /*!< PWM CLKDIV: CLKDIV0 Mask         */

/* PWM CON Bit Field Definitions */
#define EPWM_CON_PWMTYPE_Msk                     (1ul << 31)        /*!< PWM CON: PWMTYPE Mask      */
#define EPWM_CON_PWMMOD_Msk                      (1ul << 28)         /*!< PWM CON: PWMMOD Mask       */
#define EPWM_CON_HALTED_Msk                      (1ul << 27)         /*!< PWM CON: CLRPWM Mask       */
#define EPWM_CON_DZEN45_Msk                      (1ul << 26)         /*!< PWM CON: DZEN45 Mask       */
#define EPWM_CON_DZEN23_Msk                      (1ul << 25)         /*!< PWM CON: DZEN23 Mask       */
#define EPWM_CON_DZEN01_Msk                      (1ul << 24)         /*!< PWM CON: DZEN01 Mask       */
#define EPWM_CON_CH5MOD_Msk                      (1ul << 23)         /*!< PWM CON: CH5MOD Mask       */
#define EPWM_CON_CH5INV_Msk                      (1ul << 22)         /*!< PWM CON: CH5INV Mask       */
#define EPWM_CON_CH5EN_Msk                       (1ul << 20)          /*!< PWM CON: CH5EN Mask        */
#define EPWM_CON_CH4MOD_Msk                      (1ul << 19)         /*!< PWM CON: CH4MOD Mask       */
#define EPWM_CON_CH4INV_Msk                      (1ul << 18)         /*!< PWM CON: CH4INV Mask       */
#define EPWM_CON_CH4EN_Msk                       (1ul << 16)          /*!< PWM CON: CH4EN Mask        */
#define EPWM_CON_CH3MOD_Msk                      (1ul << 15)         /*!< PWM CON: CH3MOD Mask       */
#define EPWM_CON_CH3INV_Msk                      (1ul << 14)         /*!< PWM CON: CH3INV Mask       */
#define EPWM_CON_CH3EN_Msk                       (1ul << 12)          /*!< PWM CON: CH3EN Mask        */
#define EPWM_CON_CH2MOD_Msk                      (1ul << 11)         /*!< PWM CON: CH2MOD Mask       */
#define EPWM_CON_CH2INV_Msk                      (1ul << 10)         /*!< PWM CON: CH2INV Mask       */
#define EPWM_CON_CH2EN_Msk                       (1ul << 8)          /*!< PWM CON: CH2EN Mask        */
#define EPWM_CON_CH1MOD_Msk                      (1ul << 7)         /*!< PWM CON: CH1MOD Mask       */
#define EPWM_CON_CH1INV_Msk                      (1ul << 6)         /*!< PWM CON: CH1INV Mask       */
#define EPWM_CON_CH1EN_Msk                       (1ul << 4)          /*!< PWM CON: CH1EN Mask        */
#define EPWM_CON_CH0MOD_Msk                      (1ul << 3)         /*!< PWM CON: CH0MOD Mask       */
#define EPWM_CON_CH0INV_Msk                      (1ul << 2)         /*!< PWM CON: CH0INV Mask       */
#define EPWM_CON_CH0EN_Msk                       (1ul << 0)          /*!< PWM CON: CH0EN Mask        */

/* PWM PERIOD Bit Field Definitions */
#define EPWM_PERIOD_PERIOD_Msk                         (0xFFFFul << 0)       /*!< PWM PERIOD: PERIOD Mask      */

/* PWM CMPDAT Bit Field Definitions */
#define EPWM_CMPDAT_CMPDAT_Msk                         (0xFFFFul << 0)       /*!< PWM CMPDAT: CMPDAT Mask      */


/* PWM IMSC Bit Field Definitions */
#define EPWM_IMSC_BRKIE_Msk                      (1ul << 31)         /*!< PWM IMSC: BRKIE Mask       */
#define EPWM_IMSC_CMPDIE5_Msk					 (1ul << 29)//en_cmpdie
#define EPWM_IMSC_CMPDIE4_Msk					 (1ul << 28)
#define EPWM_IMSC_CMPDIE3_Msk					 (1ul << 27)
#define EPWM_IMSC_CMPDIE2_Msk					 (1ul << 26)
#define EPWM_IMSC_CMPDIE1_Msk					 (1ul << 25)
#define EPWM_IMSC_CMPDIE0_Msk					 (1ul << 24)
#define EPWM_IMSC_CMPUIE5_Msk					 (1ul << 21)//en_cmpuie
#define EPWM_IMSC_CMPUIE4_Msk					 (1ul << 20)
#define EPWM_IMSC_CMPUIE3_Msk					 (1ul << 19)
#define EPWM_IMSC_CMPUIE2_Msk					 (1ul << 18)
#define EPWM_IMSC_CMPUIE1_Msk					 (1ul << 17)
#define EPWM_IMSC_CMPUIE0_Msk					 (1ul << 16)
#define EPWM_IMSC_PIE5_Msk					 (1ul << 13)//pie
#define EPWM_IMSC_PIE4_Msk					 (1ul << 12)
#define EPWM_IMSC_PIE3_Msk					 (1ul << 11)
#define EPWM_IMSC_PIE2_Msk					 (1ul << 10)
#define EPWM_IMSC_PIE1_Msk					 (1ul << 9)
#define EPWM_IMSC_PIE0_Msk					 (1ul << 8)
#define EPWM_IMSC_ZIE5_Msk					 (1ul << 5)//zie
#define EPWM_IMSC_ZIE4_Msk					 (1ul << 4)
#define EPWM_IMSC_ZIE3_Msk					 (1ul << 3)
#define EPWM_IMSC_ZIE2_Msk					 (1ul << 2)
#define EPWM_IMSC_ZIE1_Msk					 (1ul << 1)
#define EPWM_IMSC_ZIE0_Msk					 (1ul << 0)


/* PWM MIS Bit Field Definitions */
#define EPWM_MIS_BRKIE_Msk                      (1ul << 31)         /*!< PWM MIS: BRKIE Mask       */
#define EPWM_MIS_CMPDIE5_Msk					 (1ul << 29)//en_cmpdie
#define EPWM_MIS_CMPDIE4_Msk					 (1ul << 28)
#define EPWM_MIS_CMPDIE3_Msk					 (1ul << 27)
#define EPWM_MIS_CMPDIE2_Msk					 (1ul << 26)
#define EPWM_MIS_CMPDIE1_Msk					 (1ul << 25)
#define EPWM_MIS_CMPDIE0_Msk					 (1ul << 24)
#define EPWM_MIS_CMPUIE5_Msk					 (1ul << 21)//en_cmpuie
#define EPWM_MIS_CMPUIE4_Msk					 (1ul << 20)
#define EPWM_MIS_CMPUIE3_Msk					 (1ul << 19)
#define EPWM_MIS_CMPUIE2_Msk					 (1ul << 18)
#define EPWM_MIS_CMPUIE1_Msk					 (1ul << 17)
#define EPWM_MIS_CMPUIE0_Msk					 (1ul << 16)
#define EPWM_MIS_PIE5_Msk					 (1ul << 13)//pie
#define EPWM_MIS_PIE4_Msk					 (1ul << 12)
#define EPWM_MIS_PIE3_Msk					 (1ul << 11)
#define EPWM_MIS_PIE2_Msk					 (1ul << 10)
#define EPWM_MIS_PIE1_Msk					 (1ul << 9)
#define EPWM_MIS_PIE0_Msk					 (1ul << 8)
#define EPWM_MIS_ZIE5_Msk					 (1ul << 5)//zie
#define EPWM_MIS_ZIE4_Msk					 (1ul << 4)
#define EPWM_MIS_ZIE3_Msk					 (1ul << 3)
#define EPWM_MIS_ZIE2_Msk					 (1ul << 2)
#define EPWM_MIS_ZIE1_Msk					 (1ul << 1)
#define EPWM_MIS_ZIE0_Msk					 (1ul << 0)

/* PWM ICLR Bit Field Definitions */
#define EPWM_ICLR_BRKIE_Msk                      (1ul << 31)         /*!< PWM ICLR: BRKIE Mask       */
#define EPWM_ICLR_CMPDIE5_Msk					 (1ul << 29)//en_cmpdie
#define EPWM_ICLR_CMPDIE4_Msk					 (1ul << 28)
#define EPWM_ICLR_CMPDIE3_Msk					 (1ul << 27)
#define EPWM_ICLR_CMPDIE2_Msk					 (1ul << 26)
#define EPWM_ICLR_CMPDIE1_Msk					 (1ul << 25)
#define EPWM_ICLR_CMPDIE0_Msk					 (1ul << 24)
#define EPWM_ICLR_CMPUIE5_Msk					 (1ul << 21)//en_cmpuie
#define EPWM_ICLR_CMPUIE4_Msk					 (1ul << 20)
#define EPWM_ICLR_CMPUIE3_Msk					 (1ul << 19)
#define EPWM_ICLR_CMPUIE2_Msk					 (1ul << 18)
#define EPWM_ICLR_CMPUIE1_Msk					 (1ul << 17)
#define EPWM_ICLR_CMPUIE0_Msk					 (1ul << 16)
#define EPWM_ICLR_PIE5_Msk					 (1ul << 13)//pie
#define EPWM_ICLR_PIE4_Msk					 (1ul << 12)
#define EPWM_ICLR_PIE3_Msk					 (1ul << 11)
#define EPWM_ICLR_PIE2_Msk					 (1ul << 10)
#define EPWM_ICLR_PIE1_Msk					 (1ul << 9)
#define EPWM_ICLR_PIE0_Msk					 (1ul << 8)
#define EPWM_ICLR_ZIE5_Msk					 (1ul << 5)//zie
#define EPWM_ICLR_ZIE4_Msk					 (1ul << 4)
#define EPWM_ICLR_ZIE3_Msk					 (1ul << 3)
#define EPWM_ICLR_ZIE2_Msk					 (1ul << 2)
#define EPWM_ICLR_ZIE1_Msk					 (1ul << 1)
#define EPWM_ICLR_ZIE0_Msk					 (1ul << 0)

/* PWM POEN Bit Field Definitions */
#define EPWM_POEN_PWM5_Msk                        (1ul << 5)           /*!< PWM POEN: POEN5 Mask         */   
#define EPWM_POEN_PWM4_Msk                        (1ul << 4)           /*!< PWM POEN: POEN4 Mask         */  
#define EPWM_POEN_PWM3_Msk                        (1ul << 3)           /*!< PWM POEN: POEN3 Mask         */   
#define EPWM_POEN_PWM2_Msk                        (1ul << 2)           /*!< PWM POEN: POEN2 Mask         */  
#define EPWM_POEN_PWM1_Msk                        (1ul << 1)           /*!< PWM POEN: POEN1 Mask         */  
#define EPWM_POEN_PWM0_Msk                        (1ul << 0)           /*!< PWM POEN: POEN0 Mask         */  

/* PWM BRKCTL Bit Field Definitions */
#define EPWM_BRKCTL_BRKSW_Msk					 (1ul << 10)
#define EPWM_BRKCTL_BRKSEL_Msk					 (1ul << 9)
#define EPWM_BRKCTL_BRKEN_Msk					 (1ul << 8)
#define EPWM_BRKCTL_BRKOD5_Msk					 (1ul << 5)
#define EPWM_BRKCTL_BRKOD4_Msk					 (1ul << 4)
#define EPWM_BRKCTL_BRKOD3_Msk					 (1ul << 3)
#define EPWM_BRKCTL_BRKOD2_Msk					 (1ul << 2)
#define EPWM_BRKCTL_BRKOD1_Msk					 (1ul << 1)
#define EPWM_BRKCTL_BRKOD0_Msk					 (1ul << 0)


/* PWM DTCTL Bit Field Definitions */
#define EPWM_DTCTL_DT45_Msk                      (0xFFul << 16)      /*!< PWM DTCTL: DT45 Mask       */
#define EPWM_DTCTL_DT23_Msk                      (0xFFul << 16)      /*!< PWM DTCTL: DT23 Mask       */
#define EPWM_DTCTL_DT01_Msk                      (0xFFul << 16)      /*!< PWM DTCTL: DT01 Mask       */







#ifdef __cplusplus
}
#endif

#endif //__EPWM_H__

/************************ (C) COPYRIGHT A menmber of CMSemicon *****END OF FILE****/
