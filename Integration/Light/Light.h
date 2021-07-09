#ifndef _LIGHT_H_
#define _LIGHT_H_
#include "Light_Types.h"
#include "Light_Cfg.h"

#if( STD_ON == LIGHT_CFG_MODULE_ACTIVE )

Std_ReturnType ICACHE_FLASH_ATTR Light_Init (void);
Std_ReturnType ICACHE_FLASH_ATTR Light_Hass_Register(void);

#endif

#endif