/************************************************************
 *
 * Power Supply Management.
 *
 ***********************************************************/
#ifndef __ONLP_PSU_H__
#define __ONLP_PSU_H__

typedef struct onlp_psu_info_t {

    /* PSU Identifier */
    onlp_oid_t pid;

    onlp_oid_desc_t description;

    /* PSU is present */
    int present;

    /* input voltage */
    uint32_t input_voltage;

    /* Output voltage */
    uint32_t output_voltage;

    /* Current */
    uint32_t current;

    /* Status */
    uint32_t status;

    /* Capabilities */
    uint32_t caps;

    /* child oids */
    onlp_oid_table_t oid_table;

} onlp_psu_info_t;

int onlp_psu_init(void);
int onlp_psu_info_get(int pid, onlp_psu_info_t* rv);


#endif /* __ONLP_PSU_H__ */
