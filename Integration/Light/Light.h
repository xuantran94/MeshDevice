#ifndef _LIGHT_H_
#define _LIGHT_H_
#include "Light_Types.h"
#include "Light_Cfg.h"
#include "mqtt.h"
#include "osapi.h"

#if( STD_ON == LIGHT_CFG_MODULE_ACTIVE )
Std_ReturnType ICACHE_FLASH_ATTR Light_Init (void);
Std_ReturnType ICACHE_FLASH_ATTR Light_Hass_Register(MQTT_Client* client );
Std_ReturnType Light_Toggle(uint8 LightId);
Std_ReturnType Light_SetBrightness(uint8 lightId_u8, uint8 duty_u8);
Std_ReturnType Light_SetState(uint8 lightId_u8, uint8 state_u8);
Std_ReturnType Light_GetState(uint8 lightId_u8, uint8 *state_u8);
#endif

#if (LIGHT_CFG_DEBUG == STD_ON)
#define LIGHT_DEBUG( format, ... ) os_printf("[Light]: "); os_printf( format, ## __VA_ARGS__ )
#else
#define LIGHT_DEBUG( format, ... ) 
#endif

#endif