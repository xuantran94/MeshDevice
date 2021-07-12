#ifndef _LIGHT_TYPES_H_
#define _LIGHT_TYPES_H_

#include "Std_Types.h"



typedef struct
{
    const uint8*                    lightName_pu8;
    const uint8*                    command_topic_pu8;
    const uint8*                    state_topic_pu8;
    const uint8                     light_default_state_en;
    const uint8                     connected_pin_u8;
    const bool                      isLightBrighness_b;
    const uint8                     driverSignalId_u8;

}LightConfig_tst;

typedef struct
{
    uint8                     state_u8;
    uint8                     duty_u8;
}Light_tst;



#endif