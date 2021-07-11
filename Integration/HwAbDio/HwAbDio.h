#ifndef _HWABDIO_H_
#define _HWABDIO_H_

#include "HwAbDio_Cfg.h"

#if( STD_ON == HWABDIO_CFG_MODULE_ACTIVE )

Std_ReturnType ICACHE_FLASH_ATTR HwAbDio_Init (void);

#endif

#endif