/**************************************************************************//**
 *
 *
 *
 *****************************************************************************/
#include <onlp_platform_defaults/onlp_platform_defaults_config.h>

#include "onlp_platform_defaults_log.h"

static int
datatypes_init__(void)
{
#define ONLP_PLATFORM_DEFAULTS_ENUMERATION_ENTRY(_enum_name, _desc)     AIM_DATATYPE_MAP_REGISTER(_enum_name, _enum_name##_map, _desc,                               AIM_LOG_INTERNAL);
#include <onlp_platform_defaults/onlp_platform_defaults.x>
    return 0;
}

void __onlp_platform_defaults_module_init__(void)
{
    AIM_LOG_STRUCT_REGISTER();
    datatypes_init__();
}

