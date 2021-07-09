#include "os_cfg.h"

Std_ReturnType ICACHE_FLASH_ATTR OS_mqttConnected_ISR_Cfg(MQTT_Client* client)
{
    Std_ReturnType retVal_u8;
    retVal_u8 = Light_Hass_Register();
    return retVal_u8;
};