#include "Light_Cfg.h"
#if (LIGHT_CFG_MODULE_ACTIVE == STD_ON) 
const LightConfig_tst lightConfig_ast[LIGHT_CFG_NUM_LIGHTS] =
{
  {
      //DenNhaBep
      "DenNhaBep",
      Light_state_off,
      12,
      False,
      HwAbDio_Light_DenNhaBep,
  },

};
#endif