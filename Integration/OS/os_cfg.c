#include "os_cfg.h"


void ICACHE_FLASH_ATTR OS_mqttConnected_ISR_Cfg(MQTT_Client* client)
{
    Std_ReturnType retVal_u8;
    retVal_u8 = Light_Hass_Register(client);
    retVal_u8 = HassDevice_SetOnline(client);
    rfMqttConnected_CB(client);
};
Std_ReturnType ICACHE_FLASH_ATTR OS_mqttData_Init_Cfg(MQTT_Client* client)
{
    HassDevice_Init(client);
    MqttIf_Init(client);
    return E_OK;
}
void ICACHE_FLASH_ATTR OS_Init_Cfg(void)
{
    
    (void) HwAbPwm_Init();
    HwAbDio_Init();
    (void) Light_Init();
    (void) rf_Init();
    
};
void ICACHE_FLASH_ATTR OS_IniEnd_Cfg(void)
{

};
void ICACHE_FLASH_ATTR OS_Task_10ms_Cfg(void)
{

};
void ICACHE_FLASH_ATTR OS_Task_1ms_Cfg(void)
{

};

void ICACHE_FLASH_ATTR OS_10us_Task_Cfg(void)
{
    HwAbPwm_Proc_10us();
};
void ICACHE_FLASH_ATTR OS_100ms_Task_Cfg(void)
{
    Swadp_100ms();
}
void ICACHE_FLASH_ATTR OS_10s_Task_Cfg(void)
{
    HassDevice_Proc();
}
void ICACHE_FLASH_ATTR OS_mqttData_ISR_Cfg(const char *topic, const char *data )
{
    Light_Data_ISR_Cfg(topic, data);
    Rf_Data_ISR_Cfg(topic,data);

}