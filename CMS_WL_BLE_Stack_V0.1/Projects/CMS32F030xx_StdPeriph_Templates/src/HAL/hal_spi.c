#include "hal_spi.h"
#include "CMS32F030x_spi.h"
#include "CMS32F030x_gpio.h"

#ifdef SPI_BLE_24G_CONFIG
void ble_24g_spi_pin_init(void)
{
	GPIO_InitTypeDef GPIO_InitDef;
	SPI_InitTypeDef SPI0_InitType;

	SYS_IOPConfig(E_P35,P35SPI0_SS);
	SYS_IOPConfig(E_P32,P32SPI0_MOSI);
  SYS_IOPConfig(E_P31,P31SPI0_MISO);
  SYS_IOPConfig(E_P34,P34SPI0_CLK);
  //SYS_IOPConfig(E_P00,P00SPI0_CLK);

  SPI_DeInit(SSP0);

  SYS_APBPeriphClockCmd(SYS_APB_SSP0CE,ENABLE);
  SPI_StructInit(&SPI0_InitType);
  SPI0_InitType.SPI_Mode      = SPI_Mode_Master;
  SPI0_InitType.SPI_DataSize  = SPI_DataSize_8b;
  SPI0_InitType.SPI_CPO       = SPI_CPO_Low;
  SPI0_InitType.SPI_NSS       = SPI_NSS_Soft;
  SPI_Init(SSP0,&SPI0_InitType);

	//SPI CE-->P26
	GPIO_StructInit(&GPIO_InitDef);
	GPIO_InitDef.GPIO_Pin = GPIO_Pin_6;
  GPIO_InitDef.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_Init(GPIO2, &GPIO_InitDef);
	//BLE chip enable
	GPIO_SetBits(GPIO2, GPIO_Pin_6);

  SPI_SetClockFreq(SSP0,6000000);
	SPI_NSSInternalSoftwareConfig(SSP0,SPI_NSS_Soft);
  SPI_Cmd(SSP0,ENABLE);
}

void SPI_BLE_Chip_Enable(void)
{
	GPIO_SetBits(GPIO2, GPIO_Pin_6);
}

void SPI_BLE_Chip_Disable(void)
{
	GPIO_ResetBits(GPIO2, GPIO_Pin_6);
}

uint8_t SPI_WriteRead(uint8_t SendData)
{
  while(!((SSP0->STAT >> 1) & 0x01));
  SSP0->DAT = SendData;
  while(!((SSP0->STAT>>2) & 0x01));

  return SSP0->DAT;
}

void SPI_CS_Enable_(void)
{
  SPI_SSOutputCmd(SSP0,SPI_NSSInternalSoft_Low);
}

void SPI_CS_Disable_(void)
{
  SPI_SSOutputCmd(SSP0,SPI_NSSInternalSoft_High);
}

void SPI_Write_Reg(uint8_t reg, uint8_t data)
{
	SPI_CS_Enable_();
	SPI_WriteRead(reg);
	SPI_WriteRead(data);
	SPI_CS_Disable_();
}

uint8_t SPI_Read_Reg(uint8_t reg)
{
	uint8_t temp0 = 0;
	
	SPI_CS_Enable_();
	temp0 = SPI_WriteRead(reg);
	temp0 = SPI_WriteRead(0);
	SPI_CS_Disable_();
	
	return temp0;
}

void RF_WriteBuf(uint8_t reg, uint8_t *pBuf, uint8_t length)
{
  uint8_t j;
	
  SPI_CS_Enable_();
  j = 0;
  SPI_WriteRead(reg);
  for(j = 0;j < length; j++)
  {
      SPI_WriteRead(pBuf[j]);
  }
  j = 0;
  SPI_CS_Disable_();
}

void RF_ReadBuf(uint8_t reg, unsigned char *pBuf,  uint8_t length)
{
  uint8_t byte_ctr;

  SPI_CS_Enable_();
  SPI_WriteRead(reg);
  for(byte_ctr=0;byte_ctr<length;byte_ctr++)
    pBuf[byte_ctr] = SPI_WriteRead(0);
  SPI_CS_Disable_();
}

#endif
