/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 * Fan Management.
 *
 ***********************************************************/
#ifndef __ONLP_FAN_H__
#define __ONLP_FAN_H__

#include <onlp/oids.h>
#include <onlp/onlp.h>

/* <auto.start.enum(onlp_fan_caps).define> */
/** onlp_fan_caps */
typedef enum onlp_fan_caps_e {
    ONLP_FAN_CAPS_B2F = (1 << 0),
    ONLP_FAN_CAPS_F2B = (1 << 1),
    ONLP_FAN_CAPS_SET_RPM = (1 << 2),
    ONLP_FAN_CAPS_SET_PERCENTAGE = (1 << 3),
    ONLP_FAN_CAPS_GET_RPM = (1 << 4),
    ONLP_FAN_CAPS_GET_PERCENTAGE = (1 << 5),
} onlp_fan_caps_t;
/* <auto.end.enum(onlp_fan_caps).define> */


/* <auto.start.enum(onlp_fan_status).define> */
/** onlp_fan_status */
typedef enum onlp_fan_status_e {
    ONLP_FAN_STATUS_PRESENT = (1 << 0),
    ONLP_FAN_STATUS_FAILED = (1 << 1),
    ONLP_FAN_STATUS_B2F = (1 << 2),
    ONLP_FAN_STATUS_F2B = (1 << 3),
} onlp_fan_status_t;
/* <auto.end.enum(onlp_fan_status).define> */


/* <auto.start.enum(onlp_fan_mode).define> */
/** onlp_fan_mode */
typedef enum onlp_fan_mode_e {
    ONLP_FAN_MODE_OFF,
    ONLP_FAN_MODE_SLOW,
    ONLP_FAN_MODE_NORMAL,
    ONLP_FAN_MODE_FAST,
    ONLP_FAN_MODE_MAX,
    ONLP_FAN_MODE_LAST = ONLP_FAN_MODE_MAX,
    ONLP_FAN_MODE_COUNT,
    ONLP_FAN_MODE_INVALID = -1,
} onlp_fan_mode_t;
/* <auto.end.enum(onlp_fan_mode).define> */

/* <auto.start.enum(onlp_fan_dir).define> */
/** onlp_fan_dir */
typedef enum onlp_fan_dir_e {
    ONLP_FAN_DIR_B2F,
    ONLP_FAN_DIR_F2B,
    ONLP_FAN_DIR_LAST = ONLP_FAN_DIR_F2B,
    ONLP_FAN_DIR_COUNT,
    ONLP_FAN_DIR_INVALID = -1,
} onlp_fan_dir_t;
/* <auto.end.enum(onlp_fan_dir).define> */


/**
 * Fan information structure.
 */
typedef struct onlp_fan_info_s {
    /** OID Header */
    onlp_oid_hdr_t hdr;

    /* Status */
    uint32_t status;

    /* Capabilities */
    uint32_t caps;

    /* Current fan speed, in RPM, if available */
    int rpm;

    /* Current fan percentage, if available */
    int percentage;

    /* Current fan mode, if available  */
    onlp_fan_mode_t mode;

} onlp_fan_info_t;


/**
 * @brief Initialize the fan subsystem.
 */
int onlp_fan_init(void);


/**
 * @brief Retrieve fan information.
 * @param id The fan OID.
 * @param rv [out] Receives the fan information.
 */
int onlp_fan_info_get(onlp_oid_t id, onlp_fan_info_t* rv);

/**
 * @brief Set the fan speed in RPMs.
 * @param id The fan OID.
 * @param rpm The new RPM.
 * @note Only valid if the fan has the SET_RPM capability.
 */
int onlp_fan_rpm_set(onlp_oid_t id, int rpm);

/**
 * @brief Set the fan speed in percentage.
 * @param id The fan OID.
 * @param p The percentage.
 * @note Only valid if the fan has the SET_PERCENTAGE capability.
 */
int onlp_fan_percentage_set(onlp_oid_t id, int p);

/**
 * @brief Set the fan speed by mode.
 * @param id The fan OID.
 * @param mode The fan mode value.
 */
int onlp_fan_mode_set(onlp_oid_t id, onlp_fan_mode_t mode);

/**
 * @brief Set the fan direction.
 * @param id The fan OID.
 * @param dir The fan direction (B2F or F2B)
 * @notes Only called if both capabilities are set.
 */
int onlp_fan_dir_set(onlp_oid_t id, onlp_fan_dir_t dir);

/**
 * @brief Fan OID debug dump.
 * @param id The fan OID.
 * @param pvs The output pvs.
 * @param flags The output flags.
 */
void onlp_fan_dump(onlp_oid_t id, aim_pvs_t* pvs, uint32_t flags);

/**
 * @brief Show the given Fan OID.
 * @param id The Fan OID
 * @param pvs The output pvs
 * @param flags The output flags. 
 */
void onlp_fan_show(onlp_oid_t id, aim_pvs_t* pvs, uint32_t flags);

#endif /* __ONLP_FAN_H__ */

