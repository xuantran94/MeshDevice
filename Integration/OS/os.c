#include "os.h"
#include "osapi.h"


void ICACHE_FLASH_ATTR OS_10ms_Task(void *arg);
void ICACHE_FLASH_ATTR OS_20ms_Task(void *arg);
void ICACHE_FLASH_ATTR OS_1ms_Task(void *arg);

static os_timer_t ptimer_10ms_Task;
Std_ReturnType ICACHE_FLASH_ATTR OS_Init(void)
{
    os_printf("OS_Init\r\n");

    return E_OK;
};
Std_ReturnType ICACHE_FLASH_ATTR OS_Ini (void)
{
     return E_OK;
};
Std_ReturnType ICACHE_FLASH_ATTR OS_IniEnd(void)
{
    os_printf("OS_IniEnd\r\n");
    os_timer_setfn(&ptimer_10ms_Task, OS_10ms_Task, 0);
    os_timer_arm(&ptimer_10ms_Task, 10, true);
    return E_OK;
};
/* cyclic tasks */

void ICACHE_FLASH_ATTR OS_100ms_Task(void *arg)
{
    //os_printf("OS_100ms\r\n");
};
void ICACHE_FLASH_ATTR OS_10ms_Task(void *arg)
{
    //os_printf("OS_10ms\r\n");
};
void ICACHE_FLASH_ATTR OS_20ms_Task(void *arg)
{

};
void ICACHE_FLASH_ATTR OS_1ms_Task(void *arg)
{

};
/* ISRs */
Std_ReturnType ICACHE_FLASH_ATTR OS_mqttConnected_ISR(MQTT_Client* client)
{
    OS_mqttConnected_ISR_Cfg(client);
};
Std_ReturnType ICACHE_FLASH_ATTR OS_mqttData_ISR(const char *topic, uint32_t topic_len, const char *data, uint32_t data_len)
{

};


