#ifndef __CMS32F030X_TIM_H
#define __CMS32F030X_TIM_H

#include "CMS32F030x.h"
#include "config_CMS32F030x.h"


#define TIM_TMREN_Eable         ((uint32_t)(0x00000080))
#define TIM_TMREN_Disable       ((uint32_t)(0x00000000))

#define TIM_CountMode_FreeRun   ((uint32_t)(0x00000000))
#define TIM_CountMode_Periodic  ((uint32_t)(0x00000040))

#define TIM_Prescale_Div1       ((uint32_t)(0x00000000))
#define TIM_Prescale_Div16      ((uint32_t)(0x00000004))
#define TIM_Prescale_Div256     ((uint32_t)(0x00000008))

#define TIM_CountOperation16    ((uint32_t)(0x00000000))
#define TIM_CountOperation32    ((uint32_t)(0x00000002))

#define TIM_OneShotMode_OneShot     ((uint32_t)(0x00000001))
#define TIM_OneShotMode_Wrapping    ((uint32_t)(0x00000000))

typedef struct
{
    uint32_t TIM_Mode;
    uint32_t TIM_Prsc;
    uint32_t TIM_ContOption;
    uint32_t TIM_OneShotMode;
    uint32_t TIM_Load;
}TIM_TimeBaseInitTypeDef;

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */ 

/* TimeBase management ********************************************************/
void TIM_DeInit(TIMER_TypeDef* TIMx);
void TIM_TimeBaseInit(TIMER_TypeDef* TIMx, TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void TIM_TimeBaseStructInit(TIM_TimeBaseInitTypeDef* TIM_TimeBaseInitStruct);
void TIM_PrescalerConfig(TIMER_TypeDef* TIMx, uint32_t Prescaler);
void TIM_SetCounter(TIMER_TypeDef* TIMx, uint32_t Counter);
void TIM_SetBGCounter(TIMER_TypeDef* TIMx, uint32_t Counter);
uint32_t TIM_GetCounter(TIMER_TypeDef* TIMx);
uint32_t TIM_GetBGCounter(TIMER_TypeDef* TIMx);
uint16_t TIM_GetPrescaler(TIMER_TypeDef* TIMx);
void TIM_Cmd(TIMER_TypeDef* TIMx, FunctionalState NewState);

/* Interrupts, DMA and flags management ***************************************/
void TIM_ITConfig(TIMER_TypeDef* TIMx,FunctionalState NewState);
ITStatus TIM_GetITStatus(TIMER_TypeDef* TIMx);
void TIM_ClearITPendingBit(TIMER_TypeDef* TIMx);

#endif
