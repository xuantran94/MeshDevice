#ifndef _OS_CFG_H_
#define _OS_CFG_H_

#include "Std_Types.h"
#include "HwAbPwm.h"
#include "HwAbDio.h"
#include "Light.h"
#include "Swadp.h"
/* Todo: removed in the future */
#include "mqtt.h"


Std_ReturnType ICACHE_FLASH_ATTR OS_mqttConnected_ISR_Cfg(MQTT_Client* client);
void ICACHE_FLASH_ATTR OS_Init_Cfg(void);
void ICACHE_FLASH_ATTR OS_Task_10ms_Cfg(void);
void ICACHE_FLASH_ATTR OS_Task_1ms_Cfg(void);
void ICACHE_FLASH_ATTR OS_10us_Task_Cfg(void);
void ICACHE_FLASH_ATTR OS_100ms_Task_Cfg(void);
void ICACHE_FLASH_ATTR OS_Task_10s_Cfg(void);

#endif