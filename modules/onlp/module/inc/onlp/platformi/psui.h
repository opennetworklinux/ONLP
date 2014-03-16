/************************************************************
 *
 * Power Supply Management Implementation.
 *
 ***********************************************************/
#ifndef __ONLP_PSUI_H__
#define __ONLP_PSUI_H__

#include <onlp/psu.h>

/**
 * Init
 */
typedef int (*onlp_psui_init_f)(void);

/**
 * info_get
 */
typedef int (*onlp_psui_info_get_f)(onlp_oid_t pid, onlp_psu_info_t* rv);

/**
 * ioctl
 */
typedef int (*onlp_psui_ioctl_f)(onlp_oid_t pid, va_list vargs);


typedef struct onlp_psui_vectors_s {

    onlp_psui_init_f init;
    onlp_psui_info_get_f info_get;
    onlp_psui_ioctl_f ioctl;

} onlp_psui_vectors_t;

/**
 * This is the interface implementation vector create function.
 * The platform provider must implement a single entry point
 * called 'onlp_psui_vectors_create' with the following signature:
 */
typedef int (*onlp_psui_vectors_create_f)(onlp_psui_vectors_t* rv);

int onlp_psui_vectors_create(onlp_psui_vectors_t* rv);


#endif /* __ONLP_PSUI_H__ */
