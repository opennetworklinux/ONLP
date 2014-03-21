/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 * Fan Management.
 *
 ***********************************************************/
#include <onlp/fan.h>
#include <onlp/platformi/fani.h>
#include <onlp/oids.h>

#define VALIDATE(_id)                           \
    do {                                        \
        if(!ONLP_OID_IS_FAN(_id)) {             \
            return ONLP_STATUS_E_INVALID;       \
        }                                       \
    } while(0)

#define VALIDATENR(_id)                         \
    do {                                        \
        if(!ONLP_OID_IS_FAN(_id)) {             \
            return;                             \
        }                                       \
    } while(0)


int
onlp_fan_init(void)
{
    return onlp_fani_init();
}

int
onlp_fan_info_get(onlp_oid_t id, onlp_fan_info_t* rv)
{
    VALIDATE(id);
    return onlp_fani_info_get(id, rv);
}

static int
onlp_fan_present__(onlp_oid_t id, onlp_fan_info_t* info)
{
    int rv;
    VALIDATE(id);

    /* Info retrieval required. */
    rv = onlp_fani_info_get(id, info);
    if(rv < 0) {
        return rv;
    }
    /* The fan must be present. */
    if((info->status & 0x1) == 0) {
        return ONLP_STATUS_E_MISSING;
    }
    return ONLP_STATUS_OK;
}
#define ONLP_FAN_PRESENT_OR_RETURN(_id, _info)          \
    do {                                                \
        int _rv = onlp_fan_present__(_id, _info);       \
        if(_rv < 0) {                                   \
            return _rv;                                 \
        }                                               \
    } while(0)

int
onlp_fan_rpm_set(onlp_oid_t id, int rpm)
{
    onlp_fan_info_t info;
    ONLP_FAN_PRESENT_OR_RETURN(id, &info);
    if(info.caps & ONLP_FAN_CAPS_SET_RPM) {
        return onlp_fani_rpm_set(id, rpm);
    }
    else {
        return ONLP_STATUS_E_UNSUPPORTED;
    }
}

int
onlp_fan_percentage_set(onlp_oid_t id, int p)
{
    onlp_fan_info_t info;
    ONLP_FAN_PRESENT_OR_RETURN(id, &info);
    if(info.caps & ONLP_FAN_CAPS_SET_PERCENTAGE) {
        return onlp_fani_rpm_set(id, p);
    }
    else {
        return ONLP_STATUS_E_UNSUPPORTED;
    }
}

int
onlp_fan_mode_set(onlp_oid_t id, onlp_fan_mode_t mode)
{
    onlp_fan_info_t info;
    ONLP_FAN_PRESENT_OR_RETURN(id, &info);
    return onlp_fani_mode_set(id, mode);
}

int
onlp_fan_dir_set(onlp_oid_t id, onlp_fan_dir_t dir)
{
    onlp_fan_info_t info;
    ONLP_FAN_PRESENT_OR_RETURN(id, &info);
    if( (info.caps & ONLP_FAN_CAPS_B2F) &&
        (info.caps & ONLP_FAN_CAPS_F2B) ) {
        return onlp_fani_dir_set(id, dir);
    }
    else {
        return ONLP_STATUS_E_UNSUPPORTED;
    }
}

void
onlp_fan_show(onlp_oid_t id, aim_pvs_t* pvs, uint32_t flags)
{
    int rv;
    onlp_fan_info_t info;

    VALIDATENR(id);

    rv = onlp_fan_info_get(id, &info);
    if(rv < 0) {
        aim_printf(pvs, "Error retrieving fan id %d: %{onlp_status}\n",
                   ONLP_OID_ID_GET(id), rv);
        return;
    }

    if(info.status & 1) {
        /* Present */
        aim_printf(pvs, "Fan: %s\n", info.hdr.description);
        aim_printf(pvs, "  Status: 0x%x\n", info.status);
        aim_printf(pvs, "  Caps:   0x%x\n", info.caps);
    }
    else if(flags & ONLP_OID_SHOW_F_EVEN_IF_ABSENT) {
        aim_printf(pvs, "Fan: %s (Not present)\n", info.hdr.description);
    }
    aim_printf(pvs, "\n");
}





