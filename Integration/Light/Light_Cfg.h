#ifndef _LIGHT_CFG_H_
#define _LIGHT_CFG_H_

#include "Light_Types.h"
#include "HwAbPwm.h"
#include "HwAbDio.h"

#define LIGHT_CFG_MODULE_ACTIVE    STD_ON
#define LIGHT_CFG_MQTT    STD_ON
#define LIGHT_CFG_DEBUG    STD_OFF
#define LIGHT_CFG_INFO    STD_ON
#define LIGHT_CFG_NUM_LIGHTS    1u

#if (LIGHT_CFG_MODULE_ACTIVE == STD_ON) 

#define Light_DenNhaBep   0u

extern const LightConfig_tst lightConfig_ast[LIGHT_CFG_NUM_LIGHTS];
#endif

#endif