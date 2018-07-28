#ifndef USER_CONFIG_H
#define USER_CONFIG_H

#include "CMS32F030x.h"

typedef unsigned int    	u32;
typedef unsigned short    u16;
typedef unsigned char 		u8;

typedef unsigned int    	uint32_t;
typedef unsigned short    uint16_t;
typedef unsigned char 		uint8_t;

#define CMS_BLE_CONFIG
#define CMS_24G_CONFIG

#define SPI_BLE_24G_CONFIG
#define IRQ_BLE_24G_CONFIG


#ifdef CMS_BLE_CONFIG



#else /* CMS_BLE_CONFIG */


#endif

#endif
