/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 * Thermal Sensor Platform Implementation.
 *
 ***********************************************************/
#include <onlp/platformi/thermali.h>
#include "onlpie_log.h"

/*
 * This will be called to intiialize the thermali subsystem.
 */
int
onlp_thermali_init(void)
{
    AIM_LOG_MSG("%s", __func__);
    return ONLP_STATUS_OK;
}


/*
 * Retrieve the information structure for the given thermal OID.
 *
 * If the OID is invalid, return ONLP_E_STATUS_INVALID.
 * If an unexpected error occurs, return ONLP_E_STATUS_INTERNAL.
 * Otherwise, return ONLP_STATUS_OK with the OID's information.
 *
 * Note -- it is expected that you fill out the information
 * structure even if the sensor described by the OID is not present.
 */
int
onlp_thermali_info_get(onlp_oid_t id, onlp_thermal_info_t* rv)
{
    /* Static values */
    onlp_thermal_info_t info[] = {
        { }, /* Not used */
        { { ONLP_THERMAL_ID_CREATE(1), "Chassis Thermal Sensor 1", 0}, 0x1, 23.0 },
        { { ONLP_THERMAL_ID_CREATE(2), "Chassis Thermal Sensor 2", 0}, 0x0, 0 }
    };
    *rv = info[ONLP_OID_ID_GET(id)];

    return ONLP_STATUS_OK;
}
