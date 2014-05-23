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
#ifndef __ONLP_ONLP_H__
#define __ONLP_ONLP_H__

#include <onlp/onlp_config.h>

/* <auto.start.enum(onlp_status).define> */
/** onlp_status */
typedef enum onlp_status_e {
    ONLP_STATUS_OK = 0,
    ONLP_STATUS_E_UNSUPPORTED = -1,
    ONLP_STATUS_E_MISSING = -2,
    ONLP_STATUS_E_INVALID = -3,
    ONLP_STATUS_E_INTERNAL = -4,
} onlp_status_t;
/* <auto.end.enum(onlp_status).define> */



/**
 * @brief Initialize all subsystems.
 */
int onlp_init(void);


/**
 * @brief Dump the current platform data.
 * @param pvs The output pvs
 */

void onlp_platform_dump(aim_pvs_t* pvs, uint32_t flags);
void onlp_platform_show(aim_pvs_t* pvs, uint32_t flags);

#endif /* __ONLP_ONLP_H__ */
