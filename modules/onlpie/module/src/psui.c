/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 *
 *
 ***********************************************************/
#include <onlp/platformi/psui.h>
#include "onlpie_int.h"

/*
 * This function will be called prior to any other onlp_psui functions.
 */
int
onlp_psui_init(void)
{
    return ONLP_STATUS_OK;
}

/*
 * Get all information about the given PSU oid.
 */
int
onlp_psui_info_get_f(onlp_oid_t id, onlp_psu_info_t* rv)
{
    /* Do somethign here */
    return ONLP_STATUS_E_INTERNAL;
}

/*
 * This is an optional generic ioctl() interface.
 * Its purpose is to allow future expansion and
 * custom functionality that is not otherwise exposed
 * in the standard interface.
 *
 * The semantics of this function are platform specific.
 * This function is completely optional.
 */
int
onlp_psui_ioctl(onlp_oid_t pid, va_list vargs)
{
    return ONLP_STATUS_E_UNSUPPORTED;
}
