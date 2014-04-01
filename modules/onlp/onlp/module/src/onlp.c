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
#include <onlp/led.h>
#include <onlp/psu.h>
#include <onlp/fan.h>
#include <onlp/thermal.h>

int
onlp_init(void)
{
    onlp_sys_init();
    onlp_sfp_init();
    onlp_led_init();
    onlp_psu_init();
    onlp_fan_init();
    onlp_thermal_init();
    return 0;
}
