/**
  ******************************************************************************
  * @file    WDG/Reset/main.c
  * @author  CMS IC Test Team
  * @version V1.0.0
  * @date    29-December-2016
  * @brief   Main program body
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
#include "main.h"
#include "user_config.h"
#include "CMS32F030x_syscon.h"
#include "CMS32F030x_gpio.h"

#include "hal_spi.h"
#include "hal_irq.h"

/** @addtogroup CMS32F030x_StdPeriph_Examples
  * @{
  */

/** @addtogroup GPIO_IOToggle
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/

void Delay(uint32_t dly);
void test_gpio(void);

/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */

int main(void)
{
	Delay(100);

  /*配置IHRC8M为系统时钟*/
	//IHRC默认使能，系统时钟默认选择IHRC
  //SYS_HSIConfig(SYS_HSI_8M);//配置IHRC为8M
	SYS_HSIConfig(SYS_HSI_48M);//配置IHRC为48M
	//delay_ms(10);

#if 0
	/*配置PLL为系统时钟*/
	SYS_PLLConfig(SYS_PLLCLKSrc_IHRC,SYS_PLLCLKSrcDiv_1,6,0);//8倍频
	SYS_PLLCmd(ENABLE);
	delay_ms(10);//延时等待PLL稳定
	//while(!(SYSCON->PLLCON &(1<<4)));
	SYS_SYSCLKConfig(SYS_CLK_PLLCLK);//配置PLLCLK为时钟源
  //SystemCoreClockUpdate();
#endif

	/*配置IHRC为系统时钟*/
	//SYS_SYSCLKConfig(SYS_CLK_IRC);//配置IHRC48MHz为时钟源

  SystemCoreClockUpdate();

	test_gpio();

/*外设初始化---------------------------------------------------------------------*/
    //LED_Config();//GPIO Test
//	ADC_Config();//ADC Test
		//UART_Config();//UART Test
//	TIM0_Config();//TIM Test
//	WDT_Config();//WDT Test
//	PWM1_Config();//PWM Test
//	Capture0_Config();
//  EPWM_Config();
//	WWDT_Config();
//	SPI_ConfigMaster();
//	SPI_ConfigSlaver();
//	IIC_ConfigSlaver();
/*上电测试---------------------------------------------------------------------*/

	SYS_IOPConfig(E_P36,P36CLKO);//P36设置为时钟输出
	SYSCON->CLKODIV = 0x00000732;//输出时钟选择PLL，100分频。(HCLK=FSYS)
	//SYS_MCOConfig(SYS_MCO_HCLK,1);

	//GPIO_ResetBits(GPIO1,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
  //Delay(50);
  //GPIO_SetBits(GPIO1,GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7);
  //Delay(50);

	//printf("\r\nHello,M0");
	//printf("\r\nFSYS=%d  2017-11-07  Test",SystemCoreClock);
	//printf("\r\n#6500 = 0x%X",FMC_ReadData(0x6500));
	
#ifdef SPI_BLE_24G_CONFIG
	ble_24g_spi_pin_init();
#endif

#ifdef IRQ_BLE_24G_CONFIG
	ble_24g_pkt_irq_pin_init();
	ble_24g_fifo_irq_pin_init();
#endif

  while(1)
  {
      GPIO1->DO ^= (1<<7); 
      //GPIO3->DO ^= 0x17; 

      Delay(500);
  }

	while(1);
}

void test_gpio(void)
{
    GPIO_InitTypeDef LED_InitDef;
		
//  GPIO_StructInit(&LED_InitDef);
    LED_InitDef.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_5 | GPIO_Pin_7;
		LED_InitDef.GPIO_OutRate = GPIO_OutRate_Slow;
    LED_InitDef.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_Init(GPIO1,&LED_InitDef);

    GPIO_SetBits(GPIO1, GPIO_Pin_6);
		GPIO_SetBits(GPIO1, GPIO_Pin_7);
		GPIO_SetBits(GPIO1, GPIO_Pin_5);
    
//  LED_InitDef.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 |GPIO_Pin_4;
//	LED_InitDef.GPIO_OutRate = GPIO_OutRate_Slow;
//  LED_InitDef.GPIO_Mode = GPIO_Mode_Out_PP;
//  GPIO_Init(GPIO3,&LED_InitDef);

}

void Delay(uint32_t dly)
{
    uint32_t i = 0;
    while(dly--)
    {
        for(i=0;i<1000;i++);
    }
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT A menmber of CMSemicon *****END OF FILE****/
