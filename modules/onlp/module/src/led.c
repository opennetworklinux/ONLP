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
#include "onlp_int.h"

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


/************************************************************
 *
 * Debug and Show Functions
 *
 ***********************************************************/

void
onlp_led_dump(onlp_oid_t id, aim_pvs_t* pvs, uint32_t flags)
{
    int rv;
    iof_t iof;
    onlp_led_info_t info;

    VALIDATENR(id);
    onlp_oid_dump_iof_init_default(&iof, pvs);
    iof_push(&iof, "led @ %d", ONLP_OID_ID_GET(id));
    rv = onlp_led_info_get(id, &info);
    if(rv < 0) {
        onlp_oid_info_get_error(&iof, rv);
    }
    else {
        onlp_oid_show_description(&iof, &info.hdr);
        if(info.status & 1) {
            /* Present */
            iof_iprintf(&iof, "Status: %{onlp_led_status_flags}", info.status);
            iof_iprintf(&iof, "Mode: %{onlp_led_mode}", info.mode);
        }
        else {
            iof_iprintf(&iof, "Not present.");
        }
    }
    iof_pop(&iof);
}

void
onlp_led_show(onlp_oid_t id, aim_pvs_t* pvs, uint32_t flags)
{
    int rv;
    iof_t iof;
    onlp_led_info_t info;

    VALIDATENR(id);
    onlp_oid_show_iof_init_default(&iof, pvs);
    iof_push(&iof, "LED %d", ONLP_OID_ID_GET(id));
    rv = onlp_led_info_get(id, &info);
    if(rv < 0) {
        onlp_oid_info_get_error(&iof, rv);
    }
    else {
        onlp_oid_show_description(&iof, &info.hdr);
        if(info.status & 1) {
            /* Present */
            iof_iprintf(&iof, "Mode: %{onlp_led_mode}", info.mode);
        }
        else {
            onlp_oid_show_state_missing(&iof);
        }
    }
    iof_pop(&iof);

}

