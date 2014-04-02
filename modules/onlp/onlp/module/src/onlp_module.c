/**************************************************************************//**
 *
 *
 *
 *****************************************************************************/
#include <onlp/onlp_config.h>

#include "onlp_log.h"
#include <onlplib/shlocks.h>

static int
datatypes_init__(void)
{
#define ONLP_ENUMERATION_ENTRY(_enum_name, _desc)     AIM_DATATYPE_MAP_REGISTER(_enum_name, _enum_name##_map, _desc,                               AIM_LOG_INTERNAL);
#include <onlp/onlp.x>
    return 0;
}

void __onlp_module_init__(void)
{
    AIM_LOG_STRUCT_REGISTER();
    datatypes_init__();

#if ONLP_CONFIG_INCLUDE_SHLOCK_GLOBAL_INIT == 1
    onlp_shlock_global_init();
#endif

    {
        extern int __onlp_platform_version__;
        extern int __onlp_platform_version_default__;
        __onlp_platform_version_default__ = __onlp_platform_version__;
    }
}

