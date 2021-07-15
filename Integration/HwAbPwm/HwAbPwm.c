#include "HwAbPwm.h"
#if( STD_ON == HWABPWM_CFG_MODULE_ACTIVE )
/*Todo: remove this initialization. This shoul belong the Mcal */
#include "easygpio.h"
Std_ReturnType ICACHE_FLASH_ATTR HwAbPwm_SetDuty (uint8 hwAbPwmId_u8, uint8 duty_u8);

hwAbPwm_tst hwAbPwm_ast[HWABPWM_CFG_NUM];

Std_ReturnType ICACHE_FLASH_ATTR HwAbPwm_Init (void)
{
    HWABPWM_DEBUG("Init\r\n");
    Std_ReturnType retVal_u8 = E_NOT_OK;
    uint8 hwAbPwmId_u8;
    for( hwAbPwmId_u8 =0; hwAbPwmId_u8 < HWABPWM_CFG_NUM; hwAbPwmId_u8++)
    {
        //Set the GPIO as output
        /*Todo: remove this initialization. This shoul belong the Mcal */
        easygpio_pinMode(hwAbPwmConfig_ast[hwAbPwmId_u8].connected_pin_u8, EASYGPIO_NOPULL, EASYGPIO_OUTPUT);
        easygpio_outputSet(hwAbPwmConfig_ast[hwAbPwmId_u8].connected_pin_u8, STD_ON);
        //Set the duty as init duty
        retVal_u8 = HwAbPwm_SetDuty(hwAbPwmId_u8, hwAbPwmConfig_ast[hwAbPwmId_u8].initDuty_u8);
    }

    return retVal_u8;
};
Std_ReturnType ICACHE_FLASH_ATTR HwAbPwm_SetDuty (uint8 hwAbPwmId_u8, uint8 duty_u8)
{
    HWABPWM_DEBUG("Set duty to %d\r\n",duty_u8);
    hwAbPwm_ast[hwAbPwmId_u8].duty_u8 = duty_u8;
    return E_OK;
};
void ICACHE_FLASH_ATTR HwAbPwm_Proc_10us(void)
{
    uint8 hwAbPwmId_u8 =0u;
    static uint8 hwAbPwmPer_u8 =0;
    hwAbPwmPer_u8++;

    if (100u == hwAbPwmPer_u8)
    {
        hwAbPwmPer_u8=0;
        for( hwAbPwmId_u8 =0; hwAbPwmId_u8 < HWABPWM_CFG_NUM; hwAbPwmId_u8++)
        {
            easygpio_outputSet(hwAbPwmConfig_ast[hwAbPwmId_u8].connected_pin_u8, STD_ON);
        }
    }
    else
    {
        for( hwAbPwmId_u8 =0; hwAbPwmId_u8 < HWABPWM_CFG_NUM; hwAbPwmId_u8++)
        {
            if( hwAbPwmPer_u8 == hwAbPwm_ast[hwAbPwmId_u8].duty_u8)
            {
                easygpio_outputSet(hwAbPwmConfig_ast[hwAbPwmId_u8].connected_pin_u8, STD_OFF);
            }
        }
    } 
}
#endif