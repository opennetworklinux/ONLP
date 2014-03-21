/**************************************************************************//**
 *
 * onlp Internal Header
 *
 *****************************************************************************/
#ifndef __ONLP_INT_H__
#define __ONLP_INT_H__

#include <onlp/onlp_config.h>
#include <onlp/onlp.h>
#include "onlp_log.h"

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

#endif /* __ONLP_INT_H__ */
