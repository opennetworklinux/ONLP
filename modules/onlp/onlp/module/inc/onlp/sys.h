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

    /* System Information */
    onlp_onie_info_t onie_info;

    /**
     * Top-level OIDs.
     * These do not necessarily represent all system OIDs, only
     * the root OIDs (objects with no parent OIDS).
     */
    onlp_oid_table_t oid_table;

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

#endif /* __ONLP_SYS_H_ */
