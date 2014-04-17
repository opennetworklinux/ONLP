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
static onlp_psu_info_t pinfo[] =
    {
        { }, /* Not used */
        {
            { ONLP_PSU_ID_CREATE(1), "PSU-1", 0 },
            0x1,
            ONLP_PSU_CAPS_AC | ONLP_PSU_CAPS_VIN | ONLP_PSU_CAPS_VOUT | ONLP_PSU_CAPS_IIN,
            240.0,
            12.0,
            2.0,
            3.0,
            0,
            0,
            /* This PSU has 2 fans */
            { ONLP_FAN_ID_CREATE(3), ONLP_FAN_ID_CREATE(4) },
        },
        {
            { ONLP_PSU_ID_CREATE(2), "PSU-2", 0 },
            0,
        },
        {
            { ONLP_PSU_ID_CREATE(3), "PSU-3", 0 },
            0x1,
            ONLP_PSU_CAPS_DC48,
            48,
            12,
            2.0
        },
    };


int
onlp_psui_info_get(onlp_oid_t id, onlp_psu_info_t* info)
{
    *info = pinfo[ONLP_OID_ID_GET(id)];
    return ONLP_STATUS_OK;
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
