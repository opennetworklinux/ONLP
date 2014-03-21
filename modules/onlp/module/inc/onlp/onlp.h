/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 *
 *
 ***********************************************************/
#ifndef __ONLP_ONLP_H__
#define __ONLP_ONLP_H__

#include <onlp/onlp_config.h>

/* <auto.start.enum(onlp_status).define> */
/** onlp_status */
typedef enum onlp_status_e {
    ONLP_STATUS_OK = 0,
    ONLP_STATUS_E_UNSUPPORTED = -1,
    ONLP_STATUS_E_MISSING = -2,
    ONLP_STATUS_E_INVALID = -3,
    ONLP_STATUS_E_INTERNAL = -4,
} onlp_status_t;
/* <auto.end.enum(onlp_status).define> */



/**
 * @brief Initialize all subsystems.
 */
int onlp_init(void);


/**
 * @brief Dump the current platform data.
 * @param pvs The output pvs
 */

void onlp_platform_dump(aim_pvs_t* pvs);

#endif /* __ONLP_ONLP_H__ */
