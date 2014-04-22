/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 * Power Supply Management.
 *
 ***********************************************************/

#include <onlp/onlp.h>
#include <onlp/oids.h>
#include <onlp/psu.h>
#include <onlp/platformi/psui.h>

#define VALIDATE(_id)                           \
    do {                                        \
        if(!ONLP_OID_IS_PSU(_id)) {             \
            return ONLP_STATUS_E_INVALID;       \
        }                                       \
    } while(0)

#define VALIDATENR(_id)                         \
    do {                                        \
        if(!ONLP_OID_IS_PSU(_id)) {             \
            return;                             \
        }                                       \
    } while(0)


static int
onlp_psu_present__(onlp_oid_t id, onlp_psu_info_t* info)
{
    int rv;
    VALIDATE(id);

    /* Info retrieval required. */
    rv = onlp_psui_info_get(id, info);
    if(rv < 0) {
        return rv;
    }
    /* The psu must be present. */
    if((info->status & 0x1) == 0) {
        return ONLP_STATUS_E_MISSING;
    }
    return ONLP_STATUS_OK;
}
#define ONLP_PSU_PRESENT_OR_RETURN(_id, _info)          \
    do {                                                \
        int _rv = onlp_psu_present__(_id, _info);       \
        if(_rv < 0) {                                   \
            return _rv;                                 \
        }                                               \
    } while(0)


int
onlp_psu_init(void)
{
    return onlp_psui_init();
}

int
onlp_psu_info_get(onlp_oid_t id,  onlp_psu_info_t* info)
{
    VALIDATE(id);
    return onlp_psui_info_get(id, info);
}

int
onlp_psu_ioctl(onlp_oid_t id, ...)
{
    int rv;
    onlp_psu_info_t info;
    va_list vargs;

    ONLP_PSU_PRESENT_OR_RETURN(id, &info);
    va_start(vargs, id);
    rv = onlp_psui_ioctl(id, vargs);
    va_end(vargs);
    return rv;
}

void
onlp_psu_show(onlp_oid_t id, aim_pvs_t* pvs, uint32_t flags)
{
    int rv;
    onlp_psu_info_t info;

    VALIDATENR(id);

    rv = onlp_psu_info_get(id, &info);
    if(rv < 0) {
        aim_printf(pvs, "Error retrieving psu id %d: %{onlp_status}\n",
                   ONLP_OID_ID_GET(id), rv);
        return;
    }

    if(info.status & 1) {
        /* Present */
        aim_printf(pvs, "PSU: %s\n", info.hdr.description);
        aim_printf(pvs, "  Model: %s\n", info.model[0] ? info.model[0] : "Unknown.");
        aim_printf(pvs, "  Status: %{onlp_psu_status_flags}\n", info.status);
        aim_printf(pvs, "  Caps:   %{onlp_psu_caps_flags}\n", info.caps);
        aim_printf(pvs, "  Vin:  %f\n", info.vin);
        aim_printf(pvs, "  Vout: %f\n", info.vout);
        aim_printf(pvs, "  Iin:  %f\n", info.iin);
        aim_printf(pvs, "  Iout: %f\n", info.iout);
        aim_printf(pvs, "  Pin:  %f\n", info.pin);
        aim_printf(pvs, "  Pout: %f\n", info.pout);

        if(flags & ONLP_OID_SHOW_F_RECURSE) {
            onlp_oids_show(info.oid_table, AIM_ARRAYSIZE(info.oid_table), pvs, flags);
        }
    }
    else if(flags & ONLP_OID_SHOW_F_EVEN_IF_ABSENT) {
        aim_printf(pvs, "PSU: %s (Not present)\n", info.hdr.description);
    }
    aim_printf(pvs, "\n");
}

