/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 *
 *
 ***********************************************************/
#include <onlp/onlp.h>
#include <onlp/oids.h>

int
onlpdump_main(int argc, char* argv[])
{
    onlp_init();
    onlp_platform_dump(&aim_pvs_stdout,
                       ONLP_OID_SHOW_F_RECURSE | ONLP_OID_SHOW_F_EVEN_IF_ABSENT);
    return 0;
}
