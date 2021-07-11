#ifndef _LIGHT_H_
#define _LIGHT_H_
#include "Light_Types.h"
#include "Light_Cfg.h"
#include "mqtt.h"
#include "osapi.h"

#if( STD_ON == LIGHT_CFG_MODULE_ACTIVE )
Std_ReturnType ICACHE_FLASH_ATTR Light_Init (void);
Std_ReturnType ICACHE_FLASH_ATTR Light_Hass_Register(MQTT_Client* client );
#endif

// #if (LIGHT_CFG_DEBUG == STD_ON)
// #define LIGHT_DEBUG( format, ... ) os_printf( format, ## __VA_ARGS__ )
// #else
// #define LIGHT_DEBUG( format, ... ) 
// #endif

#endif