/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 *
 *
 ***********************************************************/

#ifndef __ONLP_JSON_H__
#define __ONLP_JSON_H__

#include <onlp/onlp_config.h>
#include "onlp_int.h"
#include <cjson_util/cjson_util.h>

/**
 * @brief Initialize the JSON configuration data.
 * @param fname JSON configuration filename.
 */
void onlp_json_init(const char* fname);

/**
 * @brief Get the JSON configuration root.
 * @param reload Option to reload the config file first.
 */
cJSON* onlp_json_get(int reload);

void onlp_json_denit(void);


#endif /* __ONLP_JSON_H__ */
