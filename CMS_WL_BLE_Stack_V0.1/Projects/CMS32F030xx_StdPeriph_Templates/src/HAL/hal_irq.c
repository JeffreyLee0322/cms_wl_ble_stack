#include "hal_irq.h"
#include "CMS32F030x_gpio.h"

#ifdef IRQ_BLE_24G_CONFIG
void ble_24g_pkt_irq_pin_init(void)
{
	GPIO_InitTypeDef GPIO_InitDef;
	GPIO_INTType     ExtIntType_InitTypeDef;

  GPIO_StructInit(&GPIO_InitDef);

	ExtIntType_InitTypeDef.IntMode = GPIO_IntMode_Edge;
  ExtIntType_InitTypeDef.IntEdge = GPIO_IntEdge_One;
  ExtIntType_InitTypeDef.IntVal  = GPIO_IntVal_LowOrFall;

	GPIO_InitDef.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitDef.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIO2, &GPIO_InitDef);

	GPIO_ITConfig(GPIO2, GPIO_Pin_5, &ExtIntType_InitTypeDef);
  GPIO_ITCmd(GPIO2, GPIO_Pin_5, ENABLE);

	NVIC_ClearPendingIRQ(GPIO2_IRQn);
  NVIC_EnableIRQ(GPIO2_IRQn);
}

void ble_24g_fifo_irq_pin_init(void)
{
	GPIO_InitTypeDef GPIO_InitDef;
	GPIO_INTType     ExtIntType_InitTypeDef;

  GPIO_StructInit(&GPIO_InitDef);

	ExtIntType_InitTypeDef.IntMode = GPIO_IntMode_Edge;
  ExtIntType_InitTypeDef.IntEdge = GPIO_IntEdge_One;
  ExtIntType_InitTypeDef.IntVal  = GPIO_IntVal_LowOrFall;

	GPIO_InitDef.GPIO_Pin = GPIO_Pin_4;
  GPIO_InitDef.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIO2, &GPIO_InitDef);

	GPIO_ITConfig(GPIO2, GPIO_Pin_4, &ExtIntType_InitTypeDef);
  GPIO_ITCmd(GPIO2, GPIO_Pin_4, ENABLE);

	NVIC_ClearPendingIRQ(GPIO2_IRQn);
  NVIC_EnableIRQ(GPIO2_IRQn);
}

#endif

