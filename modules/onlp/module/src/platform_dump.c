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
onlp_platform_dump(aim_pvs_t* pvs, uint32_t flags)
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
    aim_printf(pvs, "\n");
    aim_printf(pvs, "System Information:\n");
    onlp_onie_show(&sysinfo.onie_info, pvs, "  ");
    aim_printf(pvs, "\n");

    /* Dump all platform OID objects */
    onlp_oids_show(sysinfo.oids, AIM_ARRAYSIZE(sysinfo.oids), pvs, flags);

    aim_printf(pvs, "\nSFPs:\n");
    /* Dump all SFPs */
    onlp_sfp_dump(pvs);
}

