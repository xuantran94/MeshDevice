#ifndef _HWABPWM_H_
#define _HWABPWM_H_

#include "HwAbPwm_Cfg.h"

#if( STD_ON == HWABPWM_CFG_MODULE_ACTIVE )

Std_ReturnType ICACHE_FLASH_ATTR HwAbPwm_Init (void);
Std_ReturnType ICACHE_FLASH_ATTR HwAbPwm_SetDuty (uint8 hwAbPwmId_u8, uint8 duty_u8);
void ICACHE_FLASH_ATTR           HwAbPwm_Proc_10us(void);
#endif

#endif