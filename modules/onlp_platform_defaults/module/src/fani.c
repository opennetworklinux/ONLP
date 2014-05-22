/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 * Fan Platform Implementation Defaults.
 *
 ***********************************************************/
#include <onlp/platformi/fani.h>
#include "onlp_platform_defaults_int.h"
#include "onlp_platform_defaults_log.h"

/**
 * These are the default implementations for all currently
 * defined interface functions.
 */
__ONLP_DEFAULTI_IMPLEMENTATION(onlp_fani_init(void));
__ONLP_DEFAULTI_IMPLEMENTATION(onlp_fani_info_get(onlp_oid_t id, onlp_fan_info_t* info));
__ONLP_DEFAULTI_IMPLEMENTATION(onlp_fani_rpm_set(onlp_oid_t id, int rpm));
__ONLP_DEFAULTI_IMPLEMENTATION(onlp_fani_percentage_set(onlp_oid_t id, int p));
__ONLP_DEFAULTI_IMPLEMENTATION(onlp_fani_mode_set(onlp_oid_t id, onlp_fan_mode_t mode));
__ONLP_DEFAULTI_IMPLEMENTATION(onlp_fani_dir_set(onlp_oid_t id, onlp_fan_dir_t dir));
__ONLP_DEFAULTI_IMPLEMENTATION(onlp_fani_ioctl(onlp_oid_t id, va_list vargs));

