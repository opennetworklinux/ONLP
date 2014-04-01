/************************************************************
 *
 * Power Supply Management Implementation.
 *
 ***********************************************************/
#include <onlp/platformi/psui.h>
#include "onlp_platform_defaults_int.h"

__ONLP_DEFAULTI_IMPLEMENTATION(onlp_psui_init(void));
__ONLP_DEFAULTI_IMPLEMENTATION(onlp_psui_info_get(onlp_oid_t id, onlp_psu_info_t* rv));
__ONLP_DEFAULTI_IMPLEMENTATION(onlp_psui_ioctl(onlp_oid_t pid, va_list vargs));
