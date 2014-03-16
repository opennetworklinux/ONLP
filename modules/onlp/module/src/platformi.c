/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 * Platform Implementation Vector Initializations.
 *
 ***********************************************************/
#include <onlp/onlp_config.h>
#include <onlp/platformi/sfpi.h>
#include "onlp_log.h"

#if ONLP_CONFIG_DYNAMIC_PLATFORM_LOADING == 1

#include <onlp/lib/dload.h>

/**
 * Generic load and create for all platformi components.
 */
typedef int (*onlp_generic_vectors_create_f)(void* vcs);

static int
onlp_dload_vectors_create(const char* name, void* vcs, int vcs_size,
                          int required)
{
    int rv;
    onlp_generic_vectors_create_f vcf = NULL;

    memset(vcs, 0, vcs_size);
    rv = onlp_dload(name, (onlp_dload_vector_f*)&vcf, required);
    if(rv == 0) {
        rv = vcf(vcs);
    }
    return rv;
}

int
onlp_sfpi_vectors_create(onlp_sfpi_vectors_t* rv)
{
    return onlp_dload_vectors_create(ONLP_SFPI_VECTORS_CREATE, rv,
                                     sizeof(*rv), 0);
}

#endif /* ONLP_CONFIG_DYNAMIC_PLATFORM_LOADING */

