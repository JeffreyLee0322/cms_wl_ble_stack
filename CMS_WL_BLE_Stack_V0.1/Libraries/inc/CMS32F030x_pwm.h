#ifndef __CMS32F030X_PWM_H
#define __CMS32F030X_PWM_H

#include "CMS32F030x.h"
#include "config_CMS32F030x.h"



/** @defgroup PWM_Prescale_Select
  * @{
  */
#define PWM_PWMPS_PClkDiv1          ((uint32_t)(0x00000000))
#define PWM_PWMPS_PClkDiv4      ((uint32_t)(0x00000010))
#define PWM_PWMPS_PClkDiv16     ((uint32_t)(0x00000020))
#define PWM_PWMPS_PClkDiv64     ((uint32_t)(0x00000030))
/**
  * @}
  */ 

/** @defgroup PMW_Mode_Select
  * @{
  */
#define PWM_PWMMS_Capture       ((uint32_t)(0x00000000))
#define PWM_PWMMS_PWM           ((uint32_t)(0x00000008))
/**
  * @}
  */ 

/** @defgroup Capture_Channel_Select
  * @{
  */
#define PWM_CHS_ChannelA        ((uint32_t)(0x00000000))
#define PWM_CHS_ChannelB        ((uint32_t)(0x00000004))
/**
  * @}
  */ 

/** @defgroup Capture_Mode_Select
  * @{
  */
#define PWM_CMS_CMSRis          ((uint32_t)(0x00000000))
#define PWM_CMS_CMSFall         ((uint32_t)(0x00000001))
#define PMW_CMS_CMSRisToFall    ((uint32_t)(0x00000002))
#define PWM_CMS_CMSFalltoRis    ((uint32_t)(0x00000003))
/**
  * @}
  */ 


/** @defgroup 
  * @{
  */
#define PWM0                    ((uint32_t)0x00)
#define PWM1                    ((uint32_t)0x01)
//#define PWM2                    ((uint32_t)0x02)
//#define PWM3                    ((uint32_t)0x03)
/**
  * @}
  */ 

/** @defgroup 
  * @{
  */
#define PWM_IMSC0               ((uint32_t)(0x00000001))
#define PWM_IMSC1               ((uint32_t)(0x00000002))
//#define PWM_IMSC2               ((uint32_t)(0x00000004))
//#define PWM_IMSC3               ((uint32_t)(0x00000008))
#define PWM_IMSC4               ((uint32_t)(0x00000010))
#define PWM_IMSC5               ((uint32_t)(0x00000020))
//#define PWM_IMSC6               ((uint32_t)(0x00000040))
//#define PWM_IMSC7               ((uint32_t)(0x00000080))
/**
  * @}
  */ 


/** @defgroup 
  * @{
  */
typedef enum
{
    PWM_L,
    PWM_H,
}PwmLeadStatus;
/**
  * @}
  */ 
  
/** @defgroup 
  * @{
  */
typedef enum
{
    PWM_RUN,
    PWM_STOP,
}PwmRunStatus;

/**
  * @}
  */ 

typedef struct
{
    uint32_t PWM_Prescale;        /*!< Specifies the TIM Prescale.
                                  This parameter can be a value of @ref PWM_Prescale_Select */
    uint32_t PWM_Select;          /*!< Specifies the TIM Mode.
                                  This parameter can be a value of @ref PMW_Mode_Select */
    uint32_t PWM_CaptureChannelSelect;  /*!< Specifies the TIM Channel.
                                        This parameter can be a value of @ref Capture_Channel_Select */
    uint32_t PWM_CaptureModeSelect;     /*!< Specifies the Capture Mode.
                                        This parameter can be a value of @ref Capture_Mode_Select */
}PWM_BaseStructTypeDef;

void PWM_DeInit(void);
void PWM_Init(uint8_t PWMx,PWM_BaseStructTypeDef* PWM_BaseStruct);
void PWM_BaseStructInit(PWM_BaseStructTypeDef* PWM_BaseStruct);
void PWM_SetLoadVal(uint8_t PWMx,uint16_t LoadVal,FunctionalState ReloadStatus);
void PWM_SetADataVal(uint8_t PWMx,uint16_t DataVal,PwmLeadStatus PWMOP);
void PWM_SetBDataVal(uint8_t PWMx,uint16_t DataVal,PwmLeadStatus PWMOP);
void PWM_Cmd(uint8_t PWMx,PwmRunStatus NewStatus);

void PWM_ITConfig(uint32_t PwmITSource,FunctionalState NewStatus);
ITStatus PWM_GetITStatus(uint32_t PwmITSource);
void PWM_ClearITPendingBit(uint32_t PwmITSource);




#endif
