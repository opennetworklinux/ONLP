/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 *
 *
 ***********************************************************/
#include "onlp_json.h"
#include "onlp_log.h"
#include <onlp/onlp.h>

static cJSON* root__ = NULL;
static char* file__ = NULL;

void
onlp_json_init(const char* fname)
{
    int rv;
    onlp_json_denit();

    rv = cjson_util_parse_file(fname, &root__);
    if(rv < 0 || root__ == NULL) {
        root__ = cJSON_Parse("{}");
    }
    else {
        file__ = aim_strdup(fname);
    }

}

cJSON*
onlp_json_get(int reload)
{
    if(reload) {
        onlp_json_init(file__);
    }
    return root__;
}

void
onlp_json_denit(void)
{
    if(root__) {
        cJSON_Delete(root__);
        root__ = NULL;
    }
    if(file__) {
        aim_free(file__);
        file__ = NULL;
    }
}
