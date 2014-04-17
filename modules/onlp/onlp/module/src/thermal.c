/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 * Thermal Sensor Management.
 *
 ************************************************************/
#include <onlp/thermal.h>
#include <onlp/platformi/thermali.h>
#include <onlp/oids.h>

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

int
onlp_thermal_info_get(onlp_oid_t id, onlp_thermal_info_t* info)
{
    VALIDATE(id);
    return onlp_thermali_info_get(id, info);
}

void
onlp_thermal_show(onlp_oid_t id, aim_pvs_t* pvs, uint32_t flags)
{
    int rv;
    onlp_thermal_info_t info;

    VALIDATENR(id);

    rv = onlp_thermal_info_get(id, &info);
    if(rv < 0) {
        aim_printf(pvs, "Error retrieving thermal id %d: %{onlp_status}\n",
                   ONLP_OID_ID_GET(id), rv);
        return;
    }

    if(info.status & 1) {
        /* Present */
        aim_printf(pvs, "Thermal: %s\n", info.hdr.description);
        aim_printf(pvs, "  Status: %{onlp_thermal_status_flags}\n", info.status);
        aim_printf(pvs, "  Temperature: %f\n", info.temperature);
    }
    else if(flags & ONLP_OID_SHOW_F_EVEN_IF_ABSENT) {
        aim_printf(pvs, "Thermal: %s (Not present)\n", info.hdr.description);
    }
    aim_printf(pvs, "\n");
}
