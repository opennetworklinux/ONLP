/**************************************************************************//**
 *
 * @file
 * @brief onlp_platform_defaults Porting Macros.
 *
 * @addtogroup onlp_platform_defaults-porting
 * @{
 *
 *****************************************************************************/
#ifndef __ONLP_PLATFORM_DEFAULTS_PORTING_H__
#define __ONLP_PLATFORM_DEFAULTS_PORTING_H__


/* <auto.start.portingmacro(ALL).define> */
#if ONLP_PLATFORM_DEFAULTS_CONFIG_PORTING_INCLUDE_STDLIB_HEADERS == 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <memory.h>
#endif

#ifndef ONLP_PLATFORM_DEFAULTS_MEMSET
    #if defined(GLOBAL_MEMSET)
        #define ONLP_PLATFORM_DEFAULTS_MEMSET GLOBAL_MEMSET
    #elif ONLP_PLATFORM_DEFAULTS_CONFIG_PORTING_STDLIB == 1
        #define ONLP_PLATFORM_DEFAULTS_MEMSET memset
    #else
        #error The macro ONLP_PLATFORM_DEFAULTS_MEMSET is required but cannot be defined.
    #endif
#endif

#ifndef ONLP_PLATFORM_DEFAULTS_MEMCPY
    #if defined(GLOBAL_MEMCPY)
        #define ONLP_PLATFORM_DEFAULTS_MEMCPY GLOBAL_MEMCPY
    #elif ONLP_PLATFORM_DEFAULTS_CONFIG_PORTING_STDLIB == 1
        #define ONLP_PLATFORM_DEFAULTS_MEMCPY memcpy
    #else
        #error The macro ONLP_PLATFORM_DEFAULTS_MEMCPY is required but cannot be defined.
    #endif
#endif

#ifndef ONLP_PLATFORM_DEFAULTS_STRNCPY
    #if defined(GLOBAL_STRNCPY)
        #define ONLP_PLATFORM_DEFAULTS_STRNCPY GLOBAL_STRNCPY
    #elif ONLP_PLATFORM_DEFAULTS_CONFIG_PORTING_STDLIB == 1
        #define ONLP_PLATFORM_DEFAULTS_STRNCPY strncpy
    #else
        #error The macro ONLP_PLATFORM_DEFAULTS_STRNCPY is required but cannot be defined.
    #endif
#endif

#ifndef ONLP_PLATFORM_DEFAULTS_STRLEN
    #if defined(GLOBAL_STRLEN)
        #define ONLP_PLATFORM_DEFAULTS_STRLEN GLOBAL_STRLEN
    #elif ONLP_PLATFORM_DEFAULTS_CONFIG_PORTING_STDLIB == 1
        #define ONLP_PLATFORM_DEFAULTS_STRLEN strlen
    #else
        #error The macro ONLP_PLATFORM_DEFAULTS_STRLEN is required but cannot be defined.
    #endif
#endif

/* <auto.end.portingmacro(ALL).define> */


#endif /* __ONLP_PLATFORM_DEFAULTS_PORTING_H__ */
/* @} */
