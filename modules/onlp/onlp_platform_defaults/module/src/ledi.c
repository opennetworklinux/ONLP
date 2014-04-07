/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 *
 ***********************************************************/
#include <onlp/platformi/ledi.h>
#include "onlp_platform_defaults_int.h"
#include "onlp_platform_defaults_log.h"

__ONLP_DEFAULTI_IMPLEMENTATION(onlp_ledi_init(void));
__ONLP_DEFAULTI_IMPLEMENTATION(onlp_ledi_info_get(onlp_oid_t id, onlp_led_info_t* rv));
__ONLP_DEFAULTI_IMPLEMENTATION(onlp_ledi_set(onlp_oid_t id, int on_or_off));
__ONLP_DEFAULTI_IMPLEMENTATION(onlp_ledi_ioctl(onlp_oid_t id, va_list vargs));
__ONLP_DEFAULTI_IMPLEMENTATION(onlp_ledi_mode_set(onlp_oid_t id, onlp_led_mode_t mode));
