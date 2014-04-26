/************************************************************
 *
 * Platform System Information
 *
 ***********************************************************/
#ifndef __ONLP_SYS_H__
#define __ONLP_SYS_H__

#include <onlp/onlp_config.h>
#include <onlp/onlp.h>
#include <onlplib/onie.h>
#include <onlp/oids.h>

typedef struct onlp_sys_info_s {
    /** OID Header */
    onlp_oid_hdr_t hdr;

    /* System Information */
    onlp_onie_info_t onie_info;

} onlp_sys_info_t;


/**
 * @brief Initialize the System API
 */
int onlp_sys_init(void);

/**
 * @brief Get the system information structure.
 * @param rv [out] Receives the system information.
 */
int onlp_sys_info_get(onlp_sys_info_t* rv);

/**
 * @brief Free a system information structure.
 */
void onlp_sys_info_free(onlp_sys_info_t* info);

/**
 * @brief Show the current information about the given sys id.
 * @param id The SYS OID.
 * @param pvs The output pvs.
 * @param flags The output flags.
 */
void onlp_sys_show(onlp_oid_t id, aim_pvs_t* pvs, uint32_t flags);

#endif /* __ONLP_SYS_H_ */
