/************************************************************
 * <bsn.cl fy=2014 v=onl>
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
 * @brief Initialize the SFP driver.
 */
typedef int (*onlp_sfpi_init_f)(void);

/**
 * @brief Get the bitmap of SFP-capable port numbers.
 * @param bmap [out] Receives the bitmap.
 */
typedef int (*onlp_sfpi_bitmap_get_f)(onlp_sfp_bitmap_t* bmap);

/**
 * @brief Determine if an SFP is present.
 * @param port The port number.
 * @returns 1 if present
 * @returns 0 if absent
 * @returns An error condition.
 */
typedef int (*onlp_sfpi_is_present_f)(int port);

/**
 * @brief Read the SFP EEPROM.
 * @param port The port number.
 * @param data Receives the SFP data.
 */
typedef int (*onlp_sfpi_eeprom_read_f)(int port, uint8_t data[256]);

/**
 * @brief Enable or disable the given SFP.
 * @param port The port number.
 * @param enable Enable the SFP is 1, Disable the SFP if 0
 */
typedef int (*onlp_sfpi_enable_set_f)(int port, int enable);

/**
 * @brief Get the current enable state.
 * @param port The port number.
 * @param enable [out] Receives the enable state.
 */
typedef int (*onlp_sfpi_enable_get_f)(int port, int* enable);

/**
 * @brief Perform any actions required after an SFP is inserted.
 * @param port The port number.
 * @param eeprom The eeprom data for the new SFP.
 * @notes This vector is optional.
 */
typedef int (*onlp_sfpi_post_insert_f)(int port, uint8_t eeprom[256]);

/**
 * @brief Get the current status flags for an SFP.
 * @param port The port number.
 * @param status [out] Receives the status flags.
 * @notes See onlp_sfp_status_t
 */
typedef int (*onlp_sfpi_status_get_f)(int port, uint32_t* status);

/**
 * @brief Deinitialize the SFP driver.
 */
typedef int (*onlp_sfpi_denit_f)(void);

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
 * @notes This is vector is optional.
 */
typedef int (*onlp_sfpi_debug_f)(int port, aim_pvs_t* pvs);

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
 * @notes This vector is optional.
 */
typedef int (*onlp_sfpi_ioctl_f)(int port, va_list vargs);


/**
 * This is the SFPI vector structure
 */
typedef struct onlp_sfpi_vectors_s {

    /** init */
    onlp_sfpi_init_f init;
    /** denit */
    onlp_sfpi_denit_f denit;
    /** bitmap_get */
    onlp_sfpi_bitmap_get_f bitmap_get;
    /** is_present */
    onlp_sfpi_is_present_f is_present;
    /** eeprom */
    onlp_sfpi_eeprom_read_f eeprom;
    /** enable_set */
    onlp_sfpi_enable_set_f enable_set;
    /** enable_get */
    onlp_sfpi_enable_get_f enable_get;
    /** status_get */
    onlp_sfpi_status_get_f status_get;
    /** port_insert */
    onlp_sfpi_post_insert_f post_insert;
    /** ioctl */
    onlp_sfpi_ioctl_f      ioctl;
    /** debug */
    onlp_sfpi_debug_f      debug;

} onlp_sfpi_vectors_t;


#if ONLP_CONFIG_DYNAMIC_PLATFORM_LOADING == 1

/**
 * The vector structure create entry point will be looked up
 * dynamically.
 */
typedef int (*onlp_sfpi_vectors_create_f)(onlp_sfpi_vectors_t* rv);
#define ONLP_SFPI_VECTORS_CREATE "onlp_sfpi_vectors_create"

#endif


int onlp_sfpi_vectors_create(onlp_sfpi_vectors_t* rv);










#endif /* __ONLP_SFPI_H__ */
