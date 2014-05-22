/**************************************************************************//**
 *
 *
 *
 *****************************************************************************/
#include <onlp_platform_defaults/onlp_platform_defaults_config.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <AIM/aim.h>

int aim_main(int argc, char* argv[])
{
    printf("onlp_platform_defaults Utest Is Empty\n");
    onlp_platform_defaults_config_show(&aim_pvs_stdout);
    return 0;
}

