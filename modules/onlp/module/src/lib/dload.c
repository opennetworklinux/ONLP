/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 * Dynamic Platform Library Support
 *
 ***********************************************************/
#include <onlp/onlp_config.h>
#include <onlp/lib/dload.h>
#include "../onlp_log.h"

static int
onlp_dload__(const char* name, onlp_dload_vector_f* rv)
{
    /* TODO */
    *rv = NULL;
    return AIM_ERROR_NOT_FOUND;
}

int
onlp_dload(const char* name, onlp_dload_vector_f* rvf, int required)
{
    int rv = onlp_dload__(name, rvf);
    if(rv < 0) {
        if(rv == AIM_ERROR_NOT_FOUND) {
            if(required) {
                AIM_DIE("Required dload vector '%s' was not found in the platform libraries.",
                        name);
            }
            else {
                AIM_LOG_WARN("dload vector '%s' was not found in the platform libraries.");
            }
        }
        else {
            AIM_DIE("dload(%s) error: %d\n", name, rv);
        }
    }
    return rv;
}
