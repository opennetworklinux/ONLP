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
#include <onlp/onlp_config.h>
#include <onlp/onlp.h>

#include <onlp/sys.h>
#include <onlp/sfp.h>
#include <onlp/led.h>
#include <onlp/psu.h>
#include <onlp/fan.h>
#include <onlp/thermal.h>

#include "onlp_int.h"
#include "onlp_json.h"

int
onlp_init(void)
{
    char* cfile;

    if( (cfile=getenv(ONLP_CONFIG_CONFIGURATION_ENV)) == NULL) {
        cfile = ONLP_CONFIG_CONFIGURATION_FILENAME;
    }

    onlp_json_init(cfile);
    onlp_sys_init();
    onlp_sfp_init();
    onlp_led_init();
    onlp_psu_init();
    onlp_fan_init();
    onlp_thermal_init();
    return 0;
}
