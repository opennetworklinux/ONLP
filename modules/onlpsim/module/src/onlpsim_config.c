/************************************************************
 * <bsn.cl fy=2014 v=onl>
 *
 *        Copyright 2014, 2015 Big Switch Networks, Inc.
 *
 * Licensed under the Eclipse Public License, Version 1.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *        http://www.eclipse.org/legal/epl-v10.html
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the
 * License.
 *
 * </bsn.cl>
 ************************************************************
 *
 *
 *
 ***********************************************************/

#include <onlpsim/onlpsim_config.h>

/* <auto.start.cdefs(ONLPSIM_CONFIG_HEADER).source> */
#define __onlpsim_config_STRINGIFY_NAME(_x) #_x
#define __onlpsim_config_STRINGIFY_VALUE(_x) __onlpsim_config_STRINGIFY_NAME(_x)
onlpsim_config_settings_t onlpsim_config_settings[] =
{
#ifdef ONLPSIM_CONFIG_INCLUDE_LOGGING
    { __onlpsim_config_STRINGIFY_NAME(ONLPSIM_CONFIG_INCLUDE_LOGGING), __onlpsim_config_STRINGIFY_VALUE(ONLPSIM_CONFIG_INCLUDE_LOGGING) },
#else
{ ONLPSIM_CONFIG_INCLUDE_LOGGING(__onlpsim_config_STRINGIFY_NAME), "__undefined__" },
#endif
#ifdef ONLPSIM_CONFIG_LOG_OPTIONS_DEFAULT
    { __onlpsim_config_STRINGIFY_NAME(ONLPSIM_CONFIG_LOG_OPTIONS_DEFAULT), __onlpsim_config_STRINGIFY_VALUE(ONLPSIM_CONFIG_LOG_OPTIONS_DEFAULT) },
#else
{ ONLPSIM_CONFIG_LOG_OPTIONS_DEFAULT(__onlpsim_config_STRINGIFY_NAME), "__undefined__" },
#endif
#ifdef ONLPSIM_CONFIG_LOG_BITS_DEFAULT
    { __onlpsim_config_STRINGIFY_NAME(ONLPSIM_CONFIG_LOG_BITS_DEFAULT), __onlpsim_config_STRINGIFY_VALUE(ONLPSIM_CONFIG_LOG_BITS_DEFAULT) },
#else
{ ONLPSIM_CONFIG_LOG_BITS_DEFAULT(__onlpsim_config_STRINGIFY_NAME), "__undefined__" },
#endif
#ifdef ONLPSIM_CONFIG_LOG_CUSTOM_BITS_DEFAULT
    { __onlpsim_config_STRINGIFY_NAME(ONLPSIM_CONFIG_LOG_CUSTOM_BITS_DEFAULT), __onlpsim_config_STRINGIFY_VALUE(ONLPSIM_CONFIG_LOG_CUSTOM_BITS_DEFAULT) },
#else
{ ONLPSIM_CONFIG_LOG_CUSTOM_BITS_DEFAULT(__onlpsim_config_STRINGIFY_NAME), "__undefined__" },
#endif
#ifdef ONLPSIM_CONFIG_PORTING_STDLIB
    { __onlpsim_config_STRINGIFY_NAME(ONLPSIM_CONFIG_PORTING_STDLIB), __onlpsim_config_STRINGIFY_VALUE(ONLPSIM_CONFIG_PORTING_STDLIB) },
#else
{ ONLPSIM_CONFIG_PORTING_STDLIB(__onlpsim_config_STRINGIFY_NAME), "__undefined__" },
#endif
#ifdef ONLPSIM_CONFIG_PORTING_INCLUDE_STDLIB_HEADERS
    { __onlpsim_config_STRINGIFY_NAME(ONLPSIM_CONFIG_PORTING_INCLUDE_STDLIB_HEADERS), __onlpsim_config_STRINGIFY_VALUE(ONLPSIM_CONFIG_PORTING_INCLUDE_STDLIB_HEADERS) },
#else
{ ONLPSIM_CONFIG_PORTING_INCLUDE_STDLIB_HEADERS(__onlpsim_config_STRINGIFY_NAME), "__undefined__" },
#endif
#ifdef ONLPSIM_CONFIG_INCLUDE_UCLI
    { __onlpsim_config_STRINGIFY_NAME(ONLPSIM_CONFIG_INCLUDE_UCLI), __onlpsim_config_STRINGIFY_VALUE(ONLPSIM_CONFIG_INCLUDE_UCLI) },
#else
{ ONLPSIM_CONFIG_INCLUDE_UCLI(__onlpsim_config_STRINGIFY_NAME), "__undefined__" },
#endif
#ifdef ONLPSIM_CONFIG_SFP_COUNT
    { __onlpsim_config_STRINGIFY_NAME(ONLPSIM_CONFIG_SFP_COUNT), __onlpsim_config_STRINGIFY_VALUE(ONLPSIM_CONFIG_SFP_COUNT) },
#else
{ ONLPSIM_CONFIG_SFP_COUNT(__onlpsim_config_STRINGIFY_NAME), "__undefined__" },
#endif
    { NULL, NULL }
};
#undef __onlpsim_config_STRINGIFY_VALUE
#undef __onlpsim_config_STRINGIFY_NAME

const char*
onlpsim_config_lookup(const char* setting)
{
    int i;
    for(i = 0; onlpsim_config_settings[i].name; i++) {
        if(strcmp(onlpsim_config_settings[i].name, setting)) {
            return onlpsim_config_settings[i].value;
        }
    }
    return NULL;
}

int
onlpsim_config_show(struct aim_pvs_s* pvs)
{
    int i;
    for(i = 0; onlpsim_config_settings[i].name; i++) {
        aim_printf(pvs, "%s = %s\n", onlpsim_config_settings[i].name, onlpsim_config_settings[i].value);
    }
    return i;
}

/* <auto.end.cdefs(ONLPSIM_CONFIG_HEADER).source> */

