/**************************************************************************//**
 *
 *
 *
 *****************************************************************************/
#include <onlpie/onlpie_config.h>

/* <auto.start.cdefs(ONLPIE_CONFIG_HEADER).source> */
#define __onlpie_config_STRINGIFY_NAME(_x) #_x
#define __onlpie_config_STRINGIFY_VALUE(_x) __onlpie_config_STRINGIFY_NAME(_x)
onlpie_config_settings_t onlpie_config_settings[] =
{
#ifdef ONLPIE_CONFIG_INCLUDE_LOGGING
    { __onlpie_config_STRINGIFY_NAME(ONLPIE_CONFIG_INCLUDE_LOGGING), __onlpie_config_STRINGIFY_VALUE(ONLPIE_CONFIG_INCLUDE_LOGGING) },
#else
{ ONLPIE_CONFIG_INCLUDE_LOGGING(__onlpie_config_STRINGIFY_NAME), "__undefined__" },
#endif
#ifdef ONLPIE_CONFIG_LOG_OPTIONS_DEFAULT
    { __onlpie_config_STRINGIFY_NAME(ONLPIE_CONFIG_LOG_OPTIONS_DEFAULT), __onlpie_config_STRINGIFY_VALUE(ONLPIE_CONFIG_LOG_OPTIONS_DEFAULT) },
#else
{ ONLPIE_CONFIG_LOG_OPTIONS_DEFAULT(__onlpie_config_STRINGIFY_NAME), "__undefined__" },
#endif
#ifdef ONLPIE_CONFIG_LOG_BITS_DEFAULT
    { __onlpie_config_STRINGIFY_NAME(ONLPIE_CONFIG_LOG_BITS_DEFAULT), __onlpie_config_STRINGIFY_VALUE(ONLPIE_CONFIG_LOG_BITS_DEFAULT) },
#else
{ ONLPIE_CONFIG_LOG_BITS_DEFAULT(__onlpie_config_STRINGIFY_NAME), "__undefined__" },
#endif
#ifdef ONLPIE_CONFIG_LOG_CUSTOM_BITS_DEFAULT
    { __onlpie_config_STRINGIFY_NAME(ONLPIE_CONFIG_LOG_CUSTOM_BITS_DEFAULT), __onlpie_config_STRINGIFY_VALUE(ONLPIE_CONFIG_LOG_CUSTOM_BITS_DEFAULT) },
#else
{ ONLPIE_CONFIG_LOG_CUSTOM_BITS_DEFAULT(__onlpie_config_STRINGIFY_NAME), "__undefined__" },
#endif
#ifdef ONLPIE_CONFIG_PORTING_STDLIB
    { __onlpie_config_STRINGIFY_NAME(ONLPIE_CONFIG_PORTING_STDLIB), __onlpie_config_STRINGIFY_VALUE(ONLPIE_CONFIG_PORTING_STDLIB) },
#else
{ ONLPIE_CONFIG_PORTING_STDLIB(__onlpie_config_STRINGIFY_NAME), "__undefined__" },
#endif
#ifdef ONLPIE_CONFIG_PORTING_INCLUDE_STDLIB_HEADERS
    { __onlpie_config_STRINGIFY_NAME(ONLPIE_CONFIG_PORTING_INCLUDE_STDLIB_HEADERS), __onlpie_config_STRINGIFY_VALUE(ONLPIE_CONFIG_PORTING_INCLUDE_STDLIB_HEADERS) },
#else
{ ONLPIE_CONFIG_PORTING_INCLUDE_STDLIB_HEADERS(__onlpie_config_STRINGIFY_NAME), "__undefined__" },
#endif
#ifdef ONLPIE_CONFIG_INCLUDE_UCLI
    { __onlpie_config_STRINGIFY_NAME(ONLPIE_CONFIG_INCLUDE_UCLI), __onlpie_config_STRINGIFY_VALUE(ONLPIE_CONFIG_INCLUDE_UCLI) },
#else
{ ONLPIE_CONFIG_INCLUDE_UCLI(__onlpie_config_STRINGIFY_NAME), "__undefined__" },
#endif
    { NULL, NULL }
};
#undef __onlpie_config_STRINGIFY_VALUE
#undef __onlpie_config_STRINGIFY_NAME

const char*
onlpie_config_lookup(const char* setting)
{
    int i;
    for(i = 0; onlpie_config_settings[i].name; i++) {
        if(strcmp(onlpie_config_settings[i].name, setting)) {
            return onlpie_config_settings[i].value;
        }
    }
    return NULL;
}

int
onlpie_config_show(struct aim_pvs_s* pvs)
{
    int i;
    for(i = 0; onlpie_config_settings[i].name; i++) {
        aim_printf(pvs, "%s = %s\n", onlpie_config_settings[i].name, onlpie_config_settings[i].value);
    }
    return i;
}

/* <auto.end.cdefs(ONLPIE_CONFIG_HEADER).source> */

