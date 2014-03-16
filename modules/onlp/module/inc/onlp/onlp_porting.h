/**************************************************************************//**
 *
 * @file
 * @brief onlp Porting Macros.
 *
 * @addtogroup onlp-porting
 * @{
 *
 *****************************************************************************/
#ifndef __ONLP_PORTING_H__
#define __ONLP_PORTING_H__


/* <auto.start.portingmacro(ALL).define> */
#if ONLP_CONFIG_PORTING_INCLUDE_STDLIB_HEADERS == 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <memory.h>
#endif

#ifndef ONLP_MEMSET
    #if defined(GLOBAL_MEMSET)
        #define ONLP_MEMSET GLOBAL_MEMSET
    #elif ONLP_CONFIG_PORTING_STDLIB == 1
        #define ONLP_MEMSET memset
    #else
        #error The macro ONLP_MEMSET is required but cannot be defined.
    #endif
#endif

#ifndef ONLP_MEMCPY
    #if defined(GLOBAL_MEMCPY)
        #define ONLP_MEMCPY GLOBAL_MEMCPY
    #elif ONLP_CONFIG_PORTING_STDLIB == 1
        #define ONLP_MEMCPY memcpy
    #else
        #error The macro ONLP_MEMCPY is required but cannot be defined.
    #endif
#endif

#ifndef ONLP_STRNCPY
    #if defined(GLOBAL_STRNCPY)
        #define ONLP_STRNCPY GLOBAL_STRNCPY
    #elif ONLP_CONFIG_PORTING_STDLIB == 1
        #define ONLP_STRNCPY strncpy
    #else
        #error The macro ONLP_STRNCPY is required but cannot be defined.
    #endif
#endif

#ifndef ONLP_STRLEN
    #if defined(GLOBAL_STRLEN)
        #define ONLP_STRLEN GLOBAL_STRLEN
    #elif ONLP_CONFIG_PORTING_STDLIB == 1
        #define ONLP_STRLEN strlen
    #else
        #error The macro ONLP_STRLEN is required but cannot be defined.
    #endif
#endif

/* <auto.end.portingmacro(ALL).define> */


#endif /* __ONLP_PORTING_H__ */
/* @} */
