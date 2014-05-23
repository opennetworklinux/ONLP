/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * 
 *           Copyright 2014 Big Switch Networks, Inc.          
 * 
 * Licensed under the Eclipse Public License, Version 1.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 * 
 *        http://www.eclipse.org/legal/epl-v10.html
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the
 * License.
 * 
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
#include "onlp_int.h"

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
#if ONLP_CONFIG_INCLUDE_PLATFORM_STATIC == 1
    return ONLP_CONFIG_PLATFORM_STATIC ;
#endif
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
    onlp_sysi_oids_get(rv->hdr.coids, AIM_ARRAYSIZE(rv->hdr.coids));

    return 0;
}

void
onlp_sys_info_free(onlp_sys_info_t* info)
{
    onlp_onie_info_free(&info->onie_info);
}

void
onlp_sys_dump(onlp_oid_t id, aim_pvs_t* pvs, uint32_t flags)
{
    int rv;
    iof_t iof;
    onlp_sys_info_t si;

    onlp_oid_dump_iof_init_default(&iof, pvs);

    if(ONLP_OID_TYPE_GET(id) != ONLP_OID_TYPE_SYS) {
        return;
    }

    iof_push(&iof, "System Information");
    rv = onlp_sys_info_get(&si);
    if(rv < 0) {
        onlp_oid_info_get_error(&iof, rv);
        iof_pop(&iof);
        return;
    }
    else {
        onlp_onie_show(&si.onie_info, &iof.inherit);
        iof_pop(&iof);
    }
    onlp_oid_table_dump(si.hdr.coids, pvs, flags);
    onlp_sys_info_free(&si);
}

void
onlp_sys_show(onlp_oid_t id, aim_pvs_t* pvs, uint32_t flags)
{
    int rv;
    iof_t iof;
    onlp_sys_info_t si;

    onlp_oid_show_iof_init_default(&iof, pvs);

    if(id && ONLP_OID_TYPE_GET(id) != ONLP_OID_TYPE_SYS) {
        return;
    }

    rv = onlp_sys_info_get(&si);
    if(rv < 0) {
        onlp_oid_info_get_error(&iof, rv);
        return;
    }

    /*
     * The system information is not actually shown
     * unless you specify EXTENDED or !RECURSIVE
     */
    if(flags & ONLP_OID_SHOW_F_EXTENDED ||
       (flags & ONLP_OID_SHOW_F_RECURSE) == 0) {
        iof_push(&iof, "System Information");
        onlp_onie_show(&si.onie_info, &iof.inherit);
        iof_pop(&iof);
    }

    if(flags & ONLP_OID_SHOW_F_RECURSE) {

        /** Show all Chassis Fans */
        onlp_oid_t* oidp;
        ONLP_OID_TABLE_ITER_TYPE(si.hdr.coids, oidp, FAN) {
            onlp_oid_show(*oidp, &iof.inherit, flags);
        }
        /** Show all System Thermals */
        ONLP_OID_TABLE_ITER_TYPE(si.hdr.coids, oidp, THERMAL) {
            onlp_oid_show(*oidp, &iof.inherit, flags);
        }
        /** Show all PSUs */
        ONLP_OID_TABLE_ITER_TYPE(si.hdr.coids, oidp, PSU) {
            onlp_oid_show(*oidp, &iof.inherit, flags);
        }

        if(flags & ONLP_OID_SHOW_F_EXTENDED) {
            /** Show all LEDs */
            ONLP_OID_TABLE_ITER_TYPE(si.hdr.coids, oidp, LED) {
                onlp_oid_show(*oidp, &iof.inherit, flags);
            }
        }
    }
    onlp_sys_info_free(&si);
}


