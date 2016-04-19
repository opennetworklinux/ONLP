/**************************************************************************//**
 *
 *
 *
 *****************************************************************************/
#include <sff/sff_config.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <AIM/aim.h>
#include <sff/sff.h>
#include <sff/sff_db.h>

int
aim_main(int argc, char* argv[])
{
    int i;

    sff_db_entry_t* entries;
    sff_db_entry_t* p;
    int count;

    sff_db_get(&entries, &count);

    for(i = 0, p=entries; i < count; i++, p++) {
        int rv;
        sff_info_t info;

        aim_printf(&aim_pvs_stdout, "Verifying entry %d: %s:%s:%s...\n",
                   i,
                   p->info.vendor,
                   p->info.model,
                   p->info.serial);


        if( (rv=sff_info_init(&info, p->info.eeprom)) < 0) {
            AIM_DIE("index=%d sff_info_init=%d\n", i, rv);
        }
        if (!info.supported) {
            AIM_DIE("index=%d supported=0\n", i);
        }
        if(strcmp(info.vendor, p->info.vendor)) {
            AIM_DIE("index=%d vendor expected '%s' got '%s'",
                    i, p->info.vendor, info.vendor);
        }
        if(strcmp(info.model, p->info.model)) {
            AIM_DIE("index=%d model expected '%s' got '%s'",
                    i, p->info.model, info.model);
        }
        if(strcmp(info.serial, p->info.serial)) {
            AIM_DIE("index=%d serial expected '%s' got '%s'",
                    i, p->info.serial, info.serial);
        }
        if(info.sfp_type != p->info.sfp_type) {
            AIM_DIE("index=%d sfp_type expected '%{sff_sfp_type}' got '%{sff_sfp_type}'",
                    i, p->info.sfp_type, info.sfp_type);
        }
        if(strcmp(info.sfp_type_name, p->info.sfp_type_name)) {
            AIM_DIE("index=%d type_name expected '%s' got '%s'",
                    i, p->info.sfp_type, info.sfp_type);
        }
        if(info.module_type != p->info.module_type) {
            AIM_DIE("index=%d module_type expected '%{sff_module_type}' got '%{sff_module_type}'",
                    i, p->info.module_type, info.module_type);
        }
        if(info.media_type != p->info.media_type) {
            AIM_DIE("index=%d media_type expected '%{sff_media_type}' got '%{sff_media_type}'\n",
                    i, p->info.media_type, info.media_type);
        }
        if(strcmp(info.media_type_name, p->info.media_type_name)) {
            AIM_DIE("index=%d media_type_name expected '%s' got '%s'",
                    i, p->info.media_type_name, info.media_type_name);
        }
        if (info.caps != p->info.caps) {
            AIM_DIE("index=%d caps expected '%{sff_module_caps}' got '%{sff_module_caps}'",
                    i, p->info.caps, info.caps);
        }

        if(info.length != p->info.length) {
            AIM_DIE("index=%d length expected %d got %d",
                    i, p->info.length, info.length);
        }
        if(info.length == -1 && info.length_desc[0]) {
            AIM_DIE("index=%d length_desc expected '%s' got '%s'",
                    i, '\0', info.length_desc);
        }
        else if(info.length != -1) {
            char tmp[32];
            snprintf(tmp, sizeof(tmp), "%dm", info.length);
            if(strcmp(tmp, info.length_desc)) {
                AIM_DIE("index=%d length_desc expected '%s' got '%s'",
                        i, tmp, info.length_desc);
            }
        }

        aim_printf(&aim_pvs_stdout, "Verifying entry %d: %s:%s:%s...PASSED\n",
                   i,
                   p->info.vendor,
                   p->info.model,
                   p->info.serial);

    }
    return 0;
}

