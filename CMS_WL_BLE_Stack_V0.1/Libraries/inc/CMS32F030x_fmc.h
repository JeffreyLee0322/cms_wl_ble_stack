#ifndef __CMS32F030X_FMC_H
#define __CMS32F030X_FMC_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "CMS32F030x.h"
#include "config_CMS32F030x.h"
     
#define FMC_Lock_Key                        ((uint32_t)(0x55AA6699))     
     
#define FMC_FMCCON_FMCBNormal               ((uint32_t)(0x00000000))
#define FMC_FMCCON_FMCBBusy                 ((uint32_t)(0x00000020))
     
#define FMC_FMCCON_FMCE_MapEn               ((uint32_t)(0x00000000))
#define FMC_FMCCON_FMCE_MapDis              ((uint32_t)(0x00000010))
     
#define FMC_FMCCMD_ReadData                 ((uint32_t)(0x00000001))
#define FMC_FMCCMD_WriteData                ((uint32_t)(0x00000002))
#define FMC_FMCCMD_ErasPage                 ((uint32_t)(0x00000003))
#define FMC_FMCCMD_ErasAll                  ((uint32_t)(0x00000006))
     
     
     
void FMC_UnLock(void);
void FMC_Lock(void);
uint32_t FMC_ReadData(uint32_t address);
void FMC_WriteData(uint32_t address,uint32_t data);
void FMC_ErasPage(uint32_t pageaddress);
void FMC_ErasAll(void);
void FMC_SetKey(uint32_t key);
     
#ifdef __cplusplus
}
#endif

#endif /*__CMS32F030X_FMC_H */
