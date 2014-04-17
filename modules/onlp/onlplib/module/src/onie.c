/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 * ONIE System Board Information decoding.
 *
 * See:
 * https://github.com/onie/onie/blob/master/docs/design-spec/hw_requirements.rst
 *
 * This code derived from the feature-sys-eeprom-tlv.patch in the ONIE
 * distribution.
 *
 ***********************************************************/

#include <onlplib/onie.h>
#include <onlplib/crc32.h>

#include <AIM/aim_memory.h>
#include <AIM/aim_string.h>
#include <AIM/aim_printf.h>

#include <arpa/inet.h>

#include "onlplib_log.h"

/**
 * Header Field Constants
 */
#define TLV_INFO_ID_STRING      "TlvInfo"
#define TLV_INFO_VERSION        0x01
#define TLV_INFO_MAX_LEN        2048
#define TLV_TOTAL_LEN_MAX       (TLV_INFO_MAX_LEN - sizeof(tlvinfo_header_t))

/**
 * Validate checksum
 */
static int checksum_validate__(const uint8_t *data);


/**
 * ONIE TLV EEPROM Header
 */
typedef struct __attribute__ ((__packed__)) tlvinfo_header_s {
    char        signature[8];       /* 0x00 - 0x07 EEPROM Tag "TlvInfo" */
    uint8_t     version;            /* 0x08        Structure version    */
    uint16_t    totallen;           /* 0x09 - 0x0A Length of all data which follows */
} tlvinfo_header_t;

/**
 * ONIE TLV Entry
 */
typedef struct __attribute__ ((__packed__)) tlvinfo_tlv_s {
    uint8_t  type;
    uint8_t  length;
    uint8_t  value[0];
} tlvinfo_tlv_t;


/**
 *  The TLV Types.
 */
#define TLV_CODE_PRODUCT_NAME   0x21
#define TLV_CODE_PART_NUMBER    0x22
#define TLV_CODE_SERIAL_NUMBER  0x23
#define TLV_CODE_MAC_BASE       0x24
#define TLV_CODE_MANUF_DATE     0x25
#define TLV_CODE_DEVICE_VERSION 0x26
#define TLV_CODE_LABEL_REVISION 0x27
#define TLV_CODE_PLATFORM_NAME  0x28
#define TLV_CODE_ONIE_VERSION   0x29
#define TLV_CODE_MAC_SIZE       0x2A
#define TLV_CODE_MANUF_NAME     0x2B
#define TLV_CODE_MANUF_COUNTRY  0x2C
#define TLV_CODE_VENDOR_NAME    0x2D
#define TLV_CODE_DIAG_VERSION   0x2E
#define TLV_CODE_VENDOR_EXT     0xFD
#define TLV_CODE_CRC_32         0xFE


static void
decode_tlv__(onlp_onie_info_t* info, tlvinfo_tlv_t * tlv)
{
    switch (tlv->type)
        {
            /* String TLVs */
#define CASE_TLV_STRING(_info, _member, _code, _tlv)                    \
            case TLV_CODE_##_code :                                     \
                {                                                       \
                    if(_info -> _member) {                              \
                        aim_free((void*) _info -> _member);             \
                    }                                                   \
                    _info -> _member = aim_zmalloc(_tlv->length + 1);   \
                    memcpy((void*) _info -> _member, _tlv->value, _tlv->length); \
                    break;                                              \
                }

            CASE_TLV_STRING(info, product_name, PRODUCT_NAME, tlv);
            CASE_TLV_STRING(info, part_number, PART_NUMBER, tlv);
            CASE_TLV_STRING(info, serial_number, SERIAL_NUMBER, tlv);
            CASE_TLV_STRING(info, manufacture_date, MANUF_DATE, tlv);
            CASE_TLV_STRING(info, label_revision, LABEL_REVISION, tlv);
            CASE_TLV_STRING(info, platform_name, PLATFORM_NAME, tlv);
            CASE_TLV_STRING(info, onie_version, ONIE_VERSION, tlv);
            CASE_TLV_STRING(info, manufacturer, MANUF_NAME, tlv);
            CASE_TLV_STRING(info, country_code, MANUF_COUNTRY, tlv);
            CASE_TLV_STRING(info, vendor, VENDOR_NAME, tlv);
            CASE_TLV_STRING(info, diag_version, DIAG_VERSION, tlv);

        case TLV_CODE_MAC_BASE:
            memcpy(info->mac, tlv->value, 6);
            break;

        case TLV_CODE_DEVICE_VERSION:
            info->device_version = tlv->value[0];
            break;

        case TLV_CODE_MAC_SIZE:
            info->mac_range = (tlv->value[0] << 8) | tlv->value[1];
            break;

        case TLV_CODE_VENDOR_EXT:
            AIM_LOG_WARN("ONIE data contains a vendor extension (ignored)");
            break;

        case TLV_CODE_CRC_32:
            info->crc =
                (tlv->value[0] << 24) |
                (tlv->value[1] << 16) |
                (tlv->value[2] <<  8) |
                (tlv->value[3]);
            break;

        default:
            AIM_LOG_WARN("ONIE data contains an unrecognized TLV code: 0x%.2x (ignored)", tlv->type);
            break;
        }
}

