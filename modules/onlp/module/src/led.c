/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 * LED Management
 *
 ***********************************************************/
#include <onlp/onlp.h>
#include <onlp/oids.h>
#include <onlp/led.h>
#include <onlp/platformi/ledi.h>

#define VALIDATE(_id)                           \
    do {                                        \
        if(!ONLP_OID_IS_LED(_id)) {             \
            return ONLP_STATUS_E_INVALID;       \
        }                                       \
    } while(0)

#define VALIDATENR(_id)                         \
    do {                                        \
        if(!ONLP_OID_IS_LED(_id)) {             \
            return;                             \
        }                                       \
    } while(0)


static int
onlp_led_present__(onlp_oid_t id, onlp_led_info_t* info)
{
    int rv;
    VALIDATE(id);

    /* Info retrieval required. */
    rv = onlp_ledi_info_get(id, info);
    if(rv < 0) {
        return rv;
    }
    /* The led must be present. */
    if((info->status & 0x1) == 0) {
        return ONLP_STATUS_E_MISSING;
    }
    return ONLP_STATUS_OK;
}
#define ONLP_LED_PRESENT_OR_RETURN(_id, _info)          \
    do {                                                \
        int _rv = onlp_led_present__(_id, _info);       \
        if(_rv < 0) {                                   \
            return _rv;                                 \
        }                                               \
    } while(0)

int
onlp_led_init(void)
{
    return onlp_ledi_init();
}

int
onlp_led_info_get(onlp_oid_t id, onlp_led_info_t* info)
{
    VALIDATE(id);
    return onlp_ledi_info_get(id, info);
}

int
onlp_led_set(onlp_oid_t id, int on_or_off)
{
    onlp_led_info_t info;
    ONLP_LED_PRESENT_OR_RETURN(id, &info);
    if(info.caps & ONLP_LED_CAPS_ON_OFF) {
        return onlp_ledi_set(id, on_or_off);
    }
    else {
        return ONLP_STATUS_E_UNSUPPORTED;
    }
}

int
onlp_led_mode_set(onlp_oid_t id, onlp_led_mode_t mode)
{
    onlp_led_info_t info;
    ONLP_LED_PRESENT_OR_RETURN(id, &info);

    /*
     * The mode enumeration values always match
     * the capability bit positions.
     */
    if(info.caps & (1 << mode)) {
        return onlp_ledi_mode_set(id, mode);
    }
    else {
        return ONLP_STATUS_E_UNSUPPORTED;
    }
}

void
onlp_led_show(onlp_oid_t id, aim_pvs_t* pvs, uint32_t flags)
{
    int rv;
    onlp_led_info_t info;

    VALIDATENR(id);

    rv = onlp_led_info_get(id, &info);
    if(rv < 0) {
        aim_printf(pvs, "Error retrieving LED id %d: %{onlp_status}\n",
                   ONLP_OID_ID_GET(id), rv);
        return;
    }

    if(info.status & 1) {
        /* Present */
        aim_printf(pvs, "LED: %s\n", info.hdr.description);
        aim_printf(pvs, "  Status: 0x%x\n", info.status);
        aim_printf(pvs, "  Mode: %{onlp_led_mode}\n", info.mode);
    }
    else if(flags & ONLP_OID_SHOW_F_EVEN_IF_ABSENT) {
        aim_printf(pvs, "LED: %s (Not present)\n", info.hdr.description);
    }
    aim_printf(pvs, "\n");
}

