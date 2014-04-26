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
oid_type_SYS_coids_get__(onlp_oid_t oid, onlp_oid_table_t coids)
{
    return 0;
}

static int
oid_type_THERMAL_coids_get__(onlp_oid_t oid, onlp_oid_table_t coids)
{
    return 0;
}

static int
oid_type_FAN_coids_get__(onlp_oid_t oid, onlp_oid_table_t coids)
{
    return 0;
}

static int
oid_type_LED_coids_get__(onlp_oid_t oid, onlp_oid_table_t coids)
{
    return 0;
}

static int
oid_type_PSU_coids_get__(onlp_oid_t oid, onlp_oid_table_t coids)
{
    return 0;
}

static int
oid_type_RTC_coids_get__(onlp_oid_t oid, onlp_oid_table_t coids)
{
    return 0;
}


static int
oid_type_MODULE_coids_get__(onlp_oid_t oid, onlp_oid_table_t coids)
{
    return 0;
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
onlp_oid_iterate(onlp_oid_t oid, onlp_oid_type_t type,
                 onlp_oid_iterate_f itf, void* cookie)
{
    int valid = 0;
    onlp_oid_table_t coids = { 0 };

    if(oid == 0) {
        oid = ONLP_OID_SYS;
    }

    switch(ONLP_OID_TYPE_GET(oid)) {
#define ONLP_OID_TYPE_ENTRY(_name, _value)                              \
        case ONLP_OID_TYPE_##_name:                                     \
            {                                                           \
                int rv = oid_type_##_name##_coids_get__(oid, coids);    \
                if(rv < 0) {                                            \
                    return rv;                                          \
                }                                                       \
                valid = 1;                                              \
                break;                                                  \
            }

#include <onlp/onlp.x>

            /* Intentional compile time error if an OID handler is missing. */
        }

    if(valid) {
        onlp_oid_t* oidp;
        ONLP_OID_TABLE_ITER(coids, oidp) {
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
    else {
        /* The given OID was invalid. */
        return ONLP_STATUS_E_INVALID;
    }

}
