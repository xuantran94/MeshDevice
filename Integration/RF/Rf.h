#ifndef _RF_H_
#define _RF_H_

#include "Rf_Cfg.h"
#include "osapi.h"

#if( STD_ON == RF_CFG_MODULE_ACTIVE )

Std_ReturnType ICACHE_FLASH_ATTR rf_Init(void);

#else

#endif

#if (RF_CFG_DEBUG == STD_ON)
#define RF_DEBUG( format, ... ) os_printf("[Rf]: "); os_printf( format, ## __VA_ARGS__ )
#else
#define RF_DEBUG( format, ... ) 
#endif

#endif