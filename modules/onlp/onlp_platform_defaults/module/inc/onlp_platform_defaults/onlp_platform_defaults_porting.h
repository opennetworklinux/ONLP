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

#ifndef ONLP_PLATFORM_DEFAULTS_MALLOC
    #if defined(GLOBAL_MALLOC)
        #define ONLP_PLATFORM_DEFAULTS_MALLOC GLOBAL_MALLOC
    #elif ONLP_PLATFORM_DEFAULTS_CONFIG_PORTING_STDLIB == 1
        #define ONLP_PLATFORM_DEFAULTS_MALLOC malloc
    #else
        #error The macro ONLP_PLATFORM_DEFAULTS_MALLOC is required but cannot be defined.
    #endif
#endif

#ifndef ONLP_PLATFORM_DEFAULTS_FREE
    #if defined(GLOBAL_FREE)
        #define ONLP_PLATFORM_DEFAULTS_FREE GLOBAL_FREE
    #elif ONLP_PLATFORM_DEFAULTS_CONFIG_PORTING_STDLIB == 1
        #define ONLP_PLATFORM_DEFAULTS_FREE free
    #else
        #error The macro ONLP_PLATFORM_DEFAULTS_FREE is required but cannot be defined.
    #endif
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

#ifndef ONLP_PLATFORM_DEFAULTS_VSNPRINTF
    #if defined(GLOBAL_VSNPRINTF)
        #define ONLP_PLATFORM_DEFAULTS_VSNPRINTF GLOBAL_VSNPRINTF
    #elif ONLP_PLATFORM_DEFAULTS_CONFIG_PORTING_STDLIB == 1
        #define ONLP_PLATFORM_DEFAULTS_VSNPRINTF vsnprintf
    #else
        #error The macro ONLP_PLATFORM_DEFAULTS_VSNPRINTF is required but cannot be defined.
    #endif
#endif

#ifndef ONLP_PLATFORM_DEFAULTS_SNPRINTF
    #if defined(GLOBAL_SNPRINTF)
        #define ONLP_PLATFORM_DEFAULTS_SNPRINTF GLOBAL_SNPRINTF
    #elif ONLP_PLATFORM_DEFAULTS_CONFIG_PORTING_STDLIB == 1
        #define ONLP_PLATFORM_DEFAULTS_SNPRINTF snprintf
    #else
        #error The macro ONLP_PLATFORM_DEFAULTS_SNPRINTF is required but cannot be defined.
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
