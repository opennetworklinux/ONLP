/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 *
 *
 ***********************************************************/
#include <onlp/onlp.h>
#include <onlp/oids.h>
#include <unistd.h>

int
onlpdump_main(int argc, char* argv[])
{
    int show = 0;
    uint32_t showflags = 0;
    int help = 0;
    int c;
    int rv = -1;

    while( (c = getopt(argc, argv, "srehd")) != -1) {
        switch(c)
            {
            case 's': show=1; break;
            case 'r': show=1; showflags |= ONLP_OID_SHOW_F_RECURSE; break;
            case 'e': show=1; showflags |= ONLP_OID_SHOW_F_EXTENDED; break;
            case 'd': show=0; break;
            case 'h': help=1; rv = 0; break;
            default: help=1; rv = 1; break;
            }
    }

    if(help) {
        printf("Usage: %s [OPTIONS]\n", argv[0]);
        printf("  -d   Use dump(). This is the default.\n");
        printf("  -s   Use show() instead of dump().\n");
        printf("  -r   Recursive show(). Implies -s\n");
        printf("  -e   Extended show(). Implies -s\n");
        return rv;
    }

    onlp_init();

    if(show == 0) {
        /* Default to full dump */
        onlp_platform_dump(&aim_pvs_stdout,
                           ONLP_OID_DUMP_F_RECURSE | ONLP_OID_DUMP_F_EVEN_IF_ABSENT);
    }
    else {
        onlp_platform_show(&aim_pvs_stdout,
                           showflags);
    }
    return 0;
}
