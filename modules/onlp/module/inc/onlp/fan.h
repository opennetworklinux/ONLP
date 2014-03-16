/************************************************************
 *
 * Fan Control
 *
 ************************************************************/
#ifndef __ONLP_FAN_H__
#define __ONLP_FAN_H__


typedef struct onlp_fan_info_s {

    /** Fan identifier */
    int fid;

    onlp_oid_desc_t description;

    /* Capabilities */
    uint32_t capabilities;

    /* Status */
    uint32_t status;

    /* The fan is present. */
    int present;

    /* Current fan speed, in RPM. */
    uint32_t rpm;

    /* oids associated with this fan */
    onlp_oid_table_t oid_table;

} onlp_fan_info_t;

int onlp_fan_init(void);
int onlp_fan_info_get(int fid, onlp_fan_info_t* rv);
int onlp_fan_speed_set(int fid, uint32_t rpm);

#endif /* __ONLP_FAN_H__ */

