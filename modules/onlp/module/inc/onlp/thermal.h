/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 * Thermal Sensor Management.
 *
 ************************************************************/
#ifndef __ONLP_THERMAL_H__
#define __ONLP_THERMAL_H__

#include <onlp/onlp.h>
#include <onlp/oids.h>

/* <auto.start.enum(onlp_thermal_status).define> */
/** onlp_thermal_status */
typedef enum onlp_thermal_status_e {
    ONLP_THERMAL_STATUS_PRESENT = (1 << 0),
    ONLP_THERMAL_STATUS_FAILED = (1 << 1),
} onlp_thermal_status_t;
/* <auto.end.enum(onlp_thermal_status).define> */


/**
 * Thermal sensor information structure.
 */
typedef struct onlp_thermal_info_s {

    /** OID Header */
    onlp_oid_hdr_t hdr;

    /** Status */
    uint32_t status;

    /* Current temperature. */
    float temperature;

} onlp_thermal_info_t;

/**
 * @brief Initialize the thermal subsystem.
 */
int onlp_thermal_init(void);

/**
 * @brief Retrieve information about the given thermal id.
 * @param id The thermal oid.
 * @param rv [out] Receives the thermal information.
 */
int onlp_thermal_info_get(onlp_oid_t id, onlp_thermal_info_t* rv);

/**
 * @brief Show the current information about the given thermal id.
 * @param id The thermal id.
 * @param pvs The output pvs.
 */
void onlp_thermal_show(onlp_oid_t tid, aim_pvs_t* pvs);

#endif /* __ONLP_THERMAL_H__ */
