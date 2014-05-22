/************************************************************
 *
 * Power Supply Management Implementation.
 *
 ***********************************************************/
#ifndef __ONLP_PSUI_H__
#define __ONLP_PSUI_H__

#include <onlp/psu.h>

/**
 * @brief Initialize the PSU subsystem.
 */
int onlp_psui_init(void);

/**
 * @brief Get the information structure for the given PSU
 * @param id The PSU OID
 * @param rv [out] Receives the PSU information.
 */
int onlp_psui_info_get(onlp_oid_t id, onlp_psu_info_t* rv);

/**
 * @brief Generic PSU ioctl
 * @param id The PSU OID
 * @param vargs The variable argument list for the ioctl call.
 */
int onlp_psui_ioctl(onlp_oid_t pid, va_list vargs);


#endif /* __ONLP_PSUI_H__ */
