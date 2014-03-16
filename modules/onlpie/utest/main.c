/**************************************************************************//**
 *
 *
 *
 *****************************************************************************/
#include <onlpie/onlpie_config.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <AIM/aim.h>

int aim_main(int argc, char* argv[])
{
    printf("onlpie Utest Is Empty\n");
    onlpie_config_show(&aim_pvs_stdout);
    return 0;
}

