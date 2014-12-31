/*************************************************************
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
 *************************************************************
 *
 * SFP Management Interface.
 *
 ************************************************************/
#ifndef __ONLP_SFP_H__
#define __ONLP_SFP_H__

#include <onlp/onlp_config.h>
#include <onlp/onlp.h>
#include <AIM/aim_bitmap.h>
#include <AIM/aim_pvs.h>
#include <sff/sff.h>

/* <auto.start.enum(tag:sfp).define> */
/** onlp_sfp_status */
typedef enum onlp_sfp_status_e {
    ONLP_SFP_STATUS_TX_FAILURE = (1 << 0),
    ONLP_SFP_STATUS_RX_LOS = (1 << 1),
    ONLP_SFP_STATUS_TX_DISABLED = (1 << 2),
} onlp_sfp_status_t;

/** onlp_sfp_control */
typedef enum onlp_sfp_control_e {
    ONLP_SFP_CONTROL_LPMODE,
    ONLP_SFP_CONTROL_TX_DISABLE,
    ONLP_SFP_CONTROL_LAST = ONLP_SFP_CONTROL_TX_DISABLE,
    ONLP_SFP_CONTROL_COUNT,
    ONLP_SFP_CONTROL_INVALID = -1,
} onlp_sfp_control_t;
/* <auto.end.enum(tag:sfp).define> */


/**
 * Initialize the SFP subsystem.
 */
int onlp_sfp_init(void);

/**
 * Valid SFP Port bitmaps are communicated using this type.
 */
typedef aim_bitmap256_t onlp_sfp_bitmap_t;

/**
 * @brief Get the set of valid {Q}SFP ports.
 * @param bmap Returns the valid set of SFP-capable port numbers.
 */
int onlp_sfp_bitmap_get(onlp_sfp_bitmap_t* bmap);

/**
 * @brief Determine if a given port number is a valid SFP port.
 * @param port The port number.
 */
int onlp_sfp_port_valid(int port);

/**
 * @brief Determine if an SFP is currently plugged in.
 * @param port The SFP port number.
 * @returns 1 if an SFP is present.
 * @returns 0 if an SFP is not present.
 * @returns <0 on error.
 */
int onlp_sfp_is_present(int port);

/**
 * @brief Read IEEE standard EEPROM data from the given port.
 * @param port The SFP Port
 * @param rv Receives a buffer containing the EEPROM data.
 * @notes The buffer must be freed after use.
 * @returns The size of the eeprom data, if successful
 * @returns -1 on error.
 */
int onlp_sfp_eeprom_read(int port, uint8_t** rv);

/**
 * @brief Reset the SFP on the given port.
 * @param port The SFP port.
 */
int onlp_sfp_reset(int port);

/**
 * @brief Reset all SFP ports.
 */
int onlp_sfp_reset_all(void);

/**
 * @brief Deinitialize the SFP subsystem.
 */
int onlp_sfp_denit(void);

/**
 * @brief Set the enable state on the given SFP.
 * @param port The SFP port.
 * @param enable The new enable state.
 */
int onlp_sfp_enable_set(int port, int enable);

/**
 * @brief Get the enable state of the given SFP.
 * @param port The SFP port.
 * @param [out] enable Receives the enable state.
 */
int onlp_sfp_enable_get(int port, int* enable);

typedef void (onlp_sfp_event_handler_f)(int port, void* cookie);

/**
 * @brief Register for notifications on SFP events.
 * @param handler The event handler.
 * @param cookie The cookie passed to the handler.
 */
int onlp_sfp_event_register(onlp_sfp_event_handler_f hander, void* cookie);

/**
 * @brief Start or stop event processing.
 */
int onlp_sfp_events_enable_set(int enable);

/**
 * @brief Query event processing status.
 */
int onlp_sfp_events_enable_get(int* enable);

/**
 * @brief Dump the status of all SFPs
 * @param pvs The output pvs.
 */
void onlp_sfp_dump(aim_pvs_t* pvs);

/**
 * @brief Issue an ioctl to the SFP interface.
 * @param port The port.
 * @param ... Ioctl arguments.
 */
int onlp_sfp_ioctl(int port, ...);

/**
 * @brief Call the SFP post-insertion handler.
 *
 */
int onlp_sfp_post_insert(int port, sff_info_t* info);

/**
 * @brief Retrieve the SFP status flags.
 * @param port The port.
 * @param [out] flags Receives the flags.
 * @note See onlp_sfp_status_t
 */
int onlp_sfp_status_get(int port, uint32_t* flags);

/**
 * @brief Set an SFP control.
 * @param port The port.
 * @param control The control.
 * @param value The value.
 */
int onlp_sfp_control_set(int port, onlp_sfp_control_t control, int value);

/**
 * @brief Get an SFP control.
 * @param port The port.
 * @param control The control
 * @param [out] value Receives the current value.
 */
int onlp_sfp_control_get(int port, onlp_sfp_control_t control, int* value);

/******************************************************************************
 *
 * Enumeration Support Definitions.
 *
 * Please do not add additional code beyond this point.
 *
 *****************************************************************************/
/* <auto.start.enum(tag:sfp).supportheader> */
/** Enum names. */
const char* onlp_sfp_status_name(onlp_sfp_status_t e);

/** Enum values. */
int onlp_sfp_status_value(const char* str, onlp_sfp_status_t* e, int substr);

/** Enum descriptions. */
const char* onlp_sfp_status_desc(onlp_sfp_status_t e);

/** Enum validator. */
int onlp_sfp_status_valid(onlp_sfp_status_t e);

/** validator */
#define ONLP_SFP_STATUS_VALID(_e) \
    (onlp_sfp_status_valid((_e)))

/** onlp_sfp_status_map table. */
extern aim_map_si_t onlp_sfp_status_map[];
/** onlp_sfp_status_desc_map table. */
extern aim_map_si_t onlp_sfp_status_desc_map[];

/** Strings macro. */
#define ONLP_SFP_CONTROL_STRINGS \
{\
    "LPMODE", \
    "TX_DISABLE", \
}
/** Enum names. */
const char* onlp_sfp_control_name(onlp_sfp_control_t e);

/** Enum values. */
int onlp_sfp_control_value(const char* str, onlp_sfp_control_t* e, int substr);

/** Enum descriptions. */
const char* onlp_sfp_control_desc(onlp_sfp_control_t e);

/** validator */
#define ONLP_SFP_CONTROL_VALID(_e) \
    ( (0 <= (_e)) && ((_e) <= ONLP_SFP_CONTROL_TX_DISABLE))

/** onlp_sfp_control_map table. */
extern aim_map_si_t onlp_sfp_control_map[];
/** onlp_sfp_control_desc_map table. */
extern aim_map_si_t onlp_sfp_control_desc_map[];
/* <auto.end.enum(tag:sfp).supportheader> */

#endif /* __ONLP_SFP_H__ */
