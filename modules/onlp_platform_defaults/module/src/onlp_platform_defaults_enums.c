/**************************************************************************//**
 *
 *
 *
 *****************************************************************************/
#include <onlp_platform_defaults/onlp_platform_defaults_config.h>
#include "onlp_platform_defaults_int.h"

/* <auto.start.enum(ALL).source> */
aim_map_si_t onlp_platform_defaults_log_flag_map[] =
{
    { "called", ONLP_PLATFORM_DEFAULTS_LOG_FLAG_CALLED },
    { NULL, 0 }
};

aim_map_si_t onlp_platform_defaults_log_flag_desc_map[] =
{
    { "None", ONLP_PLATFORM_DEFAULTS_LOG_FLAG_CALLED },
    { NULL, 0 }
};

const char*
onlp_platform_defaults_log_flag_name(onlp_platform_defaults_log_flag_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_platform_defaults_log_flag_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_platform_defaults_log_flag'";
    }
}

int
onlp_platform_defaults_log_flag_value(const char* str, onlp_platform_defaults_log_flag_t* e, int substr)
{
    int i;
    AIM_REFERENCE(substr);
    if(aim_map_si_s(&i, str, onlp_platform_defaults_log_flag_map, 0)) {
        /* Enum Found */
        *e = i;
        return 0;
    }
    else {
        return -1;
    }
}

const char*
onlp_platform_defaults_log_flag_desc(onlp_platform_defaults_log_flag_t e)
{
    const char* name;
    if(aim_map_si_i(&name, e, onlp_platform_defaults_log_flag_desc_map, 0)) {
        return name;
    }
    else {
        return "-invalid value for enum type 'onlp_platform_defaults_log_flag'";
    }
}

/* <auto.end.enum(ALL).source> */

