#include "Light.h"

#if( STD_ON == LIGHT_CFG_MODULE_ACTIVE )

#include "osapi.h"

Light_tst light_ast[LIGHT_CFG_NUM_LIGHTS];

Std_ReturnType ICACHE_FLASH_ATTR Light_Init (void)
{
    LIGHT_DEBUG("Light_Init\r\n");
    uint8 lightId_u8;
    for (lightId_u8 = 0; lightId_u8 < LIGHT_CFG_NUM_LIGHTS; lightId_u8++)
    {
        light_ast[lightId_u8].state_u8 = lightConfig_ast[lightId_u8].light_default_state_en;
    }
    return E_OK;
};
Std_ReturnType ICACHE_FLASH_ATTR Light_Hass_Register(MQTT_Client* client )
{
    LIGHT_DEBUG("Hass register\r\n");
    uint8 light_id_u8 = 0;
    uint8 configTopic_au8[256];
    uint8 payload_au8[1024];
    uint8 stateTopic_au8[256];
    uint8 lightUniqueId_au8[256];

    for (light_id_u8= 0; light_id_u8 < LIGHT_CFG_NUM_LIGHTS; light_id_u8++)
    {
        os_sprintf(lightUniqueId_au8, "%s_%s", DEVICE_ID, lightConfig_ast[light_id_u8].lightName_pu8);
        os_sprintf(configTopic_au8, "%s/%s/%s/%s/config", HASS_TOPIC, "light", DEVICE_NAME, lightConfig_ast[light_id_u8].lightName_pu8);
        LIGHT_DEBUG("publish to %s\r\n", configTopic_au8);
        os_sprintf(payload_au8,
        "{\"schema\":\"json\",\"brightness\": %s,\"name\":\"%s\",\"stat_t\":\"%s\",\"cmd_t\":\"%s\",\"avty_t\":\"%s\",\"uniq_id\":\"%s\"}",
        (lightConfig_ast[light_id_u8].isLightBrighness_b? "true" : "false"), /* brighness */
        lightConfig_ast[light_id_u8].lightName_pu8,     /* name */
        lightConfig_ast[light_id_u8].state_topic_pu8,   /* state topic */
        lightConfig_ast[light_id_u8].command_topic_pu8, /* command topic */
        HASS_DEVICE_AVAILABILITY_TOPIC,                 /* availability topic */
        lightUniqueId_au8);                             /* unique id */
        LIGHT_DEBUG("payload  %s\r\n", payload_au8);
        mqtt_pub_str_retain(configTopic_au8, payload_au8);
        MQTT_Subscribe(client, (char*) lightConfig_ast[light_id_u8].command_topic_pu8, 0);
    }
    
    return E_OK;
};
Std_ReturnType ICACHE_FLASH_ATTR Light_GetState(uint8 lightId_u8, uint8 *state_u8)
{
    Std_ReturnType retVal_u8 = E_OK;
    *state_u8 = light_ast[lightId_u8].state_u8;
    return retVal_u8;
}
Std_ReturnType ICACHE_FLASH_ATTR Light_SetState(uint8 lightId_u8, uint8 state_u8)
{
    Std_ReturnType retVal_u8 = E_NOT_OK;
    light_ast[lightId_u8].state_u8 = state_u8;
    if(!lightConfig_ast[lightId_u8].isLightBrighness_b)
    {
        light_ast[lightId_u8].state_u8 = state_u8;
        retVal_u8 = HwAbDio_Set(lightConfig_ast[lightId_u8].driverSignalId_u8, state_u8);
    }


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
    return retVal_u8;
};
Std_ReturnType ICACHE_FLASH_ATTR Light_SetBrightness(uint8 lightId_u8, uint8 duty_u8)
{
    Std_ReturnType retVal_u8 = E_NOT_OK;
    if(lightConfig_ast[lightId_u8].isLightBrighness_b)
    {   
        retVal_u8 = HwAbPwm_SetDuty(lightConfig_ast[lightId_u8].driverSignalId_u8, duty_u8);
    }
    return retVal_u8;
};
Std_ReturnType ICACHE_FLASH_ATTR Light_Toggle(uint8 lightId)
{
    uint8 ligtStateCurr_u8;
    Std_ReturnType retVal_u8;
    retVal_u8 = Light_GetState(lightId, &ligtStateCurr_u8);
    if(retVal_u8 == E_OK)
    {
        retVal_u8 = Light_SetState(lightId, !ligtStateCurr_u8);
    }
    return retVal_u8;
};
#endif