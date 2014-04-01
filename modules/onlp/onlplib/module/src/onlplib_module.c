/**************************************************************************//**
 *
 *
 *
 *****************************************************************************/
#include <onlplib/onlplib_config.h>

#include "onlplib_log.h"

static int
datatypes_init__(void)
{
#define ONLPLIB_ENUMERATION_ENTRY(_enum_name, _desc)     AIM_DATATYPE_MAP_REGISTER(_enum_name, _enum_name##_map, _desc,                               AIM_LOG_INTERNAL);
#include <onlplib/onlplib.x>
    return 0;
}

void __onlplib_module_init__(void)
{
    AIM_LOG_STRUCT_REGISTER();
    datatypes_init__();
}

