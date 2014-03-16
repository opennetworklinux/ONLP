/************************************************************
 *
 * LEDs
 *
 ***********************************************************/
#ifndef __ONLP_LED_H__
#define __ONLP_LED_H__

#include <onlp/oids.h>

typedef struct onlp_led_info_s {

    onlp_oid_t lid;

    onlp_oid_desc_t description;

    uint32_t capabilities;

    uint32_t status;

} onlp_led_info_t;

int onlp_led_init(void);

int onlp_led_info_get(onlp_oid_t lid, onlp_led_info_t* rv);

int onlp_led_set(onlp_oid_t lid, int on_or_off, int mode);


#endif /* __ONLP_LED_H__ */
