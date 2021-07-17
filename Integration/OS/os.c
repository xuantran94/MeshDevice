#define USE_US_TIMER
#include "os.h"
#include "osapi.h"


void ICACHE_FLASH_ATTR OS_10ms_Task(void *arg);
void ICACHE_FLASH_ATTR OS_100ms_Task(void *arg);
void ICACHE_FLASH_ATTR OS_20ms_Task(void *arg);
void ICACHE_FLASH_ATTR OS_1ms_Task(void *arg);
void ICACHE_FLASH_ATTR OS_10us_Task(void *arg);
void ICACHE_FLASH_ATTR OS_10s_Task(void *arg);

static os_timer_t ptimer_100ms_Task;
static os_timer_t ptimer_10ms_Task;
static os_timer_t ptimer_1ms_Task;

static os_timer_t ptimer_10us_Task;
static os_timer_t ptimer_10s_Task;

void ICACHE_FLASH_ATTR Os_shutdown(void)
{
    os_timer_disarm(&ptimer_100ms_Task);
    os_timer_disarm(&ptimer_10ms_Task);
    os_timer_disarm(&ptimer_1ms_Task);
    os_timer_disarm(&ptimer_10us_Task);
    os_timer_disarm(&ptimer_10s_Task);
    Rf_Shutdown();
}
void ICACHE_FLASH_ATTR Os_Start(void)
{
    os_timer_setfn(&ptimer_10ms_Task, OS_10ms_Task, 0);
    os_timer_arm(&ptimer_10ms_Task, 10, true);

    os_timer_setfn(&ptimer_10us_Task, OS_10us_Task, 0);
    os_timer_arm_us(&ptimer_10us_Task, 10, true);

    os_timer_setfn(&ptimer_100ms_Task, OS_100ms_Task, 0);
    os_timer_arm(&ptimer_100ms_Task, 100, true);

    os_timer_setfn(&ptimer_10s_Task, OS_10s_Task, 0);
    os_timer_arm(&ptimer_10s_Task, 10000, true);
}

Std_ReturnType ICACHE_FLASH_ATTR OS_Init(void)
{
    os_printf("OS_Init\r\n");
    OS_Init_Cfg();
    return E_OK;
};
Std_ReturnType ICACHE_FLASH_ATTR OS_Ini (void)
{
    
    return E_OK;
};
void ICACHE_FLASH_ATTR OS_100ms_Task(void *arg)
{   
    OS_100ms_Task_Cfg();
};
void ICACHE_FLASH_ATTR OS_10s_Task(void *arg)
{
    OS_10s_Task_Cfg();
};
Std_ReturnType ICACHE_FLASH_ATTR OS_IniEnd(void)
{
    OS_IniEnd_Cfg();
    Os_Start();

    return E_OK;
};

void ICACHE_FLASH_ATTR OS_10ms_Task(void *arg)
{
    OS_Task_10ms_Cfg();
};
void ICACHE_FLASH_ATTR OS_20ms_Task(void *arg)
{

};
void ICACHE_FLASH_ATTR OS_1ms_Task(void *arg)
{

};
void ICACHE_FLASH_ATTR OS_10us_Task(void *arg)
{
    OS_10us_Task_Cfg();
};
/* ISRs */
void ICACHE_FLASH_ATTR OS_mqttConnected_ISR(MQTT_Client* client)
{
    OS_mqttConnected_ISR_Cfg(client);
};
void ICACHE_FLASH_ATTR OS_mqttData_ISR(const char *topic, uint32_t topic_len, const char *data, uint32_t data_len)
{
    uint8 lc_topic_pu8[topic_len];
    uint8 lc_data_pu8[data_len];
    uint32 i;
    lc_topic_pu8[topic_len] = 0u;
    lc_data_pu8[data_len] = 0u;
    for ( i = 0; i < topic_len; i++)
    {
        lc_topic_pu8[i] = topic[i];
    }
    for ( i = 0; i < data_len; i++)
    {
        lc_data_pu8[i] = data[i];
    }
    OS_mqttData_ISR_Cfg(lc_topic_pu8, lc_data_pu8);
};

void ICACHE_FLASH_ATTR OS_mqttData_Init(MQTT_Client* client)
{
    OS_mqttData_Init_Cfg(client);
    
};
uint32 ICACHE_FLASH_ATTR Os_GetTime_us(void)
{
    return system_get_time();
}


