/************************************************************
 * <bsn.cl v=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 * Common mmap() platform support.
 *
 ***********************************************************/
#ifndef __ONLP_MMAP_H__
#define __ONLP_MMAP_H__

#include <onlplib/onlplib_config.h>
#include <unistd.h>
#include <sys/mman.h>

/**
 * @brief Map a physical address range.
 * @param addr The physical
 * @param size The size of the region to map.
 * @param name The name of the memory region for debugging/logging purposes.
 */
void* onlp_mmap(off_t pa, uint32_t size, const char* name);





#endif /* __ONLP_MMAP_H__ */
