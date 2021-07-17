#ifndef _OS_H_
#define _OS_H_

#include "Std_Types.h"
#include "os_cfg.h"
#include "mqtt.h"

Std_ReturnType ICACHE_FLASH_ATTR OS_Init  (void);
Std_ReturnType ICACHE_FLASH_ATTR OS_Ini   (void);
Std_ReturnType ICACHE_FLASH_ATTR OS_IniEnd(void);
void ICACHE_FLASH_ATTR ICACHE_FLASH_ATTR OS_mqttConnected_ISR(MQTT_Client* client);
void ICACHE_FLASH_ATTR OS_mqttData_ISR(const char *topic, uint32_t topic_len, const char *data, uint32_t data_len );
void ICACHE_FLASH_ATTR OS_mqttData_Init(MQTT_Client* client);
uint32 ICACHE_FLASH_ATTR Os_GetTime_us(void);
void ICACHE_FLASH_ATTR Os_shutdown(void);
#endif