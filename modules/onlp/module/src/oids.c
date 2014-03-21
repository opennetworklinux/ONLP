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

static int
oid_type_THERMAL_show__(onlp_oid_t oid, aim_pvs_t* pvs)
{
    AIM_LOG_MSG("thermal_show: 0x%x", oid);
    return 0;
}

static int
oid_type_FAN_show__(onlp_oid_t oid, aim_pvs_t* pvs)
{
    return 0;
}

static int
oid_type_PSU_show__(onlp_oid_t oid, aim_pvs_t* pvs)
{
    return 0;
}
static int
oid_type_LED_show__(onlp_oid_t oid, aim_pvs_t* pvs)
{
    return 0;
}

static int
oid_type_MODULE_show__(onlp_oid_t oid, aim_pvs_t* pvs)
{
    return 0;
}


void
onlp_oid_show(onlp_oid_t oid, aim_pvs_t* pvs)
{
    int otype = ONLP_OID_TYPE_GET(oid);

    switch(ONLP_OID_TYPE_GET(oid)) {
#define ONLP_OID_TYPE_ENTRY(_name, _value)               \
        case ONLP_OID_TYPE_##_name:                 \
            oid_type_##_name##_show__(oid, pvs); \
            return;
#include <onlp/onlp.x>

        /* Intentional compile time error if an OID decode is missing. */
    }


    AIM_LOG_WARN("OID TYPE %d is unknown.", otype);
    aim_printf(pvs, "OID 0x%x type=%d (unrecognized)\n", oid, otype);
}



