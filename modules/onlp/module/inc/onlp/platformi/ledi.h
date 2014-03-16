/************************************************************
 *
 * LED Interface Implementation
 *
 ***********************************************************/
#ifndef __ONLP_LEDI_H__
#define __ONLP_LEDI_H__

#include <onlp/led.h>

/**
 * Init
 */
typedef int (*onlp_ledi_init_f)(void);

/**
 * Info_get
 */
typedef int (*onlp_ledi_info_get_f)(onlp_oid_t lid, onlp_led_info_t* rv);

/**
 * Turn an led on or off with a given mode
 */
typedef int (*onlp_ledi_set_f)(onlp_oid_t lid, int on_or_off, int mode);

/**
 * ioctl
 */
typedef int (*onlp_ledi_ioctl_f)(onlp_oid_t lid, va_list vargs);


/**
 * LEDI vector structure
 */
typedef struct onlp_ledi_vectors_s {
    onlp_ledi_init_f init;
    onlp_ledi_info_get_f info_get;
    onlp_ledi_set_f set;
    onlp_ledi_ioctl_f ioctl;
} onlp_ledi_vectors_t;


/**
 * This is the interface implementation vector create function.
 * The platform provider must implement a single entry point
 * called 'onlp_ledi_vectors_create' with the following signature:
 */
typedef int (*onlp_ledi_vectors_create_f)(onlp_ledi_vectors_t* rv);

int onlp_ledi_vectors_create(onlp_ledi_vectors_t* rv);


#endif /* __ONLP_LED_H__ */
