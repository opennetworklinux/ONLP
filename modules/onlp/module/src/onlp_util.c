/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 *
 *
 ***********************************************************/
#include <onlp/onlp_config.h>
#include <onlp/onlp.h>
#include "onlp_int.h"

/**
 * The OID dump() and show() routines
 * need a default IOF.
 */
void
onlp_oid_dump_iof_init_default(iof_t* iof, aim_pvs_t* pvs)
{
    if(iof_init(iof, pvs) == 0) {
        /* Default settings */
        iof->indent_factor=4;
        iof->level=1;
        iof->indent_terminator="";
    }
}
void
onlp_oid_show_iof_init_default(iof_t* iof, aim_pvs_t* pvs)
{
    if(iof_init(iof, pvs) == 0) {
        /* Default settings */
        iof->indent_factor=2;
        iof->level=1;
        iof->indent_terminator="";
        iof->pop_string = NULL;
        iof->push_string = "";
    }
}

void
onlp_oid_info_get_error(iof_t* iof, int error)
{
    iof_iprintf(iof, "Error retrieving status: %{onlp_status}", error);
}
void
onlp_oid_show_description(iof_t* iof, onlp_oid_hdr_t* hdr)
{
    iof_iprintf(iof, "Description: %s", hdr->description);
}

void
onlp_oid_show_state_missing(iof_t* iof)
{
    iof_iprintf(iof, "State: Missing");
}

int
onlp_float_tenths(float f)
{
    f*=10;
    return (int) f;
}

float
onlp_float_normal(float f)
{
    int r = onlp_float_tenths(f);
    float rv = (float)r;
    return rv/10;
}
