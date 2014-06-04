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
 * Power Supply Management.
 *
 ***********************************************************/
#ifndef __ONLP_PSU_H__
#define __ONLP_PSU_H__

#include <onlp/onlp.h>
#include <onlp/oids.h>

/* <auto.start.enum(onlp_psu_status).define> */
/** onlp_psu_status */
typedef enum onlp_psu_status_e {
    ONLP_PSU_STATUS_PRESENT = (1 << 0),
    ONLP_PSU_STATUS_FAILED = (1 << 1),
    ONLP_PSU_STATUS_UNPLUGGED = (1 << 2),
} onlp_psu_status_t;
/* <auto.end.enum(onlp_psu_status).define> */

/* <auto.start.enum(onlp_psu_caps).define> */
/** onlp_psu_caps */
typedef enum onlp_psu_caps_e {
    ONLP_PSU_CAPS_AC = (1 << 0),
    ONLP_PSU_CAPS_DC12 = (1 << 1),
    ONLP_PSU_CAPS_DC48 = (1 << 2),
    ONLP_PSU_CAPS_VIN = (1 << 3),
    ONLP_PSU_CAPS_VOUT = (1 << 4),
    ONLP_PSU_CAPS_IIN = (1 << 5),
    ONLP_PSU_CAPS_IOUT = (1 << 6),
    ONLP_PSU_CAPS_PIN = (1 << 7),
    ONLP_PSU_CAPS_POUT = (1 << 8),
} onlp_psu_caps_t;
/* <auto.end.enum(onlp_psu_caps).define> */

/**
 * PSU Information Structure
 */
typedef struct onlp_psu_info_t {
    /** OID Header */
    onlp_oid_hdr_t hdr;

    /* Model */
#define ONLP_PSU_MODEL_NAME_MAX 64
    char model[ONLP_PSU_MODEL_NAME_MAX];

    /* Status */
    uint32_t status;

    /* Capabilities */
    uint32_t caps;

    /* Float values are deprecated */
    float vin;
    float vout;
    float iin;
    float iout;
    float pin;
    float pout;

    /* millivolts */
    int mvin;
    int mvout;

    /* milliamps */
    int miin;
    int miout;

    /* milliwatts */
    int mpin;
    int mpout;

} onlp_psu_info_t;

/**
 * @brief Initialize the PSU subsystem.
 */
int onlp_psu_init(void);

/**
 * @brief Get the PSU information.
 * @param id The PSU OID.
 * @param rv [out] Receives the information structure.
 */
int onlp_psu_info_get(onlp_oid_t id, onlp_psu_info_t* rv);

/**
 * @brief PSU OID debug dump
 * @param id The PSU OID
 * @param pvs The output pvs
 * @param flags The output flags
 */
void onlp_psu_dump(onlp_oid_t id, aim_pvs_t* pvs, uint32_t flags);


/**
 * @brief Show the given PSU OID.
 * @param id The PSU OID
 * @param pvs The output pvs
 * @param flags The output flags
 */
void onlp_psu_show(onlp_oid_t id, aim_pvs_t* pvs, uint32_t flags);


#endif /* __ONLP_PSU_H__ */
