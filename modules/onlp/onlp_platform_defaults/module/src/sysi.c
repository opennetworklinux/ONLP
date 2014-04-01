/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 *
 ***********************************************************/
#include <onlp/platformi/sysi.h>
#include "onlp_platform_defaults_int.h"

const char* __ONLP_DEFAULTI
onlp_sysi_platform_get(void)
{
    /*
     * This function should never be called.
     *
     * If we get here its because the platform libraries are
     * not written, initialized, or setup properly before we execute.
     */
    AIM_LOG_ERROR("The default implementation of onlp_sysi_platform_get() has been called.");
    AIM_LOG_ERROR("This can happen for the following reasons, all fatal:");
    AIM_LOG_ERROR("* The ONLP build configuration is incorrect.");
    AIM_LOG_ERROR("* The ONLP platform library for this platform does not contain the onlp_sysi_platform_get() symbol.");
    AIM_LOG_ERROR("* The ONLP platform shared libraries are not setup properly before we executed.");

#if ONLP_CONFIG_INCLUDE_PLATFORM_ERROR_CHECK == 1
    AIM_LOG_ERROR("* The platform cannot continue until this issue is resolved.");
    abort();
#endif

    return ONLP_SYSI_PLATFORM_NAME_DEFAULT;
}

__ONLP_DEFAULTI_IMPLEMENTATION(onlp_sysi_platform_set(const char* p));
__ONLP_DEFAULTI_IMPLEMENTATION(onlp_sysi_init(void));
__ONLP_DEFAULTI_IMPLEMENTATION(onlp_sysi_onie_data_phys_addr_get(void** physaddr));
__ONLP_DEFAULTI_IMPLEMENTATION(onlp_sysi_onie_data_get(uint8_t** data, int* size));
__ONLP_DEFAULTI_VIMPLEMENTATION(onlp_sysi_onie_data_free(uint8_t* data));
__ONLP_DEFAULTI_IMPLEMENTATION(onlp_sysi_oids_get(onlp_oid_t* table, int max));
__ONLP_DEFAULTI_IMPLEMENTATION(onlp_sysi_ioctl(int id, va_list vargs));

