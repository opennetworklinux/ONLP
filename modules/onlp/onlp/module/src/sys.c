/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 *
 *
 ***********************************************************/
#include <onlp/sys.h>
#include <onlp/platformi/sysi.h>
#include <onlplib/mmap.h>
#include <AIM/aim.h>
#include "onlp_log.h"

int
onlp_sys_init(void)
{
    int rv;

    const char* pname = onlp_sysi_platform_get();
    AIM_LOG_MSG("onlp_sys_init: platform is '%s'", pname);

    /*
     * TODO:
     * Platform verification and override logic as per documentation in
     * sysi.h
     *
     */
    rv = onlp_sysi_init();
    return rv;
}

static uint8_t*
onie_data_get__(int* free)
{
    void* pa;
    uint8_t* ma = NULL;
    int size;
    if(onlp_sysi_onie_data_phys_addr_get(&pa) == 0) {
        ma = onlp_mmap((off_t)pa, 64*1024, "onie_data_get__");
        *free = 0;
    }
    else if(onlp_sysi_onie_data_get(&ma, &size) == 0) {
        *free = 1;
    }
    else {
        ma = NULL;
        *free = 0;
    }
    return ma;
}

int
onlp_sys_info_get(onlp_sys_info_t* rv)
{
    if(rv == NULL) {
        return -1;
    }

    memset(rv, 0, sizeof(*rv));

    /**
     * Get the system ONIE information.
     */
    int free;
    uint8_t* onie_data = onie_data_get__(&free);
    onlp_onie_decode(&rv->onie_info, onie_data, -1);
    if(free) {
        onlp_sysi_onie_data_free(onie_data);
    }

    /*
     * Query the sys oids
     */
    onlp_sysi_oids_get(rv->oids, AIM_ARRAYSIZE(rv->oids));

    return 0;
}
