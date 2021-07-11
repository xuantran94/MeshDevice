#ifndef _HWABDIO_H_
#define _HWABDIO_H_

#include "HwAbDio_Cfg.h"

#if( STD_ON == HWABDIO_CFG_MODULE_ACTIVE )

Std_ReturnType ICACHE_FLASH_ATTR HwAbDio_Init (void);
Std_ReturnType ICACHE_FLASH_ATTR HwAbDio_Set (uint8 hwAbDioId_u8, uint8 state_u8);
Std_ReturnType ICACHE_FLASH_ATTR HwAbDio_Get (uint8 hwAbDioId_u8, uint8* state_u8);

// #else

// #define HwAbDio_Init()
// #define HwAbDio_Set(x,y) E_NOT_OK
// #define HwAbDio_Get(x,y) E_NOT_OK

#endif

#endif