#include "os_cfg.h"

Std_ReturnType ICACHE_FLASH_ATTR OS_mqttConnected_ISR_Cfg(MQTT_Client* client)
{
    Std_ReturnType retVal_u8;
    retVal_u8 = Light_Hass_Register(client);
};
void ICACHE_FLASH_ATTR OS_Init_Cfg(void)
{
    HwAbPwm_Init();
};
void ICACHE_FLASH_ATTR OS_IniEnd_Cfg(void)
{
    // HwAbPwm_Init();
};
void ICACHE_FLASH_ATTR OS_Task_10ms_Cfg(void)
{
    // HwAbPwm_Proc_10ms();
}
void ICACHE_FLASH_ATTR OS_Task_1ms_Cfg(void)
{
    // HwAbPwm_Proc_1ms();
}

void ICACHE_FLASH_ATTR OS_10us_Task_Cfg(void)
{
    HwAbPwm_Proc_10us();
}