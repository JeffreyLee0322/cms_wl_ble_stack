#ifndef HAL_SPI_H
#define HAL_SPI_H

#include "user_config.h"


#ifdef SPI_BLE_24G_CONFIG
void ble_24g_spi_pin_init(void);
uint8_t SPI_WriteRead(uint8_t SendData);
void SPI_CS_Enable_(void);
void SPI_CS_Disable_(void);
void SPI_Write_Reg(uint8_t reg, uint8_t data);
uint8_t SPI_Read_Reg(uint8_t reg);
void RF_WriteBuf(uint8_t reg, uint8_t *pBuf, uint8_t length);
void RF_ReadBuf(uint8_t reg, unsigned char *pBuf,  uint8_t length);
#endif

#endif

