/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 *
 *
 ***********************************************************/
#include <onlp/onlp.h>
#include <onlp/sys.h>
#include <onlp/oids.h>
#include <onlp/sfp.h>

void
onlp_platform_dump(aim_pvs_t* pvs)
{
    /* Everything starts with the SYS interface. */
    int rv;
    onlp_sys_info_t sysinfo;
    onlp_sys_init();
    rv = onlp_sys_info_get(&sysinfo);
    if(rv < 0) {
        aim_printf(pvs, "sys_info_get() failed: %d\n", rv);
        return;
    }

    /* Display the ONIE system information */
    aim_printf(pvs, "System Information:\n");
    onlp_onie_show(&sysinfo.onie_info, pvs, "  ");

    /* Dump all platform OID objects */
    int i;
    for(i = 0; i < AIM_ARRAYSIZE(sysinfo.oids); i++) {
        if(sysinfo.oids[i] != 0) {
            /* Valid OID */
            onlp_oid_show(sysinfo.oids[i], pvs);
        }
    }

    /* Dump all SFPs */
    onlp_sfp_dump(pvs);
}

