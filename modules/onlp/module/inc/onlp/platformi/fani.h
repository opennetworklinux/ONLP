/************************************************************
 *
 * Fan Interface
 *
 ************************************************************/
#ifndef __ONLP_FANI_H__
#define __ONLP_FANI_H__

#include <onlp/fan.h>

/**
 * Initialize
 */
typedef int (*onlp_fani_init_f)(void);

/**
 * Query fan info
 */
typedef int (*onlp_fani_info_get_f)(onlp_oid_t fid, onlp_fan_info_t* rv);

/**
 * Set the fan speed (if supported)
 */
typedef int (*onlp_fani_speed_set_f)(onlp_oid_t fid, uint32_t rpm);

/**
 * Set the fan direction (if supported)
 */
typedef int (*onlp_fani_direction_set_f)(onlp_oid_t fid, int direction);

/**
 * Fan ioctl
 */
typedef int (*onlp_fani_ioctl_f)(onlp_oid_t fid, va_list vargs);


typedef struct onlp_fani_vectors_s {
    onlp_fani_init_f init;
    onlp_fani_info_get_f info_get;
    onlp_fani_speed_set_f speed_set;
    onlp_fani_direction_set_f direction_set;
    onlp_fani_ioctl_f ioctl;
} onlp_fani_vectors_t;

/**
 * This is the interface implementation vector create function.
 * The platform provider must implement a single entry point
 * called 'onlp_fani_vectors_create' with the following signature:
 */
typedef int (*onlp_fani_vectors_create_f)(onlp_fani_vectors_t* rv);

int onlp_fani_vectors_create(onlp_fani_vectors_t* rv);


#endif /* __ONLP_FANI_H__ */

