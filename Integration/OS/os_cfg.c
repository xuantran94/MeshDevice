#include "os_cfg.h"


Std_ReturnType ICACHE_FLASH_ATTR OS_mqttConnected_ISR_Cfg(MQTT_Client* client)
{
    Std_ReturnType retVal_u8;
    retVal_u8 = Light_Hass_Register(client);
};
void ICACHE_FLASH_ATTR OS_Init_Cfg(void)
{
#if( STD_ON == LIGHT_CFG_MODULE_ACTIVE )
    Light_Init();
#endif
#if( STD_ON == HWABPWM_CFG_MODULE_ACTIVE )
    HwAbPwm_Init();
#endif
#if( STD_ON == HWABDIO_CFG_MODULE_ACTIVE )
    HwAbDio_Init();
#endif
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
#if( STD_ON == HWABPWM_CFG_MODULE_ACTIVE )
    HwAbPwm_Proc_10us();
#endif
};
void ICACHE_FLASH_ATTR OS_100ms_Task_Cfg(void)
{
    Swadp_100ms();
}