#include "Light.h"

#if( STD_ON == LIGHT_CFG_MODULE_ACTIVE )

#include "osapi.h"
#include "Hass.h"
#include "Device.h"

Light_tst light_ast[LIGHT_CFG_NUM_LIGHTS];

Std_ReturnType ICACHE_FLASH_ATTR Light_Init (void)
{
    //LIGHT_DEBUG("Light_Init\r\n");
    uint8 lightId_u8;
    for (lightId_u8 = 0; lightId_u8 < LIGHT_CFG_NUM_LIGHTS; lightId_u8++)
    {
        light_ast[lightId_u8].state_u8 = lightConfig_ast[lightId_u8].Light_default_state_en;
    }
    
};
Std_ReturnType ICACHE_FLASH_ATTR Light_Hass_Register(MQTT_Client* client )
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
        os_sprintf(lightUniqueId_au8, "%s_%s", DEVICE_ID, lightConfig_ast[light_id_u8].lightName_pu8);
        os_sprintf(stateTopic_au8, "%s/light/%s/state", DEVICE_NAME, lightConfig_ast[light_id_u8].lightName_pu8);
        os_sprintf(commandTopic_au8, "%s/light/%s/command", DEVICE_NAME, lightConfig_ast[light_id_u8].lightName_pu8);
        os_sprintf(configTopic_au8, "%s/%s/%s/%s/config", HASS_TOPIC, "light", DEVICE_NAME, lightConfig_ast[light_id_u8].lightName_pu8);
        //LIGHT_DEBUG("publish to %s\r\n", configTopic_au8);

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
        (lightConfig_ast[light_id_u8].isLightBrighness_b? "true" : "false"), /* brighness */
        lightConfig_ast[light_id_u8].lightName_pu8, /* name */
        stateTopic_au8,                         /* state topic */
        commandTopic_au8,                       /* command topic */
        availabilityTopic_au8,                  /* availability topic */
        lightUniqueId_au8);                     /* unique id */
        //LIGHT_DEBUG("payload  %s\r\n", payload_au8);
        mqtt_pub_str_retain(configTopic_au8, payload_au8);
        MQTT_Subscribe(client, commandTopic_au8, 0);
    }
 
    
};
Std_ReturnType LightSetState(uint8 lightId_u8, uint8 state_u8)
{
    // Std_ReturnType retVal_u8 = E_NOT_OK;
    // light_ast[lightId_u8].state_u8 = state_u8;
    // if(lightConfig_ast[lightId_u8].isLightBrighness_b)
    // {
    //     if(state_u8 == Light_state_on)
    //     {
    //         retVal_u8 = HwAbPwm_SetDuty(lightConfig_ast[lightId_u8].driverSignalId_u8, light_ast[lightId_u8].duty_u8);
    //     }else
    //     {
    //         retVal_u8 = HwAbPwm_SetDuty(lightConfig_ast[lightId_u8].driverSignalId_u8, 0u);
    //     }
        
    // }
    // return retVal_u8;
};
Std_ReturnType LightSetBrightness(uint8 lightId_u8, uint8 duty_u8)
{
    Std_ReturnType retVal_u8 = E_NOT_OK;
    if(lightConfig_ast[lightId_u8].isLightBrighness_b)
    {   
#if( STD_ON == HWABPWM_CFG_MODULE_ACTIVE )
        retVal_u8 = HwAbPwm_SetDuty(lightConfig_ast[lightId_u8].driverSignalId_u8, duty_u8);
#else
        retVal_u8 = E_NOT_OK;
#endif
    }
    return retVal_u8;
};
Std_ReturnType LightToggle(uint8 LightId, uint8 state_u8)
{
    
};


#endif