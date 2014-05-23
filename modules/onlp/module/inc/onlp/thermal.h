/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * 
 *           Copyright 2014 Big Switch Networks, Inc.          
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
 * @brief Thermal OID debug dump.
 * @param id The thermal id.
 * @param pvs The output pvs.
 * @param flags The dump flags.
 */
void onlp_thermal_dump(onlp_oid_t id, aim_pvs_t* pvs, uint32_t flags);

/**
 * @brief Show the given thermal OID.
 * @param id The Thermal OID
 * @param pvs The output pvs
 * @param flags The output flags
 */
void onlp_thermal_show(onlp_oid_t id, aim_pvs_t* pvs, uint32_t flags);

#endif /* __ONLP_THERMAL_H__ */
