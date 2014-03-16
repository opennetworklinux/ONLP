/************************************************************
 *
 * ONLP System Interface Implementation
 *
 ***********************************************************/
#ifndef __ONLP_SYSI_H__
#define __ONLP_SYSI_H__

#include <onlp/sys.h>

/**
 * These function vectors must be provided.
 */

/* Initialize sys interface */
typedef int (*onlp_sysi_init_f)(void);

/**
 * The physical base address of the ONIE eeprom data.
 *
 * IF you provide this address, the common system layer
 * will map the address and decode the data for you.
 *
 * This should be the most common option.
 *
 * If you cannot provide the physical address of the system eeprom
 * see the next vector below.
 */
typedef int (*onlp_sysi_onie_data_phys_addr_get_f)(void** physaddr);

/**
 * Return the raw contents of the ONIE system eeprom.
 * You only need to do this if the device cannot be mapped directly
 * from the physical base address.
 */

typedef int (*onlp_sysi_onie_data_get_f)(const char** data);

/**
 * This function will be called when the upper-layer is done with
 * your onie data.
 */
typedef void (*onlp_sysi_onie_data_free_f)(const char* data);

/**
 * This function returns the root oid list for the platform:
 */
typedef int (*onlp_sysi_oids_get_f)(onlp_oid_t* table, int max);


/**
 * This function provides a generic ioctl hook.
 */
typedef int (*onlp_sysi_ioctl_f)(int id, va_list vargs);


/**
 * This is the SYSI vector table.
 */
typedef struct onlp_sysi_vectors_s {

    onlp_sysi_init_f init;
    onlp_sysi_onie_data_phys_addr_get_f onie_data_phys_addr_get;
    onlp_sysi_onie_data_get_f onie_data_get;
    onlp_sysi_onie_data_free_f onie_data_free;
    onlp_sysi_oids_get_f oids_get;
    onlp_sysi_ioctl_f ioctl;

} onlp_sysi_vectors_t;


/**
 * This is the interface implementation vector create function.
 * The platform provider must implement a single entry point
 * called 'onlp_sysi_vectors_create' with the following signature:
 */
typedef int (*onlp_sysi_vectors_create_f)(onlp_sysi_vectors_t* rv);

int onlp_sysi_vectors_create(onlp_sysi_vectors_t* rv);



#endif /* __ONLP_SYSI_H__ */
