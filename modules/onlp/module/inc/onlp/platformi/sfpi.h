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
 * SFP Platform Implementation Interface.
 *
 * This interface must be implemented and available for all
 * platforms that support SFP interfaces.
 *
 ***********************************************************/
#ifndef __ONLP_SFPI_H__
#define __ONLP_SFPI_H__

#include <onlp/onlp_config.h>
#include <onlp/sfp.h>

/**
 * @brief Initialize the SFPI subsystem.
 */
int onlp_sfpi_init(void);

/**
 * @brief Get the bitmap of SFP-capable port numbers.
 * @param bmap [out] Receives the bitmap.
 */
int onlp_sfpi_bitmap_get(onlp_sfp_bitmap_t* bmap);

/**
 * @brief Determine if an SFP is present.
 * @param port The port number.
 * @returns 1 if present
 * @returns 0 if absent
 * @returns An error condition.
 */
int onlp_sfpi_is_present(int port);

/**
 * @brief Read the SFP EEPROM.
 * @param port The port number.
 * @param data Receives the SFP data.
 */
int onlp_sfpi_eeprom_read(int port, uint8_t data[256]);

/**
 * @brief Enable or disable the given SFP.
 * @param port The port number.
 * @param enable Enable the SFP is 1, Disable the SFP if 0
 */
int onlp_sfpi_enable_set(int port, int enable);

/**
 * @brief Get the current enable state.
 * @param port The port number.
 * @param enable [out] Receives the enable state.
 */
int onlp_sfpi_enable_get(int port, int* enable);

/**
 * @brief Perform any actions required after an SFP is inserted.
 * @param port The port number.
 * @param eeprom The eeprom data for the new SFP.
 * @notes Optional
 */
int onlp_sfpi_post_insert(int port, uint8_t eeprom[256]);

/**
 * @brief Reset the SFP if supported.
 * @param port The port number.
 * @notes Optional
 */
int onlp_sfpi_reset(int port);

/**
 * @brief Get the current status flags for an SFP.
 * @param port The port number.
 * @param status [out] Receives the status flags.
 * @notes See onlp_sfp_status_t
 */
int onlp_sfpi_status_get(int port, uint32_t* status);

/**
 * @brief Deinitialize the SFP driver.
 */
int onlp_sfpi_denit(void);

/**
 * @brief Generic debug status information.
 * @param port The port number.
 * @param pvs The output pvs.
 * @notes The purpose of this vector is to allow reporting of internal debug
 * status and information from the platform driver that might be used to debug
 * SFP runtime issues.
 * For example, internal equalizer settings, tuning status information, status
 * of additional signals useful for system debug but not exposed in this interface.
 *
 * @notes This is function is optional.
 */
void onlp_sfpi_debug(int port, aim_pvs_t* pvs);

/**
 * @brief Generic ioctl
 * @param port The port number
 * @param The variable argument list of parameters.
 *
 * @notes This generic ioctl interface can be used
 * for platform-specific or driver specific features
 * that cannot or have not yet been defined in this
 * interface. It is intended as a future feature expansion
 * support mechanism.
 *
 * @notes Optional
 */
int onlp_sfpi_ioctl(int port, va_list vargs);


#endif /* __ONLP_SFPI_H__ */
