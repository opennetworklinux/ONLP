/************************************************************
 *
 * Thermal Sensor Management.
 *
 ************************************************************/
#ifndef __ONLP_THERMAL_H__
#define __ONLP_THERMAL_H__

#include <onlp/oids.h>


typedef struct onlp_thermal_info_s {
    /* Thermal Identifier */
    int tid;

    /* User description of this thermal sensor -- location */
    onlp_oid_desc_t description;

    /* The sensor is present. */
    int present;

    /* Sensor status */
    uint32_t status;

    /* Current temperature. */
    uint32_t temperature;

} onlp_thermal_info_t;

int onlp_thermal_init(void);
int onlp_thermal_info_get(int tid, onlp_thermal_info_t* rv);


#endif /* __ONLP_THERMAL_H__ */
