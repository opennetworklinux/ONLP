/************************************************************
 *
 * Thermal Sensor Implementation.
 *
 ***********************************************************/
#ifndef __ONLP_THERMALI_H__
#define __ONLP_THERMALI_H__

#include <onlp/thermal.h>

/**
 * Initialize thermal system.
 */
typedef int (*onlp_thermali_init_f)(void);

/**
 * Get the information for this thermal id
 */
typedef int (*onlp_thermali_info_get_f)(onlp_oid_t tid, onlp_thermal_info_t* rv);


/* Thermal vector structure */
typedef struct onlp_thermali_vectors_s {
    onlp_thermali_init_f init;
    onlp_thermali_info_get_f info_get;
} onlp_thermali_vectors_t;

/**
 * This is the interface implementation vector create function.
 * The platform provider must implement a single entry point
 * called 'onlp_thermali_vectors_create' with the following signature:
 */
typedef int (*onlp_thermali_vectors_create_f)(onlp_thermali_vectors_t* rv);

int onlp_thermali_vectors_create(onlp_thermali_vectors_t* rv);



#endif /* __ONLP_THERMALI_H__ */
