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
#include <onlp/platformi/psui.h>
#include "onlpie_int.h"

/*
 * This function will be called prior to any other onlp_psui functions.
 */
int
onlp_psui_init(void)
{
    return ONLP_STATUS_OK;
}

/*
 * Get all information about the given PSU oid.
 */
static onlp_psu_info_t pinfo[] =
    {
        { }, /* Not used */
        {
            {
                ONLP_PSU_ID_CREATE(1), "PSU-1", 0,
                /* This PSU has 2 fans */
                { ONLP_FAN_ID_CREATE(3), ONLP_FAN_ID_CREATE(4) }
            },
            "ONLPIE PSU MODEL (AC)",
            0x1,
            ONLP_PSU_CAPS_AC | ONLP_PSU_CAPS_VIN | ONLP_PSU_CAPS_VOUT | ONLP_PSU_CAPS_IIN,
            240.0,
            12.0,
            2.0,
            3.0,
            0,
            0,
        },
        {
            { ONLP_PSU_ID_CREATE(2), "PSU-2", 0 },
            "",
            0,
        },
        {
            { ONLP_PSU_ID_CREATE(3), "PSU-3", 0 },
            "ONLPIE PSU MODEL (DC)",
            0x1,
            ONLP_PSU_CAPS_DC48,
            48,
            12,
            2.0
        },
    };


int
onlp_psui_info_get(onlp_oid_t id, onlp_psu_info_t* info)
{
    *info = pinfo[ONLP_OID_ID_GET(id)];
    return ONLP_STATUS_OK;
}

/*
 * This is an optional generic ioctl() interface.
 * Its purpose is to allow future expansion and
 * custom functionality that is not otherwise exposed
 * in the standard interface.
 *
 * The semantics of this function are platform specific.
 * This function is completely optional.
 */
int
onlp_psui_ioctl(onlp_oid_t pid, va_list vargs)
{
    return ONLP_STATUS_E_UNSUPPORTED;
}
