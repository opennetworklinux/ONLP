/**************************************************************************//**
 *
 *
 *
 *****************************************************************************/
#include <onlp/onlp_config.h>

/* <auto.start.cdefs(ONLP_CONFIG_HEADER).source> */
#define __onlp_config_STRINGIFY_NAME(_x) #_x
#define __onlp_config_STRINGIFY_VALUE(_x) __onlp_config_STRINGIFY_NAME(_x)
onlp_config_settings_t onlp_config_settings[] =
{
#ifdef ONLP_CONFIG_INCLUDE_LOGGING
    { __onlp_config_STRINGIFY_NAME(ONLP_CONFIG_INCLUDE_LOGGING), __onlp_config_STRINGIFY_VALUE(ONLP_CONFIG_INCLUDE_LOGGING) },
#else
{ ONLP_CONFIG_INCLUDE_LOGGING(__onlp_config_STRINGIFY_NAME), "__undefined__" },
#endif
#ifdef ONLP_CONFIG_LOG_OPTIONS_DEFAULT
    { __onlp_config_STRINGIFY_NAME(ONLP_CONFIG_LOG_OPTIONS_DEFAULT), __onlp_config_STRINGIFY_VALUE(ONLP_CONFIG_LOG_OPTIONS_DEFAULT) },
#else
{ ONLP_CONFIG_LOG_OPTIONS_DEFAULT(__onlp_config_STRINGIFY_NAME), "__undefined__" },
#endif
#ifdef ONLP_CONFIG_LOG_BITS_DEFAULT
    { __onlp_config_STRINGIFY_NAME(ONLP_CONFIG_LOG_BITS_DEFAULT), __onlp_config_STRINGIFY_VALUE(ONLP_CONFIG_LOG_BITS_DEFAULT) },
#else
{ ONLP_CONFIG_LOG_BITS_DEFAULT(__onlp_config_STRINGIFY_NAME), "__undefined__" },
#endif
#ifdef ONLP_CONFIG_LOG_CUSTOM_BITS_DEFAULT
    { __onlp_config_STRINGIFY_NAME(ONLP_CONFIG_LOG_CUSTOM_BITS_DEFAULT), __onlp_config_STRINGIFY_VALUE(ONLP_CONFIG_LOG_CUSTOM_BITS_DEFAULT) },
#else
{ ONLP_CONFIG_LOG_CUSTOM_BITS_DEFAULT(__onlp_config_STRINGIFY_NAME), "__undefined__" },
#endif
#ifdef ONLP_CONFIG_PORTING_STDLIB
    { __onlp_config_STRINGIFY_NAME(ONLP_CONFIG_PORTING_STDLIB), __onlp_config_STRINGIFY_VALUE(ONLP_CONFIG_PORTING_STDLIB) },
#else
{ ONLP_CONFIG_PORTING_STDLIB(__onlp_config_STRINGIFY_NAME), "__undefined__" },
#endif
#ifdef ONLP_CONFIG_PORTING_INCLUDE_STDLIB_HEADERS
    { __onlp_config_STRINGIFY_NAME(ONLP_CONFIG_PORTING_INCLUDE_STDLIB_HEADERS), __onlp_config_STRINGIFY_VALUE(ONLP_CONFIG_PORTING_INCLUDE_STDLIB_HEADERS) },
#else
{ ONLP_CONFIG_PORTING_INCLUDE_STDLIB_HEADERS(__onlp_config_STRINGIFY_NAME), "__undefined__" },
#endif
#ifdef ONLP_CONFIG_INCLUDE_UCLI
    { __onlp_config_STRINGIFY_NAME(ONLP_CONFIG_INCLUDE_UCLI), __onlp_config_STRINGIFY_VALUE(ONLP_CONFIG_INCLUDE_UCLI) },
#else
{ ONLP_CONFIG_INCLUDE_UCLI(__onlp_config_STRINGIFY_NAME), "__undefined__" },
#endif
#ifdef ONLP_CONFIG_INCLUDE_PLATFORM_ERROR_CHECK
    { __onlp_config_STRINGIFY_NAME(ONLP_CONFIG_INCLUDE_PLATFORM_ERROR_CHECK), __onlp_config_STRINGIFY_VALUE(ONLP_CONFIG_INCLUDE_PLATFORM_ERROR_CHECK) },
#else
{ ONLP_CONFIG_INCLUDE_PLATFORM_ERROR_CHECK(__onlp_config_STRINGIFY_NAME), "__undefined__" },
#endif
#ifdef ONLP_CONFIG_INCLUDE_SHLOCK_GLOBAL_INIT
    { __onlp_config_STRINGIFY_NAME(ONLP_CONFIG_INCLUDE_SHLOCK_GLOBAL_INIT), __onlp_config_STRINGIFY_VALUE(ONLP_CONFIG_INCLUDE_SHLOCK_GLOBAL_INIT) },
#else
{ ONLP_CONFIG_INCLUDE_SHLOCK_GLOBAL_INIT(__onlp_config_STRINGIFY_NAME), "__undefined__" },
#endif
    { NULL, NULL }
};
#undef __onlp_config_STRINGIFY_VALUE
#undef __onlp_config_STRINGIFY_NAME

const char*
onlp_config_lookup(const char* setting)
{
    int i;
    for(i = 0; onlp_config_settings[i].name; i++) {
        if(strcmp(onlp_config_settings[i].name, setting)) {
            return onlp_config_settings[i].value;
        }
    }
    return NULL;
}

int
onlp_config_show(struct aim_pvs_s* pvs)
{
    int i;
    for(i = 0; onlp_config_settings[i].name; i++) {
        aim_printf(pvs, "%s = %s\n", onlp_config_settings[i].name, onlp_config_settings[i].value);
    }
    return i;
}

/* <auto.end.cdefs(ONLP_CONFIG_HEADER).source> */

