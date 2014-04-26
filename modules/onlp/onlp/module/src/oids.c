/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 *
 *
 ***********************************************************/
#include <onlp/onlp_config.h>
#include <onlp/oids.h>
#include "onlp_log.h"
#include <AIM/aim.h>
#include <AIM/aim_printf.h>

#include <onlp/thermal.h>
#include <onlp/fan.h>
#include <onlp/led.h>
#include <onlp/psu.h>
#include <onlp/sys.h>

static void
oid_type_SYS_show__(onlp_oid_t oid, aim_pvs_t* pvs,
                    uint32_t flags)
{
    onlp_sys_show(oid, pvs, flags);
}

static void
oid_type_RTC_show__(onlp_oid_t oid, aim_pvs_t* pvs,
                    uint32_t flags)
{
    /* Not implemented yet. */
    AIM_LOG_MSG("RTC_show: 0x%x", oid);
}

static void
oid_type_THERMAL_show__(onlp_oid_t oid, aim_pvs_t* pvs,
                        uint32_t flags)
{
    onlp_thermal_show(oid, pvs, flags);
}

static void
oid_type_FAN_show__(onlp_oid_t oid, aim_pvs_t* pvs,
                    uint32_t flags)

{
    onlp_fan_show(oid, pvs, flags);
}

static void
oid_type_PSU_show__(onlp_oid_t oid, aim_pvs_t* pvs,
                    uint32_t flags)
{
    onlp_psu_show(oid, pvs, flags);
}
static void
oid_type_LED_show__(onlp_oid_t oid, aim_pvs_t* pvs,
                    uint32_t flags)
{
    onlp_led_show(oid, pvs, flags);
}

static void
oid_type_MODULE_show__(onlp_oid_t oid, aim_pvs_t* pvs,
                       uint32_t flags)

{
    AIM_LOG_MSG("MODULE_show: 0x%x", oid);
}

static int
oid_type_SYS_hdr_get__(onlp_oid_t oid, onlp_oid_hdr_t* hdr)
{
    int rv;
    onlp_sys_info_t si;
    rv = onlp_sys_info_get(&si);
    memcpy(hdr, &si.hdr, sizeof(si.hdr));
    return rv;
}

static int
oid_type_THERMAL_hdr_get__(onlp_oid_t oid, onlp_oid_hdr_t* hdr)
{
    int rv;
    onlp_thermal_info_t ti;
    rv = onlp_thermal_info_get(oid, &ti);
    memcpy(hdr, &ti.hdr, sizeof(ti.hdr));
    return rv;
}

static int
oid_type_FAN_hdr_get__(onlp_oid_t oid, onlp_oid_hdr_t* hdr)
{
    int rv;
    onlp_fan_info_t fi;
    rv = onlp_fan_info_get(oid, &fi);
    memcpy(hdr, &fi.hdr, sizeof(fi.hdr));
    return rv;
}

static int
oid_type_LED_hdr_get__(onlp_oid_t oid, onlp_oid_hdr_t* hdr)
{
    int rv;
    onlp_led_info_t li;
    rv = onlp_led_info_get(oid, &li);
    memcpy(hdr, &li.hdr, sizeof(li.hdr));
    return rv;
}

static int
oid_type_PSU_hdr_get__(onlp_oid_t oid, onlp_oid_hdr_t* hdr)
{
    int rv;
    onlp_psu_info_t pi;
    rv = onlp_psu_info_get(oid, &pi);
    memcpy(hdr, &pi.hdr, sizeof(pi.hdr));
    return rv;
}

static int
oid_type_RTC_hdr_get__(onlp_oid_t oid, onlp_oid_hdr_t* hdr)
{
    /* Not implemented yet */
    AIM_LOG_MSG("RTC_coids_get: 0x%x", oid);
    return ONLP_STATUS_E_INVALID;
}


static int
oid_type_MODULE_hdr_get__(onlp_oid_t oid, onlp_oid_hdr_t* hdr)
{
    /* Not implemented yet */
    AIM_LOG_MSG("MODULE_coids_get: 0x%x", oid);
    return ONLP_STATUS_E_INVALID;
}


void
onlp_oid_show(onlp_oid_t oid, aim_pvs_t* pvs, uint32_t flags)
{
    int otype;

    if(oid == 0) {
        oid = ONLP_OID_SYS;
    }

    otype = ONLP_OID_TYPE_GET(oid);

    switch(ONLP_OID_TYPE_GET(oid)) {
#define ONLP_OID_TYPE_ENTRY(_name, _value)                              \
        case ONLP_OID_TYPE_##_name:                                     \
            oid_type_##_name##_show__(oid, pvs, flags);                 \
            return;
#include <onlp/onlp.x>

        /* Intentional compile time error if an OID decode is missing. */
    }


    AIM_LOG_WARN("OID TYPE %d is unknown.", otype);
    aim_printf(pvs, "OID 0x%x type=%d (unrecognized)\n", oid, otype);
}

void
onlp_oids_show(onlp_oid_t* oids, int count, aim_pvs_t* pvs,
               uint32_t flags)
{
    int i;
    for(i = 0; i < count; i++) {
        if(oids[i]) {
            onlp_oid_show(oids[i], pvs, flags);
        }
    }
}


int
onlp_oid_hdr_get(onlp_oid_t oid, onlp_oid_hdr_t* hdr)
{
    switch(ONLP_OID_TYPE_GET(oid))
        {
#define ONLP_OID_TYPE_ENTRY(_name, _value)                              \
            case ONLP_OID_TYPE_##_name:                                 \
                return oid_type_##_name##_hdr_get__(oid, hdr);
#include <onlp/onlp.x>
            /* Intentional compile time error if an OID handler is missing. */
        }
    return ONLP_STATUS_E_INVALID;
}

int
onlp_oid_iterate(onlp_oid_t oid, onlp_oid_type_t type,
                 onlp_oid_iterate_f itf, void* cookie)
{
    int rv;
    onlp_oid_hdr_t hdr;
    onlp_oid_t* oidp;

    if(oid == 0) {
        oid = ONLP_OID_SYS;
    }

    rv = onlp_oid_hdr_get(oid, &hdr);
    if(rv < 0) {
        return rv;
    }

    ONLP_OID_TABLE_ITER(hdr.coids, oidp) {
        if(type == 0 || ONLP_OID_IS_TYPE(*oidp, type)) {
            int rv = itf(*oidp, cookie);
            if(rv < 0) {
                return rv;
            }
            rv = onlp_oid_iterate(*oidp, type, itf, cookie);
            if(rv < 0) {
                return rv;
            }
        }
    }
    return ONLP_STATUS_OK;
}
