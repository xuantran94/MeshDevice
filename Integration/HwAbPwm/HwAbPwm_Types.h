#ifndef _HWABPWM_TYPES_H_
#define _HWABPWM_TYPES_H_

#include "Std_Types.h"

typedef struct
{
    // Std_ReturnType (*const setLight_cpfct)(rba_IoSigDio_idSignal_tu16 idSignal_u16,
    //                                       rba_IoSigDio_stSignal_ten  stSignal_en);
    const uint8                     connected_pin_u8;
    const uint8                     initDuty_u8;

}hwAbPwmConfig_tst;

typedef struct
{
    uint8                     duty_u8;
}hwAbPwm_tst;
#endif