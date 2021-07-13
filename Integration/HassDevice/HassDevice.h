#ifndef _HASS_DEVICE_H_
#define _HASS_DEVICE_H_

#include "HassDevice_Cfg.h"
#include "mqtt.h"

Std_ReturnType ICACHE_FLASH_ATTR HassDevice_Init(MQTT_Client* client);
Std_ReturnType ICACHE_FLASH_ATTR HassDevice_SetOnline(MQTT_Client* client);
void ICACHE_FLASH_ATTR HassDevice_Proc(void);

#endif