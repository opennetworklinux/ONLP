/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 * Thermal Sensor Platform Implementation.
 *
 ***********************************************************/
#ifndef __ONLP_THERMALI_H__
#define __ONLP_THERMALI_H__

#include <onlp/thermal.h>

/**
 * @brief Initialize the thermal subsystem.
 */
int onlp_thermali_init(void);


/**
 * @brief Get the information for the given thermal OID.
 * @param id The Thermal OID
 * @param rv [out] Receives the thermal information.
 */
int onlp_thermali_info_get(onlp_oid_t id, onlp_thermal_info_t* rv);


#endif /* __ONLP_THERMALI_H__ */
