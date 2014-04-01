/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 * ONLP Platform Object Identifiers.
 *
 ***********************************************************/
#ifndef __ONLP_OID_H__
#define __ONLP_OID_H__

#include <onlp/onlp_config.h>

#include <stdint.h>
#include <AIM/aim_pvs.h>

/**
 * System peripherals are identified by a 32bit OID.
 *
 * The First byte is the object-class identifier:
 *    Thermal sensor object
 *    Fan object
 *    PSU object
 *    LED object
 *    MODULE object
 *    etc..
 * The remaining bytes are the object id.
 */

typedef uint32_t onlp_oid_t;

/* <auto.start.enum(onlp_oid_type).define> */
/** onlp_oid_type */
typedef enum onlp_oid_type_e {
    ONLP_OID_TYPE_THERMAL = 1,
    ONLP_OID_TYPE_FAN = 2,
    ONLP_OID_TYPE_PSU = 3,
    ONLP_OID_TYPE_LED = 4,
    ONLP_OID_TYPE_MODULE = 5,
} onlp_oid_type_t;
/* <auto.end.enum(onlp_oid_type).define> */

/**
 * Get the or set the type of an OID
 */
#define ONLP_OID_TYPE_GET(_id) ( ( (_id) >> 24) )
#define ONLP_OID_TYPE_CREATE(_type, _id) ( ( (_type) << 24) | (_id))
#define ONLP_OID_IS_TYPE(_type,_id) (ONLP_OID_TYPE_GET((_id)) == _type)
#define ONLP_OID_ID_GET(_id) (_id & 0xFFFFFF)
#define ONLP_THERMAL_ID_CREATE(_id) ONLP_OID_TYPE_CREATE(ONLP_OID_TYPE_THERMAL, _id)
#define ONLP_FAN_ID_CREATE(_id)     ONLP_OID_TYPE_CREATE(ONLP_OID_TYPE_FAN, _id)
#define ONLP_PSU_ID_CREATE(_id)     ONLP_OID_TYPE_CREATE(ONLP_OID_TYPE_PSU, _id)
#define ONLP_LED_ID_CREATE(_id)     ONLP_OID_TYPE_CREATE(ONLP_OID_TYPE_LED, _id)
#define ONLP_MODULE_ID_CREATE(_id)  ONLP_OID_TYPE_CREATE(ONLP_OID_TYPE_MODULE, _id)

#define ONLP_OID_IS_THERMAL(_id) ONLP_OID_IS_TYPE(ONLP_OID_TYPE_THERMAL,_id)
#define ONLP_OID_IS_FAN(_id)     ONLP_OID_IS_TYPE(ONLP_OID_TYPE_FAN,_id)
#define ONLP_OID_IS_PSU(_id)     ONLP_OID_IS_TYPE(ONLP_OID_TYPE_PSU,_id)
#define ONLP_OID_IS_LED(_id)     ONLP_OID_IS_TYPE(ONLP_OID_TYPE_LED,_id)
#define ONLP_OID_IS_MODULE(_id)  ONLP_OID_IS_TYPE(ONLP_OID_TYPE_MODULE,_id)

/**
 * All OIDs have user-level description strings:
 */
#define ONLP_OID_DESC_SIZE 128

typedef char onlp_oid_desc_t[ONLP_OID_DESC_SIZE];

/* fixme */
typedef onlp_oid_t onlp_oid_table_t[32];


/**
 * This macro can be used to construct your OID hdr tables
 */
#define ONLP_OID_THERMAL_ENTRY(_id, _desc, _parent_type, _parent_id) \
    { ONLP_THERMAL_ID_CREATE(_id), _desc, ONLP_OID_TYPE_CREATE(_parent_type, _parent_id) }

/**
 * All OID objects contain this header as the first member.
 */
typedef struct onlp_oid_hdr_s {
    /** The OID */
    onlp_oid_t id;
    /** The description of this object. */
    onlp_oid_desc_t description;
    /** The parent OID of this object. */
    onlp_oid_t pid;
} onlp_oid_hdr_t;




#define ONLP_OID_SHOW_F_RECURSE 0x1
#define ONLP_OID_SHOW_F_EVEN_IF_ABSENT 0x2

/**
 * All OIDs can be dumped.
 */
void onlp_oid_show(onlp_oid_t oid, aim_pvs_t* pvs, uint32_t flags);
void onlp_oids_show(onlp_oid_t* oids, int count, aim_pvs_t* pvs,
                    uint32_t flags);

#endif /* __ONLP_OID_H__ */
