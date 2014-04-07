/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 *
 ***********************************************************/
#include <onlp/platformi/sfpi.h>
#include "onlp_platform_defaults_int.h"
#include "onlp_platform_defaults_log.h"

__ONLP_DEFAULTI_IMPLEMENTATION(onlp_sfpi_init(void));
__ONLP_DEFAULTI_IMPLEMENTATION(onlp_sfpi_bitmap_get(onlp_sfp_bitmap_t* bmap));
__ONLP_DEFAULTI_IMPLEMENTATION(onlp_sfpi_is_present(int port));
__ONLP_DEFAULTI_IMPLEMENTATION(onlp_sfpi_eeprom_read(int port, uint8_t data[256]));
__ONLP_DEFAULTI_IMPLEMENTATION(onlp_sfpi_enable_set(int port, int enable));
__ONLP_DEFAULTI_IMPLEMENTATION(onlp_sfpi_enable_get(int port, int* enable));
__ONLP_DEFAULTI_IMPLEMENTATION(onlp_sfpi_post_insert(int port, uint8_t eeprom[256]));
__ONLP_DEFAULTI_IMPLEMENTATION(onlp_sfpi_reset(int port));
__ONLP_DEFAULTI_IMPLEMENTATION(onlp_sfpi_status_get(int port, uint32_t* status));
__ONLP_DEFAULTI_IMPLEMENTATION(onlp_sfpi_denit(void));
__ONLP_DEFAULTI_VIMPLEMENTATION(onlp_sfpi_debug(int port, aim_pvs_t* pvs));
__ONLP_DEFAULTI_IMPLEMENTATION(onlp_sfpi_ioctl(int port, va_list vargs));
