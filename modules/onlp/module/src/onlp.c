/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 *
 *
 ***********************************************************/
#include <onlp/onlp_config.h>
#include <onlp/onlp.h>
#include <onlp/sys.h>
#include <onlp/sfp.h>


int
onlp_init(void)
{
    onlp_sys_init();
    onlp_sfp_init();
    return 0;
}
