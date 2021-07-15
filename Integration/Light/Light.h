#ifndef _LIGHT_H_
#define _LIGHT_H_
#include "Light_Types.h"
#include "Light_Cfg.h"
#include "mqtt.h"
#include "osapi.h"
#include "Hass.h"
#include "HassDevice.h"

#if( STD_ON == LIGHT_CFG_MODULE_ACTIVE )
Std_ReturnType ICACHE_FLASH_ATTR Light_Init (void);
Std_ReturnType ICACHE_FLASH_ATTR Light_Hass_Register(MQTT_Client* client );
Std_ReturnType ICACHE_FLASH_ATTR Light_Toggle(uint8 lightId_u8);
Std_ReturnType ICACHE_FLASH_ATTR Light_SetBrightness(uint8 lightId_u8, uint8 duty_u8);
Std_ReturnType ICACHE_FLASH_ATTR Light_SetState(uint8 lightId_u8, uint8 state_u8);
Std_ReturnType ICACHE_FLASH_ATTR Light_GetState(uint8 lightId_u8, uint8 *state_u8);
void ICACHE_FLASH_ATTR Light_Data_ISR_Cfg(const char *topic_pu8, const char *data_pu8 );
#else
    #define Light_Init()                E_NOT_OK
    #define Light_Hass_Register(x)      E_NOT_OK
    #define Light_Toggle(x)             E_NOT_OK
    #define Light_SetBrightness(x,y)    E_NOT_OK
    #define Light_SetState(x,y)         E_NOT_OK
    #define Light_GetState(x,y)         E_NOT_OK
#endif

#if (LIGHT_CFG_DEBUG == STD_ON)
#define LIGHT_DEBUG( format, ... ) os_printf("[Light]: "); os_printf( format, ## __VA_ARGS__ )
#else
#define LIGHT_DEBUG( format, ... ) 
#endif

#endif