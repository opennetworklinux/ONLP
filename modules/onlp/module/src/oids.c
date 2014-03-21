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


void
onlp_oid_show(onlp_oid_t oid, aim_pvs_t* pvs, uint32_t flags)
{
    int otype = ONLP_OID_TYPE_GET(oid);

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

