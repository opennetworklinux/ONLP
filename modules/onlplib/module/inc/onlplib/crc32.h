/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 * CRC32 Calculations
 *
 ***********************************************************/
#ifndef __ONLP_CRC32_H__
#define __ONLP_CRC32_H__

#include <stdint.h>

/**
 * @brief Calculate CRC32 on the given data buffer.
 * @param crc CRC start
 * @param buf The data buffer
 * @param size The size of the data buffer.
 * @returns The CRC32 value.
 */

uint32_t onlp_crc32(uint32_t crc, const void *buf, int size);

#endif /* __ONLP_CRC32_H__ */
