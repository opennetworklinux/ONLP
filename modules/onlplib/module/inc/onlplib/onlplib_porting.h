/**************************************************************************//**
 *
 * @file
 * @brief onlplib Porting Macros.
 *
 * @addtogroup onlplib-porting
 * @{
 *
 *****************************************************************************/
#ifndef __ONLPLIB_PORTING_H__
#define __ONLPLIB_PORTING_H__


/* <auto.start.portingmacro(ALL).define> */
#if ONLPLIB_CONFIG_PORTING_INCLUDE_STDLIB_HEADERS == 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <memory.h>
#endif

#ifndef ONLPLIB_MALLOC
    #if defined(GLOBAL_MALLOC)
        #define ONLPLIB_MALLOC GLOBAL_MALLOC
    #elif ONLPLIB_CONFIG_PORTING_STDLIB == 1
        #define ONLPLIB_MALLOC malloc
    #else
        #error The macro ONLPLIB_MALLOC is required but cannot be defined.
    #endif
#endif

#ifndef ONLPLIB_FREE
    #if defined(GLOBAL_FREE)
        #define ONLPLIB_FREE GLOBAL_FREE
    #elif ONLPLIB_CONFIG_PORTING_STDLIB == 1
        #define ONLPLIB_FREE free
    #else
        #error The macro ONLPLIB_FREE is required but cannot be defined.
    #endif
#endif

#ifndef ONLPLIB_MEMSET
    #if defined(GLOBAL_MEMSET)
        #define ONLPLIB_MEMSET GLOBAL_MEMSET
    #elif ONLPLIB_CONFIG_PORTING_STDLIB == 1
        #define ONLPLIB_MEMSET memset
    #else
        #error The macro ONLPLIB_MEMSET is required but cannot be defined.
    #endif
#endif

#ifndef ONLPLIB_MEMCPY
    #if defined(GLOBAL_MEMCPY)
        #define ONLPLIB_MEMCPY GLOBAL_MEMCPY
    #elif ONLPLIB_CONFIG_PORTING_STDLIB == 1
        #define ONLPLIB_MEMCPY memcpy
    #else
        #error The macro ONLPLIB_MEMCPY is required but cannot be defined.
    #endif
#endif

#ifndef ONLPLIB_STRNCPY
    #if defined(GLOBAL_STRNCPY)
        #define ONLPLIB_STRNCPY GLOBAL_STRNCPY
    #elif ONLPLIB_CONFIG_PORTING_STDLIB == 1
        #define ONLPLIB_STRNCPY strncpy
    #else
        #error The macro ONLPLIB_STRNCPY is required but cannot be defined.
    #endif
#endif

#ifndef ONLPLIB_VSNPRINTF
    #if defined(GLOBAL_VSNPRINTF)
        #define ONLPLIB_VSNPRINTF GLOBAL_VSNPRINTF
    #elif ONLPLIB_CONFIG_PORTING_STDLIB == 1
        #define ONLPLIB_VSNPRINTF vsnprintf
    #else
        #error The macro ONLPLIB_VSNPRINTF is required but cannot be defined.
    #endif
#endif

#ifndef ONLPLIB_SNPRINTF
    #if defined(GLOBAL_SNPRINTF)
        #define ONLPLIB_SNPRINTF GLOBAL_SNPRINTF
    #elif ONLPLIB_CONFIG_PORTING_STDLIB == 1
        #define ONLPLIB_SNPRINTF snprintf
    #else
        #error The macro ONLPLIB_SNPRINTF is required but cannot be defined.
    #endif
#endif

#ifndef ONLPLIB_STRLEN
    #if defined(GLOBAL_STRLEN)
        #define ONLPLIB_STRLEN GLOBAL_STRLEN
    #elif ONLPLIB_CONFIG_PORTING_STDLIB == 1
        #define ONLPLIB_STRLEN strlen
    #else
        #error The macro ONLPLIB_STRLEN is required but cannot be defined.
    #endif
#endif

/* <auto.end.portingmacro(ALL).define> */


#endif /* __ONLPLIB_PORTING_H__ */
/* @} */
