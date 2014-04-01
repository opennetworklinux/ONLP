/**************************************************************************//**
 *
 * onlp_platform_defaults Internal Header
 *
 *****************************************************************************/
#ifndef __ONLP_PLATFORM_DEFAULTS_INT_H__
#define __ONLP_PLATFORM_DEFAULTS_INT_H__

#include <onlp_platform_defaults/onlp_platform_defaults_config.h>
#include "onlp_platform_defaults_log.h"

#define __ONLP_DEFAULTI __attribute__((weak))

#define ONLP_SYSI_PLATFORM_NAME_DEFAULT "onlp-sysi-platform-default"


#define __ONLP_DEFAULTI_IMPLEMENTATION(__f)             \
    int __ONLP_DEFAULTI __f                             \
    {                                                   \
        AIM_LOG_WARN("using default %s", __func__);     \
        return ONLP_STATUS_E_UNSUPPORTED;               \
    }

#define __ONLP_DEFAULTI_VIMPLEMENTATION(__f)             \
    void __ONLP_DEFAULTI __f                             \
    {                                                    \
        AIM_LOG_WARN("using default %s", __func__);      \
    }



#endif /* __ONLP_PLATFORM_DEFAULTS_INT_H__ */
