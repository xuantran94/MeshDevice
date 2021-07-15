#include "Light.h"

#if( STD_ON == LIGHT_CFG_MODULE_ACTIVE )

#include "osapi.h"
#include "string.h" 
#include "jsmn.h"

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
    uint8 ligtStateCurr_u8;
    retVal_u8 = Light_GetState(lightId_u8, &ligtStateCurr_u8);
    light_ast[lightId_u8].state_u8 = state_u8;

    if(!lightConfig_ast[lightId_u8].isLightBrighness_b)
    {
        light_ast[lightId_u8].state_u8 = state_u8;
        retVal_u8 = HwAbDio_Set(lightConfig_ast[lightId_u8].driverSignalId_u8, state_u8);
    }
    else
    {
        if((state_u8 == STD_ON) && (STD_OFF == ligtStateCurr_u8))
        {
            uint8 brightness_payload_au8[255];
            os_sprintf(brightness_payload_au8, "{\"state\":\"ON\",\"brightness\":%d}", light_ast[lightId_u8].duty_u8);
            retVal_u8 = HwAbPwm_SetDuty(lightConfig_ast[lightId_u8].driverSignalId_u8, light_ast[lightId_u8].duty_u8*100u/255u);
             MqttIf_Publish(lightConfig_ast[lightId_u8].state_topic_pu8, brightness_payload_au8, strlen(brightness_payload_au8) , 0, 1);
            return retVal_u8;
        }else
        {
            retVal_u8 = HwAbPwm_SetDuty(lightConfig_ast[lightId_u8].driverSignalId_u8, STD_OFF);
        }
        
    }
    if(state_u8 == STD_ON)
    {
        MqttIf_Publish(lightConfig_ast[lightId_u8].state_topic_pu8, "{\"state\":\"ON\"}", strlen("{\"state\":\"ON\"}") , 0, 1);
    }
    else
    {
        MqttIf_Publish(lightConfig_ast[lightId_u8].state_topic_pu8, "{\"state\":\"OFF\"}", strlen("{\"state\":\"OFF\"}") , 0, 1);
    }
    
    return retVal_u8;
};
Std_ReturnType ICACHE_FLASH_ATTR Light_SetBrightness(uint8 lightId_u8, uint8 duty_u8)
{
    Std_ReturnType retVal_u8 = E_NOT_OK;

    uint8 ligtStateCurr_u8;
    retVal_u8 = Light_GetState(lightId_u8, &ligtStateCurr_u8);

    if(lightConfig_ast[lightId_u8].isLightBrighness_b)
    {   
        light_ast[lightId_u8].duty_u8 = duty_u8;
        if( (retVal_u8 == E_OK) && ( ligtStateCurr_u8 == STD_ON))
        {
            retVal_u8 = HwAbPwm_SetDuty(lightConfig_ast[lightId_u8].driverSignalId_u8, light_ast[lightId_u8].duty_u8*100u/255u);
        }
    }
    return retVal_u8;
};
Std_ReturnType ICACHE_FLASH_ATTR Light_Toggle(uint8 lightId_u8)
{
    uint8 ligtStateCurr_u8;
    Std_ReturnType retVal_u8;
    //TODO: Check the filter time
    retVal_u8 = Light_GetState(lightId_u8, &ligtStateCurr_u8);
    if(retVal_u8 == E_OK)
    {
        retVal_u8 = Light_SetState(lightId_u8, !ligtStateCurr_u8);
    }
    return retVal_u8;
};
//TODO: cehck the json. It is not saftify me right now
void ICACHE_FLASH_ATTR Light_Data_ISR_Cfg(const char *topic_pu8, const char *data_pu8 )
{
    
    uint8 lightId_u8;

    // LIGHT_DEBUG("ISR at topic: %s\r\n data: %s\r\n",lc_topic_pu8,lc_data_pu8);
    for ( lightId_u8 =0; lightId_u8 < LIGHT_CFG_NUM_LIGHTS; lightId_u8++)
    {
        if((0u == strcmp(lightConfig_ast[lightId_u8].command_topic_pu8, topic_pu8)))
        {
            LIGHT_DEBUG("action on light %d with data: %s\r\n", lightId_u8,data_pu8);

            int r, i, j;
            jsmn_parser p;
            jsmntok_t t[128]; /* We expect no more than 128 tokens */
            jsmn_init(&p);
            r = jsmn_parse(&p, data_pu8, strlen(data_pu8), t,
                 sizeof(t) / sizeof(t[0]));
            if (r < 0) 
            {
                LIGHT_DEBUG("Failed to parse JSON: %d\n", r);
                return;
            }
            for (i = 1; i < r; i++) 
            {
                if (jsoneq(data_pu8, &t[i], "state") == 0u) 
                {
                    
                    uint8 stateDataLen_u8 = t[i+1].end - t[i+1].start;
                    uint8 stateData_au8[stateDataLen_u8];
                    stateData_au8[stateDataLen_u8] = 0u;
                    for (j = 0; j< stateDataLen_u8; j++)
                    {
                        stateData_au8[j] = data_pu8[j+t[i+1].start];
                    }

                    LIGHT_DEBUG("reQuest state is detected %s\r\n", stateData_au8);
                    if(0u == strcmp(stateData_au8, "ON"))
                    {
                        Light_SetState(lightId_u8, STD_ON);
                    }
                    else
                    {
                        Light_SetState(lightId_u8, STD_OFF);
                    }
                    i++;
                } else if (jsoneq(data_pu8, &t[i], "brightness") == 0u) 
                {
                    uint8 brighness_u8 = 0u; 
                    for (j = t[i+1].start; j< t[i+1].end; j++)
                    {
                        // LIGHT_DEBUG("brightness data %d\r\n", (data_pu8[j] - 48u));
                        brighness_u8 = brighness_u8*10u + (data_pu8[j] - 48u) ;
                    }
                    LIGHT_DEBUG("reQuest brighness is detected %d\r\n",brighness_u8);
                    Light_SetBrightness(lightId_u8, brighness_u8);
                    i++;
                } 
            }
            break;
        }
    }
};
#endif