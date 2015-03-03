/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 *
 *
 ***********************************************************/
#ifndef __ONLP_GPIO_H__
#define __ONLP_GPIO_H__

#include <onlplib/onlplib_config.h>

typedef enum onlp_gpio_direction_e {
    ONLP_GPIO_DIRECTION_NONE,
    ONLP_GPIO_DIRECTION_IN,
    ONLP_GPIO_DIRECTION_OUT,
    ONLP_GPIO_DIRECTION_LOW,
    ONLP_GPIO_DIRECTION_HIGH,
} onlp_gpio_direction_t;

/**
 * @brief Export the given GPIO and set its direction.
 * @param gpio The gpio number.
 * @param dir The gpio direction.
 */
int onlp_gpio_export(int gpio, onlp_gpio_direction_t dir);

/**
 * @brief Set the given GPIO value.
 * @param gpio The gpio number.
 * @param v The value to set.
 * @param ... Additional GPIO and Value parameters.
 */
int onlp_gpio_set(int gpio, int v);

/**
 * @brief Get the given GPIO value.
 * @param gpio The gpio number.
 * @returns Returns the value or negative on error.
 */
int onlp_gpio_get(int gpio, int* rv);


#endif /* __ONLP_GPIO_H__ */
