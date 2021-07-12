#include "HassDevice.h"
#include "osapi.h"

Std_ReturnType ICACHE_FLASH_ATTR HassDevice_GetAvaiTopic( uint8* topic_pau8)
{
    static uint8 availabilityTopic_au8[100];
    os_sprintf(availabilityTopic_au8, "%s/avai", DEVICE_NAME);
    *topic_pau8 = availabilityTopic_au8[0];
    return E_OK;
}