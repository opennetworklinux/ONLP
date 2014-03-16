/************************************************************
 * <bsn.cl v=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 *
 *
 ***********************************************************/
#include <onlp/lib/mmap.h>
#include "../onlp_log.h"
#include <unistd.h>
#include <sys/mman.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

void*
onlp_mmap(off_t pa, uint32_t size, const char* name)
{
    int msize = 0;
    int psize = getpagesize();

    msize = (((size / psize) + 1) * psize);

    int fd = open("/dev/mem", O_RDWR | O_SYNC);

    if(fd <= 0) {
        AIM_LOG_ERROR("open(/dev/mem) failed: %{errno}", errno);
        return NULL;
    }

    uint8_t* memory = mmap(NULL,
                           msize,
                           PROT_READ | PROT_WRITE,
                           MAP_SHARED,
                           fd,
                           pa);

    close(fd);

    if(memory == MAP_FAILED) {
        AIM_LOG_ERROR("mmap() pa=0x%llx size=%d name=%s failed: %{errno}",
                      pa, size, errno);
        return NULL;
    }
    return memory;
}

