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
    /* Dump all OIDS, starting with the SYS OID */
    onlp_oid_dump(ONLP_OID_SYS, pvs, flags);
    aim_printf(pvs, "\nSFPs:\n");
    /* Dump all SFPs */
    onlp_sfp_dump(pvs);
}

void
onlp_platform_show(aim_pvs_t* pvs, uint32_t flags)
{
    onlp_oid_show(ONLP_OID_SYS, pvs, flags);
}
