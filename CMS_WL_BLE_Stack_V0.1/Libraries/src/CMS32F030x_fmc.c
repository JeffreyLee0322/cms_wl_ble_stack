#include "CMS32F030x_fmc.h"

/**
  * @brief  Unlocks the FMC control register and program memory access.
  * @param  None
  * @retval None
  */
void FMC_UnLock(void)
{
    FMC->LOCK = FMC_Lock_Key;
}

/**
  * @brief  Locks the Program memory access.
  * @param  None
  * @retval None
  */
void FMC_Lock(void)
{
    FMC->LOCK = 0;
}

/**
  * @brief  Read a word at a specified address.
  * @note   To correctly run this function, the FMC_UnLock() function must be called before.
  * @note   Call the FMC_UnLock() to disable the flash memory access.
  * @param  Address: specifies the address to be read.
  * @retval ReadData: The returned value is read data.
  */
uint32_t FMC_ReadData(uint32_t address)
{
    uint32_t data = 0;
    FMC_UnLock();
    while(FMC->CON & FMC_FMCCON_FMCBBusy);
    FMC->ADR = address;
    FMC->CMD = FMC_FMCCMD_ReadData;
    while(FMC->CON & FMC_FMCCON_FMCBBusy);
    data = FMC->DAT;
    FMC_Lock();
    return data;
}

/**
  * @brief  Write a word at a specified address.
  * @note   To correctly run this function, the FMC_UnLock() function must be called before.
  * @note   Call the FLASH_Lock() to disable the flash memory access 
  * @note   Must be erased before writing a address.
  * @param  Address: specifies the address to be read.
  * @retval ReadData: The returned value is read data.
  */
void FMC_WriteData(uint32_t address,uint32_t data)
{
    FMC_UnLock();
    while(FMC->CON & FMC_FMCCON_FMCBBusy);
    FMC->ADR = address;
    FMC->DAT = data;
    FMC->CMD = FMC_FMCCMD_WriteData;
    while(FMC->CON & FMC_FMCCON_FMCBBusy);
    FMC_Lock();
}

/**
  * @brief  Erases a specified page in program memory.
  * @note   To correctly run this function, the FLASH_Unlock() function must be called before.
  * @note   Call the FLASH_Lock() to disable the flash memory access 
  * @param  pageaddress: The page address in program memory to be erased.
  * @retval none.
  */
void FMC_ErasPage(uint32_t pageaddress)
{
    FMC_UnLock();
    while(FMC->CON & FMC_FMCCON_FMCBBusy);
    FMC->ADR = pageaddress;
    FMC->CMD = FMC_FMCCMD_ErasPage;
    while(FMC->CON & FMC_FMCCON_FMCBBusy);
    FMC_Lock();
}

/**
  * @brief  Set the KEY register.
  * @note   
* @param  key : Set the data to KEY register.
  * @retval none.
  */
void FMC_SetKey(uint32_t key)
{
    FMC_UnLock();
    FMC->KEY = key;
    FMC_Lock();
}

/**
  * @brief  Erases all FLASH pages.
  * @note   To correctly run this function, the FLASH_Unlock() function must be called before.
  * @note   Call the FLASH_Lock() to disable the flash memory access 
  * @param  None
  * @retval None
  */
void FMC_ErasAll(void)
{
    FMC_UnLock();
    while(FMC->CON &  FMC_FMCCON_FMCBBusy);
    FMC->CMD = FMC_FMCCMD_ErasAll;
    while(FMC->CON & FMC_FMCCON_FMCBBusy);
    FMC_Lock();    
}
