/**
  ******************************************************************************
  * @file    Project/CMS32F030x_StdPeriph_Templates/CMS32F030x_it.c
  * @author  CMS IC Test Team
  * @version V1.0.0
  * @date    05-December-2016
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2016 A menmber of CMSemicon</center></h2>
  *
  * Licensed under MCD-CMS Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.mcu.com.cn/about.php
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "CMS32F030x_it.h"
#include "CMS32F030x_gpio.h"

/** @addtogroup Template_Project
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
/* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
	  	
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
	
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
//void SysTick_Handler(void)
//{

//}

/******************************************************************************/
/*                 CMS32F030x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_CMS32F030x.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/
//void WDT_IRQHandler(void)
//{
//    NVIC_ClearPendingIRQ(WDT_IRQn);
//}

void GPIO2_IRQHandler(void)
{
  NVIC_ClearPendingIRQ(GPIO2_IRQn);
	if(1 == GPIO_GetITSource(GPIO2, GPIO_Pin_4))
	{
		if(0 == GPIO_ReadInputDataBit(GPIO2, GPIO_Pin_4))
		{

		}
		else if(1 == GPIO_ReadInputDataBit(GPIO2, GPIO_Pin_4))
		{

		}
		GPIO_ITClear(GPIO2, GPIO_Pin_4);
	}
	
	if(1 == GPIO_GetITSource(GPIO2, GPIO_Pin_5))
	{
		if(0 == GPIO_ReadInputDataBit(GPIO2, GPIO_Pin_5))
		{

		}
		else if(1 == GPIO_ReadInputDataBit(GPIO2, GPIO_Pin_5))
		{

		}
		GPIO_ITClear(GPIO2, GPIO_Pin_5);
	}
}


/**
  * @}
  */


/************************ (C) COPYRIGHT A menmber of CMSemicon *****END OF FILE****/
