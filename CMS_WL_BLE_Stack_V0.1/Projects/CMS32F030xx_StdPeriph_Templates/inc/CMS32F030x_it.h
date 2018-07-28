/**
  ******************************************************************************
  * @file    Project/CMS32F030x_StdPeriph_Templates/CMS32F030x_it.h
  * @author  CMS IC Test Team
  * @version V1.0.0
  * @date    05-December-2016
  * @brief   This file contains the headers of the interrupt handlers.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __CMS32F030X_IT_H
#define __CMS32F030X_IT_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */

void NMI_Handler(void);
void HardFault_Handler(void);
void SVC_Handler(void);
void PendSV_Handler(void);
void SysTick_Handler(void);

/*void PPP_IRQHandler(void);*/

#ifdef __cplusplus
}
#endif

#endif /* __CMS32F030X_IT_H */

/************************ (C) COPYRIGHT A menmber of CMSemicon *****END OF FILE****/
