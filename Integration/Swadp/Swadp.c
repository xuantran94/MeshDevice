#include "Swadp.h"
Std_ReturnType ICACHE_FLASH_ATTR Swadp_Init  (void)
{
    return E_NOT_OK;
};
Std_ReturnType ICACHE_FLASH_ATTR Swadp_Ini   (void)
{
    return E_NOT_OK;
};
void ICACHE_FLASH_ATTR Swadp_100ms (void)
{
    Light_Toggle(0);
    //os_printf("swadp_100ms");
};