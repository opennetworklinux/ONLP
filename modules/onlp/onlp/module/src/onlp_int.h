/**************************************************************************//**
 *
 * onlp Internal Header
 *
 *****************************************************************************/
#ifndef __ONLP_INT_H__
#define __ONLP_INT_H__

#include <onlp/onlp_config.h>
#include <IOF/iof.h>
#include <onlp/oids.h>

/** Default IOF initializations for dump() and show() routines */
void onlp_oid_show_iof_init_default(iof_t* iof, aim_pvs_t* pvs);
void onlp_oid_dump_iof_init_default(iof_t* iof, aim_pvs_t* pvs);

/** Default error message when the status of an OID cannot be retreived */
void onlp_oid_info_get_error(iof_t* iof, int error);

/** Standardize floating point numbers to tenths only. */
float onlp_float_normal(float f);
int onlp_float_tenths(float f);

/** Standard OID description output */
void onlp_oid_show_description(iof_t* iof, onlp_oid_hdr_t* hdr);
/** Standard message when an OID is missing. */
void onlp_oid_show_state_missing(iof_t* iof);

#endif /* __ONLP_INT_H__ */
