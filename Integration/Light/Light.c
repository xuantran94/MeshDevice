#include "Light.h"

#if( STD_ON == LIGHT_CFG_MODULE_ACTIVE )

#include "osapi.h"
#include "Hass.h"
#include "Device.h"
//#include "config_flash.h"
//sysconfig_t config;

Std_ReturnType ICACHE_FLASH_ATTR Light_Init (void)
{

};
Std_ReturnType ICACHE_FLASH_ATTR Light_Hass_Register(void)
{
    uint8 light_id_u8 = 0;
    uint8 configTopic_au8[256];
    uint8 payload_au8[1024];
    uint8 commandTopic_au8[256];
    uint8 stateTopic_au8[256];
    uint8 availabilityTopic_au8[256];
    uint8 lightUniqueId_au8[256];

    os_sprintf(availabilityTopic_au8, "%s/availibility", DEVICE_NAME);
    for (light_id_u8= 0; light_id_u8 < LIGHT_CFG_NUM_LIGHTS; light_id_u8++)
    {
        os_sprintf(lightUniqueId_au8, "%s_%s", DEVICE_ID, lightConfig_ast[light_id_u8].lightName);
        os_sprintf(stateTopic_au8, "%s/light/%s/state", DEVICE_NAME, lightConfig_ast[light_id_u8].lightName);
        os_sprintf(commandTopic_au8, "%s/light/%s/command", DEVICE_NAME, lightConfig_ast[light_id_u8].lightName);
        os_sprintf(configTopic_au8, "%s/%s/%s/%s/config", HASS_TOPIC, "light", DEVICE_NAME, lightConfig_ast[light_id_u8].lightName);
        os_printf("publish to %s\r\n", configTopic_au8);

        /* {
         "schema":"json",
         "brightness":true,
         "name":"12V light 1",
         "state_topic":"testdevice2/light/12v_light_1/state",
         "command_topic":"testdevice2/light/12v_light_1/command",
         "availability_topic":"testdevice2/status",
         "unique_id":"ESPlight12v_light_1",
         "device":
         {
             "identifiers":"84cca885c327",
             "name":"testdevice2",
             "sw_version":"esphome v1.19.1 Jul  3 2021, 14:20:06",
             "model":"PLATFORMIO_ESP12E",
             "manufacturer":"espressif"
         }
        } */

        os_sprintf(payload_au8,
        "{\"schema\":\"json\",\"brightness\": %s,\"name\":\"%s\",\"state_topic\":\"%s\",\"command_topic\":\"%s\",\"availability_topic\":\"%s\",\"unique_id\":\"%s\"}",
        (lightConfig_ast[light_id_u8].isLightBrighness? "true" : "false"), /* brighness */
        lightConfig_ast[light_id_u8].lightName, /* name */
        stateTopic_au8,                         /* state topic */
        commandTopic_au8,                       /* command topic */
        availabilityTopic_au8,                  /* availability topic */
        lightUniqueId_au8);                     /* unique id */
        os_printf("payload  %s\r\n", payload_au8);
        mqtt_pub_str_retain(configTopic_au8, payload_au8);
    }
 
    
};

#endif