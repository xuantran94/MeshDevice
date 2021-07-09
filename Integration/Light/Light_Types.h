#ifndef _LIGHT_TYPES_H_
#define _LIGHT_TYPES_H_

#include "Std_Types.h"

typedef struct
{
    // Std_ReturnType (*const setLight_cpfct)(rba_IoSigDio_idSignal_tu16 idSignal_u16,
    //                                       rba_IoSigDio_stSignal_ten  stSignal_en);
    uint8*  lightName;
    bool    isLightBrighness;

}LightConfig_tst;

#endif