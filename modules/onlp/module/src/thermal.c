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
#include <onlp/thermal.h>
#include <onlp/platformi/thermali.h>
#include <onlp/oids.h>
#include "onlp_int.h"

#define VALIDATE(_id)                           \
    do {                                        \
        if(!ONLP_OID_IS_THERMAL(_id)) {         \
            return ONLP_STATUS_E_INVALID;       \
        }                                       \
    } while(0)

#define VALIDATENR(_id)                         \
    do {                                        \
        if(!ONLP_OID_IS_THERMAL(_id)) {         \
            return;                             \
        }                                       \
    } while(0)


int
onlp_thermal_init(void)
{
    return onlp_thermali_init();
}

#if ONLP_CONFIG_INCLUDE_PLATFORM_OVERRIDES == 1

static int
onlp_thermali_info_from_json__(cJSON* data, onlp_thermal_info_t* info, int errorcheck)
{
    int rv;
    double t;

    if(data == NULL) {
        return (errorcheck) ? ONLP_STATUS_E_PARAM : 0;
    }

    rv = cjson_util_lookup_int(data, (int*) &info->status, "status");
    if(rv < 0 && errorcheck) return rv;

    rv = cjson_util_lookup_double(data, &t, "temperature");
    if(rv < 0 && errorcheck) return rv;
    info->temperature = t;

    return 0;
}

#endif

int
onlp_thermal_info_get(onlp_oid_t oid, onlp_thermal_info_t* info)
{
    int rv;
    VALIDATE(oid);

    rv = onlp_thermali_info_get(oid, info);
    if(rv >= 0) {

#if ONLP_CONFIG_INCLUDE_PLATFORM_OVERRIDES == 1
        int id = ONLP_OID_ID_GET(oid);
        cJSON* entry = NULL;

        cjson_util_lookup(onlp_json_get(0), &entry, "overrides.thermal.%d", id);
        onlp_thermali_info_from_json__(entry, info, 0);
#endif

    }
    return rv;
}


/************************************************************
 *
 * Debug and Show Functions
 *
 ***********************************************************/
void
onlp_thermal_dump(onlp_oid_t id, aim_pvs_t* pvs, uint32_t flags)
{
    int rv;
    iof_t iof;
    onlp_thermal_info_t info;

    VALIDATENR(id);
    onlp_oid_dump_iof_init_default(&iof, pvs);

    iof_push(&iof, "thermal @ %d", ONLP_OID_ID_GET(id));
    rv = onlp_thermal_info_get(id, &info);
    if(rv < 0) {
        onlp_oid_info_get_error(&iof, rv);
    }
    else {
        onlp_oid_show_description(&iof, &info.hdr);
        if(info.status & 1) {
            /* Present */
            iof_iprintf(&iof, "Status: %{onlp_thermal_status_flags}", info.status);
            iof_iprintf(&iof, "Temperature: %f", info.temperature);
        }
        else {
            iof_iprintf(&iof, "Not present.");
        }
    }
    iof_pop(&iof);
}

void
onlp_thermal_show(onlp_oid_t id, aim_pvs_t* pvs, uint32_t flags)
{
    int rv;
    iof_t iof;
    onlp_thermal_info_t ti;
    VALIDATENR(id);
    onlp_oid_show_iof_init_default(&iof, pvs);

    rv = onlp_thermal_info_get(id, &ti);
    iof_push(&iof, "Thermal %d", ONLP_OID_ID_GET(id));
    if(rv < 0) {
        onlp_oid_info_get_error(&iof, rv);
    }
    else {
        onlp_oid_show_description(&iof, &ti.hdr);
        if(ti.status & 0x1) {
            /* Present */
            if(ti.status & ONLP_THERMAL_STATUS_FAILED) {
                iof_iprintf(&iof, "Status: FAILED");
            }
            else {
                iof_iprintf(&iof, "Temperature: %.1f C.",
                            onlp_float_normal(ti.temperature));
            }
        }
        else {
            /* Not present */
            iof_iprintf(&iof, "State: Missing.");
        }
    }
    iof_pop(&iof);
}
