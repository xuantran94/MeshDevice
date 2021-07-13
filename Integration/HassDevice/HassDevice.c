#include "HassDevice.h"
#include "MqttIf.h"
#include "osapi.h"
Std_ReturnType ICACHE_FLASH_ATTR HassDevice_Init(MQTT_Client* client)
{
    MQTT_InitLWT(client, HASS_DEVICE_AVAILABILITY_TOPIC, "offline", 0, 1);
    return E_OK;
}
Std_ReturnType ICACHE_FLASH_ATTR HassDevice_SetOnline(MQTT_Client* client)
{
    return MqttIf_Publish(HASS_DEVICE_AVAILABILITY_TOPIC, "online", os_strlen("online"), 0, 1);
}
void ICACHE_FLASH_ATTR HassDevice_Proc(void)
{
    (void)MqttIf_Publish(HASS_DEVICE_AVAILABILITY_TOPIC, "online", os_strlen("online"), 0, 1);
}