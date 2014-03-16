/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 * Common ONIE Infrastructure Support.
 *
 ***********************************************************/
#ifndef __ONLP_ONIE_H__
#define __ONLP_ONIE_H__

#include <stdint.h>
#include <AIM/aim_pvs.h>

/**
 * The ONIE specification defines the format of the system
 * eeprom and the available fields that may be described there.
 *
 * This structure contains the decoded fields for application
 * and platform use.
 */

typedef struct onlp_onie_info_s {

    char* product_name;
    char* part_number;
    char* serial_number;
    uint8_t     mac[6];
    char* manufacture_date;
    uint8_t     device_version;
    char* label_revision;
    char* platform_name;
    char* onie_version;
    uint16_t    mac_range;
    char* manufacturer;
    char* country_code;
    char* vendor;
    char* diag_version;
    char* service_tag;
    uint32_t    crc;



    /* Internal/debug */
    char* _hdr_id_string;
    uint8_t     _hdr_version;
    uint8_t     _hdr_length;
    uint8_t     _hdr_valid_crc;

} onlp_onie_info_t;


/**
 * Support for parsing ONIE eeprom data into the
 * ONIE information structure is provided for all platforms.
 */

int onlp_onie_decode(onlp_onie_info_t* rv, const uint8_t* data, int size);

/**
 * Free an ONIE info structure.
 */
void onlp_onie_info_free(onlp_onie_info_t* info);

/**
 * Show the contents of an ONIE info structure.
 */
void onlp_onie_show(onlp_onie_info_t* info, aim_pvs_t* pvs);


#endif /* __ONLP_ONIE_H__ */