/**
 *  is_valid_tlvinfo_header
 *
 *  Perform sanity checks on the first 11 bytes of the TlvInfo EEPROM
 *  data pointed to by the parameter:
 *      1. First 8 bytes contain null-terminated ASCII string "TlvInfo"
 *      2. Version byte is 1
 *      3. Total length bytes contain value which is less than or equal
 *         to the allowed maximum (2048-11)
 *
 */
static inline int is_valid_tlvinfo_header__(tlvinfo_header_t *hdr)
{
    return( (strcmp(hdr->signature, TLV_INFO_ID_STRING) == 0) &&
            (hdr->version == TLV_INFO_VERSION) &&
            (ntohs(hdr->totallen) <= TLV_TOTAL_LEN_MAX) );
}


/**
 *  is_valid_tlv
 *
 *  Perform basic sanity checks on a TLV field. The TLV is pointed to
 *  by the parameter provided.
 *      1. The type code is not reserved (0x00 or 0xFF)
 */
static inline int is_valid_tlv__(tlvinfo_tlv_t *tlv)
{
       return( (tlv->type != 0x00) &&
               (tlv->type != 0xFF) );

}


int
onlp_onie_decode(onlp_onie_info_t* rv, const uint8_t* data, int size)
{
    int tlv_end;
    int curr_tlv;
    tlvinfo_header_t* data_hdr = (tlvinfo_header_t *) data;
    tlvinfo_tlv_t* data_tlv;

    if(rv == NULL || data == NULL || (size && size < sizeof(*data_hdr))) {
        return -1;
    }

    memset(rv, 0, sizeof(*rv));

    if ( !is_valid_tlvinfo_header__(data_hdr) ) {
        AIM_LOG_ERROR("ONIE data is not in TlvInfo format.");
        return -1;
    }

    rv->_hdr_id_string = aim_strdup(data_hdr->signature);
    rv->_hdr_version = data_hdr->version;
    rv->_hdr_length = ntohs(data_hdr->totallen);

    /* We only parse TLV Header Version 1 */
    if(rv->_hdr_version != 1) {
        AIM_LOG_ERROR("ONIE data header version %d id string %s is not supported.", rv->_hdr_version, rv->_hdr_id_string);
        return -1;
    }

    /* Validate CRC checksum before attempting to parse */
    if(checksum_validate__(data) != 0) {
        /* Error already logged */
        return -1;
    }


    curr_tlv = sizeof(tlvinfo_header_t);
    tlv_end  = sizeof(tlvinfo_header_t) + ntohs(data_hdr->totallen);
    while (curr_tlv < tlv_end) {
        data_tlv = (tlvinfo_tlv_t *) &data[curr_tlv];
        if (!is_valid_tlv__(data_tlv)) {
            AIM_LOG_ERROR("ONIE data invalid TLV field starting at offset %d\n", curr_tlv);
            return -1;
        }
        decode_tlv__(rv, data_tlv);
        curr_tlv += sizeof(tlvinfo_tlv_t) + data_tlv->length;
    }

    return 0;
}

/**
 *  Validate the checksum in the provided TlvInfo EEPROM data. First,
 *  verify that the TlvInfo header is valid, then make sure the last
 *  TLV is a CRC-32 TLV. Then calculate the CRC over the EEPROM data
 *  and compare it to the value stored in the EEPROM CRC-32 TLV.
 */
