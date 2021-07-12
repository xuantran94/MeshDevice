#ifndef _HWABPWM_H_
#define _HWABPWM_H_

#include "HwAbPwm_Cfg.h"
#include "osapi.h"

#if( STD_ON == HWABPWM_CFG_MODULE_ACTIVE )
Std_ReturnType ICACHE_FLASH_ATTR HwAbPwm_Init (void);
Std_ReturnType ICACHE_FLASH_ATTR HwAbPwm_SetDuty (uint8 hwAbPwmId_u8, uint8 duty_u8);
void ICACHE_FLASH_ATTR           HwAbPwm_Proc_10us(void);
#else
#define HwAbPwm_Init                E_NOT_OK
#define HwAbPwm_SetDuty (x,  y)     E_NOT_OK
#define HwAbPwm_Proc_10us()
#endif

#if (HWABPWM_CFG_DEBUG == STD_ON)
#define HWABPWM_DEBUG( format, ... ) os_printf("[HwAbPwm]: "); os_printf( format, ## __VA_ARGS__ )
#else
#define HWABPWM_DEBUG( format, ... ) 
#endif

#endif