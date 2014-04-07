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

static char*
platform_detect_fs__(int warn)
{
    /*
     * Check the filesystem for the platform identifier.
     */
    char* rv = NULL;
    if(ONLP_CONFIG_PLATFORM_FILENAME) {
        FILE* fp;
        if((fp=fopen(ONLP_CONFIG_PLATFORM_FILENAME, "r"))) {
            char platform[256];
            if(fgets(platform, sizeof(platform), fp) == platform) {
                /* TODO: Base this detection on the global platform registry. */
                if(platform[0]) {
                    if(platform[ONLP_STRLEN(platform)-1] == '\n') {
                        platform[ONLP_STRLEN(platform)-1] = 0;
                    }
                    rv = aim_strdup(platform);
                }
            }
            fclose(fp);
        }
        else {
            if(warn) {
                AIM_LOG_WARN("could not open platform filename '%s'", ONLP_CONFIG_PLATFORM_FILENAME);
            }
        }
    }
    return rv;
}

static char*
platform_detect__(void)
{
    /* Only detection from the filesystem is currently supported. */
    return platform_detect_fs__(1);
}

int
onlp_sys_init(void)
{
    int rv;

    const char* current_platform = platform_detect__();
    if(current_platform == NULL) {
        AIM_DIE("Could not determine the current platform.");
    }
    const char* current_interface = onlp_sysi_platform_get();
    if(current_interface == NULL) {
        AIM_DIE("The platform driver did not return an appropriate platform identifier.");
    }
    AIM_LOG_MSG("onlp_sys_init: current is %s, interface is %s", current_platform, current_interface);

    if(strcmp(current_interface, current_platform)) {
        /* They do not match. Ask the interface if it supports the current platform. */
        int rv = onlp_sysi_platform_set(current_platform);
        if(rv < 0) {
            AIM_DIE("The current platform interface (%s) does not support the current platform (%s). This is fatal.",
                    current_interface, current_platform);
        }
    }

    /* If we get here, its all good */
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
    onlp_sysi_oids_get(rv->oid_table, AIM_ARRAYSIZE(rv->oid_table));

    return 0;
}
