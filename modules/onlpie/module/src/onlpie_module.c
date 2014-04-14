/**************************************************************************//**
 *
 *
 *
 *****************************************************************************/
#include <onlpie/onlpie_config.h>

#include "onlpie_log.h"

static int
datatypes_init__(void)
{
#define ONLPIE_ENUMERATION_ENTRY(_enum_name, _desc)     AIM_DATATYPE_MAP_REGISTER(_enum_name, _enum_name##_map, _desc,                               AIM_LOG_INTERNAL);
#include <onlpie/onlpie.x>
    return 0;
}

void __onlpie_module_init__(void)
{
    AIM_LOG_STRUCT_REGISTER();
    datatypes_init__();
}

int __onlp_platform_version__ = 1;
