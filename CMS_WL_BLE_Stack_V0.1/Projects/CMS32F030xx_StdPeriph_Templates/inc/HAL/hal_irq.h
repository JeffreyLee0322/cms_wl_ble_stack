#ifndef HAL_IRQ_H
#define HAL_IRQ_H

#include "user_config.h"

#ifdef IRQ_BLE_24G_CONFIG
void ble_24g_pkt_irq_pin_init(void);
void ble_24g_fifo_irq_pin_init(void);
#endif

#endif


