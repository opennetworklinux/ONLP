/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 * LED Management
 *
 ***********************************************************/
#ifndef __ONLP_LED_H__
#define __ONLP_LED_H__

#include <onlp/onlp.h>
#include <onlp/oids.h>

/* <auto.start.enum(onlp_led_status).define> */
/** onlp_led_status */
typedef enum onlp_led_status_e {
    ONLP_LED_STATUS_PRESENT = (1 << 0),
    ONLP_LED_STATUS_FAILED = (1 << 1),
    ONLP_LED_STATUS_ON = (1 << 2),
} onlp_led_status_t;
/* <auto.end.enum(onlp_led_status).define> */

/* <auto.start.enum(onlp_led_caps).define> */
/** onlp_led_caps */
typedef enum onlp_led_caps_e {
    ONLP_LED_CAPS_ON_OFF = (1 << 0),
    ONLP_LED_CAPS_RED = (1 << 2),
    ONLP_LED_CAPS_RED_BLINKING = (1 << 3),
    ONLP_LED_CAPS_ORANGE = (1 << 4),
    ONLP_LED_CAPS_ORANGE_BLINKING = (1<<5),
    ONLP_LED_CAPS_YELLOW = ( 1 << 6),
    ONLP_LED_CAPS_YELLOW_BLINKING = (1<<7),
    ONLP_LED_CAPS_GREEN = (1 << 8),
    ONLP_LED_CAPS_GREEN_BLINKING = (1 << 9),
    ONLP_LED_CAPS_BLUE = (1 << 10),
    ONLP_LED_CAPS_BLUE_BLINKING = (1<<11),
    ONLP_LED_CAPS_PURPLE = (1 << 12),
    ONLP_LED_CAPS_PURPLE_BLINKING = (1 << 13),
} onlp_led_caps_t;
/* <auto.end.enum(onlp_led_caps).define> */

/* <auto.start.enum(onlp_led_mode).define> */
/** onlp_led_mode */
typedef enum onlp_led_mode_e {
    ONLP_LED_MODE_OFF,
    ONLP_LED_MODE_ON,
    ONLP_LED_MODE_BLINKING,
    ONLP_LED_MODE_RED,
    ONLP_LED_MODE_RED_BLINKING,
    ONLP_LED_MODE_ORANGE,
    ONLP_LED_MODE_ORANGE_BLINKING,
    ONLP_LED_MODE_YELLOW,
    ONLP_LED_MODE_YELLOW_BLINKING,
    ONLP_LED_MODE_GREEN,
    ONLP_LED_MODE_GREEN_BLINKING,
    ONLP_LED_MODE_BLUE,
    ONLP_LED_MODE_BLUE_BLINKING,
    ONLP_LED_MODE_PURPLE,
    ONLP_LED_MODE_PURPLE_BLINKING,
    ONLP_LED_MODE_LAST = ONLP_LED_MODE_PURPLE_BLINKING,
    ONLP_LED_MODE_COUNT,
    ONLP_LED_MODE_INVALID = -1,
} onlp_led_mode_t;
/* <auto.end.enum(onlp_led_mode).define> */

/**
 * LED information structure.
 */
typedef struct onlp_led_info_s {
    /** Header */
    onlp_oid_hdr_t hdr;

    /** Status */
    uint32_t status;

    /** Capabilities */
    uint32_t caps;

    /** Current mode, if capable. */
    onlp_led_mode_t mode;
} onlp_led_info_t;

/**
 * @brief Initialize the LED subsystem.
 */
int onlp_led_init(void);

/**
 * @brief Get LED information.
 * @param id The LED OID
 * @param rv [out] Receives the information structure.
 */
int onlp_led_info_get(onlp_oid_t id, onlp_led_info_t* rv);

/**
 * @brief Turn an LED on or off.
 * @param id The LED OID
 * @param on_or_off Led on (1) or LED off (0)
 * @param Relevant if the LED has the ON_OFF capability.
 * @note For the purposes of this function the
 * interpretation of "on" for multi-mode or multi-color LEDs
 * is up to the platform implementation.
 */
int onlp_led_set(onlp_oid_t id, int on_or_off);

/**
 * @brief Set the LED color
 * @param id The LED OID
 * @param color The color.
 * @note Only relevant if the LED supports the color capability.
 */
int onlp_led_mode_set(onlp_oid_t id, onlp_led_mode_t color);

#endif /* __ONLP_LED_H__ */
