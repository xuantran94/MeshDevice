#include "Rf.h"
#if( STD_ON == RF_CFG_MODULE_ACTIVE )
#include "easygpio.h"
#include "gpio.h"
#include "os.h"


void rf_gpio_intr_handler(void *dummy)
{
    uint32_t systemTime_u32 =0;
    static uint32_t lasTimeStamp_u32 =0;
    static uint32_t rfResult =0;
    uint32 duration_u32;

    uint32 gpio_status = GPIO_REG_READ(GPIO_STATUS_ADDRESS);
    GPIO_REG_WRITE(GPIO_STATUS_W1TC_ADDRESS, gpio_status & BIT(RF_PIN));
    systemTime_u32 = Os_GetTime_us(); 
    duration_u32 = systemTime_u32 -lasTimeStamp_u32;
    //Todo: make this time configuable
    //TODO: remove all the magic number
    
    uint8 rfId_u8;
    if(duration_u32 > 9000 && duration_u32 <11000) 
    {
        // RF_DEBUG("Result %lu\r\n", rfResult);
        for( rfId_u8 = 0u; rfId_u8 < RF_CFG_NUM; rfId_u8++)
        {
            if (rfResult == rfConfig_ast[rfId_u8].rfValue_u32)
            {
                RF_DEBUG("Press %d\r\n", rfId_u8);
                if( rfConfig_ast[rfId_u8].lighToggle_Id_u8 != LIGHT_ID_INVALID)
                {
                    Light_Toggle(rfConfig_ast[rfId_u8].lighToggle_Id_u8);
                }else
                {
                    uint8 topic_au8[255];
                    os_sprintf(topic_au8,"rf/%lu",rfConfig_ast[rfId_u8].rfValue_u32);
                    MqttIf_Publish(topic_au8,"aa",2, 0, 0);
                }
                break;
            }
            
        }
        rfResult =0;
    }
    //else
    {
        if(duration_u32 < 500)
        {
            rfResult = rfResult << 1;
        }
        if(duration_u32 > 500 && duration_u32 <1500)
        {
            rfResult = rfResult << 1;
            rfResult += 1;
        }
    }
    lasTimeStamp_u32 = systemTime_u32;
};

Std_ReturnType ICACHE_FLASH_ATTR rf_Init(void)
{
    easygpio_pinMode(RF_PIN, EASYGPIO_NOPULL, EASYGPIO_INPUT);
    easygpio_attachInterrupt(RF_PIN, EASYGPIO_PULLUP, rf_gpio_intr_handler, NULL);
    gpio_pin_intr_state_set(GPIO_ID_PIN(RF_PIN), GPIO_PIN_INTR_ANYEDGE);
    RF_DEBUG("Init done\r\n");
    return E_OK;
};
void ICACHE_FLASH_ATTR rfMqttConnected_CB (MQTT_Client* client )
{
    uint8 rfId_u8;
    uint8 topic_au8[255];
    for(rfId_u8=0u; rfId_u8 <RF_CFG_NUM; rfId_u8++)
    {
        if(rfConfig_ast[rfId_u8].lighToggle_Id_u8 != LIGHT_ID_INVALID)
        {
            
            os_sprintf(topic_au8,"rf/%lu",rfConfig_ast[rfId_u8].rfValue_u32);
            RF_DEBUG("subcribe %s\r\n",topic_au8);
            MQTT_Subscribe(client, topic_au8, 0u);
        }
    }
};
void ICACHE_FLASH_ATTR Rf_Data_ISR_Cfg(const char *topic_pu8, const char *data_pu8 )
{
    
    uint8 rfId_u8;
    uint8 topic_au8[255];
    for ( rfId_u8 =0; rfId_u8 < RF_CFG_NUM; rfId_u8++)
    {
        if(rfConfig_ast[rfId_u8].lighToggle_Id_u8 != LIGHT_ID_INVALID)
        {
            os_sprintf(topic_au8,"rf/%lu",rfConfig_ast[rfId_u8].rfValue_u32);
            if((0u == strcmp(topic_au8, topic_pu8)))
            {
                RF_DEBUG("action on rf %d\r\n", rfId_u8);
                Light_Toggle(rfConfig_ast[rfId_u8].lighToggle_Id_u8);
                break;
            }
        }
    }
};
#endif