#ifndef _LIGHT_TYPES_H_
#define _LIGHT_TYPES_H_

#include "Std_Types.h"

typedef enum
{
    Light_state_off = STD_OFF,
    Light_state_on  = STD_ON,
} Light_state_ten;

typedef struct
{
    // Std_ReturnType (*const setLight_cpfct)(rba_IoSigDio_idSignal_tu16 idSignal_u16,
    //                                       rba_IoSigDio_stSignal_ten  stSignal_en);
    const uint8*                    lightName_pu8;
    const Light_state_ten           Light_default_state_en;
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