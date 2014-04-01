/**************************************************************************//**
 *
 *
 *
 *****************************************************************************/
#include <onlplib/onlplib_config.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <AIM/aim.h>

int aim_main(int argc, char* argv[])
{
    printf("onlplib Utest Is Empty\n");
    onlplib_config_show(&aim_pvs_stdout);
    return 0;
}