static int
checksum_validate__(const uint8_t *data)
{
    tlvinfo_header_t* data_hdr = (tlvinfo_header_t *) data;
    tlvinfo_tlv_t* data_crc;
    unsigned int calc_crc;
    unsigned int stored_crc;

    // Is the eeprom header valid?
    if (!is_valid_tlvinfo_header__(data_hdr)) {
        return 0;
    }

    // Is the last TLV a CRC?
    data_crc = (tlvinfo_tlv_t *) &data[sizeof(tlvinfo_header_t) +
                                       ntohs(data_hdr->totallen) - (sizeof(tlvinfo_tlv_t) + 4)];

    if ((data_crc->type != TLV_CODE_CRC_32) || (data_crc->length != 4)) {
        AIM_LOG_ERROR("ONIE CRC TLV is invalid.");
        return 0;
    }

    // Calculate the checksum
    calc_crc = onlp_crc32(0, (void *)data,
                          sizeof(tlvinfo_header_t) + ntohs(data_hdr->totallen) - 4);
    stored_crc = (data_crc->value[0] << 24) |
        (data_crc->value[1] << 16) |
        (data_crc->value[2] <<  8) |
        data_crc->value[3];

    if(calc_crc != stored_crc)  {
        AIM_LOG_ERROR("ONIE data crc error: expected 0x%.8x calculated 0x%.8x",
                      stored_crc, calc_crc);
        return -1;
    }
    return 0;
}

void
onlp_onie_info_free(onlp_onie_info_t* info)
{
    if(info) {
        aim_free(info->product_name);
        aim_free(info->part_number);
        aim_free(info->serial_number);
        aim_free(info->manufacture_date);
        aim_free(info->label_revision);
        aim_free(info->platform_name);
        aim_free(info->onie_version);
        aim_free(info->manufacturer);
        aim_free(info->country_code);
        aim_free(info->vendor);
        aim_free(info->diag_version);
        aim_free(info->service_tag);
        aim_free(info->_hdr_id_string);
    }
}

void
onlp_onie_show(onlp_onie_info_t* info, aim_pvs_t* pvs, const char* indent)
{
    const char* i = indent ? indent : "";
    aim_printf(pvs, "%sProduct Name: %s\n", i, info->product_name);
    aim_printf(pvs, "%sPart Number: %s\n", i, info->part_number);
    aim_printf(pvs, "%sSerial Number: %s\n", i, info->serial_number);
    aim_printf(pvs, "%sMAC: %{mac}\n", i, info->mac);
    aim_printf(pvs, "%sMAC Range: %d\n", i, info->mac_range);
    aim_printf(pvs, "%sManufacturer: %s\n", i, info->device_version);
    aim_printf(pvs, "%sManufacture Date: %s\n", i, info->manufacture_date);
    aim_printf(pvs, "%sVendor: %s\n", i, info->vendor);
    aim_printf(pvs, "%sPlatform Name: %s\n", i, info->platform_name);
    aim_printf(pvs, "%sDevice Version: %s\n", i, info->device_version);
    aim_printf(pvs, "%sLabel Revision: %s\n", i, info->label_revision);
    aim_printf(pvs, "%sCountry Code: %s\n", i, info->country_code);
    aim_printf(pvs, "%sDiag Version: %s\n", i, info->diag_version);
    aim_printf(pvs, "%sService Tag: %s\n", i, info->service_tag);
    aim_printf(pvs, "%sONIE Version: %s\n", i, info->onie_version);
    aim_printf(pvs, "%sCRC: 0x%x\n", i, info->crc);
}

void
onlp_onie_show_json(onlp_onie_info_t* info, aim_pvs_t* pvs)
{
    aim_printf(pvs, "{\n");

#define STROUT(_name, _member)                                   \
    do {                                                         \
        aim_printf(pvs, "    \"%s\" : ", #_name);                 \
        if(info-> _member) {                                     \
            aim_printf(pvs, "\"%s\",\n", info->_member);         \
        }                                                        \
        else {                                                   \
            aim_printf(pvs, "null,\n");                          \
        }                                                        \
    } while(0)

    STROUT(Product Name, product_name);
    STROUT(Part Number, part_number);
    STROUT(Serial Number, serial_number);
    aim_printf(pvs, "    \"MAC\": \"%{mac}\", ", info->mac);
    aim_printf(pvs, "    \"MAC Range\": %d,\n", info->mac_range);
    STROUT(Manufacture Date,manufacture_date);
    STROUT(Vendor,vendor);
    STROUT(Platform Name,platform_name);
    STROUT(Device Version,device_version);
    STROUT(Label Revision,label_revision);
    STROUT(Country Code,country_code);
    STROUT(Diag Version,diag_version);
    STROUT(Service Tag,service_tag);
    STROUT(ONIE Version,onie_version);
    aim_printf(pvs, "    \"CRC\": \"0x%x\"\n", info->crc);
    aim_printf(pvs, "}\n");
}


