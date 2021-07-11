#include "HwAbDio.h"
#if( STD_ON == HWABDIO_CFG_MODULE_ACTIVE )
#include "easygpio.h"

Std_ReturnType ICACHE_FLASH_ATTR HwAbDio_Init (void)
{
    uint8 hwAbDioId_u8;
    for( hwAbDioId_u8 =0; hwAbDioId_u8 < HWABDIO_CFG_NUM; hwAbDioId_u8++)
    {
        //Set the GPIO as output
        /*Todo: remove this initialization. This shoul belong the Mcal */
        easygpio_pinMode(hwAbDioConfig_ast[hwAbDioId_u8].connected_pin_u8, EASYGPIO_NOPULL, EASYGPIO_OUTPUT);
        easygpio_outputSet(hwAbDioConfig_ast[hwAbDioId_u8].connected_pin_u8, hwAbDioConfig_ast[hwAbDioId_u8].initState_u8 );
    }
};
Std_ReturnType ICACHE_FLASH_ATTR HwAbDio_Set (uint8 hwAbDioId_u8, uint8 state_u8)
{
    easygpio_outputSet(hwAbDioConfig_ast[hwAbDioId_u8].connected_pin_u8, state_u8);
};
Std_ReturnType ICACHE_FLASH_ATTR HwAbDio_Get (uint8 hwAbDioId_u8, uint8* state_u8)
{
    *state_u8 = easygpio_inputGet(hwAbDioConfig_ast[hwAbDioId_u8].connected_pin_u8); 
};
#endif