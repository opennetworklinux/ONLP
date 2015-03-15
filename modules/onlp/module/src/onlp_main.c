/************************************************************
 * <bsn.cl fy=2014 v=onl>
 *
 *        Copyright 2014, 2015 Big Switch Networks, Inc.
 *
 * Licensed under the Eclipse Public License, Version 1.0 (the
 * "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at
 *
 *        http://www.eclipse.org/legal/epl-v10.html
 *
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
 * either express or implied. See the License for the specific
 * language governing permissions and limitations under the
 * License.
 *
 * </bsn.cl>
 ************************************************************
 *
 *
 *
 ***********************************************************/
#include <onlp/onlp.h>
#include <onlp/oids.h>
#include <unistd.h>
#include <onlp/sys.h>
#include <onlp/sfp.h>

static int
iterate_oids_callback__(onlp_oid_t oid, void* cookie)
{
    int type = ONLP_OID_TYPE_GET(oid);
    int id   = ONLP_OID_ID_GET(oid);

    static int thermal = 1;
    static int fan = 1;
    static int psu = 1;

    switch(type)
        {
        case ONLP_OID_TYPE_THERMAL:
            printf("thermal,Thermal %d,%d\n", id, thermal++);
            break;
        case ONLP_OID_TYPE_FAN:
            printf("fan,Fan %d,%d\n", id, fan++);
            break;
        case ONLP_OID_TYPE_PSU:
            printf("psu,PSU %d,%d\n", id, psu++);
            break;
        }
    return 0;
}


static void
iterate_oids__(void)
{
    onlp_oid_iterate(ONLP_OID_SYS, 0,
                     iterate_oids_callback__, NULL);
}




int
onlpdump_main(int argc, char* argv[])
{
    int show = 0;
    uint32_t showflags = 0;
    int help = 0;
    int c;
    int rv = -1;
    int j = 0;
    int o = 0;
    int m = 0;
    int i = 0;
    int p = 0;
    int x = 0;
    const char* t = NULL;

    while( (c = getopt(argc, argv, "srehdojmipxt:")) != -1) {
        switch(c)
            {
            case 's': show=1; break;
            case 'r': show=1; showflags |= ONLP_OID_SHOW_F_RECURSE; break;
            case 'e': show=1; showflags |= ONLP_OID_SHOW_F_EXTENDED; break;
            case 'd': show=0; break;
            case 'h': help=1; rv = 0; break;
            case 'j': j=1; break;
            case 'o': o=1; break;
            case 'x': x=1; break;
            case 'm': m=1; break;
            case 'i': i=1; break;
            case 'p': p=1; show=-1; break;
            case 't': t = optarg; break;
            default: help=1; rv = 1; break;
            }
    }

    if(help) {
        printf("Usage: %s [OPTIONS]\n", argv[0]);
        printf("  -d   Use dump(). This is the default.\n");
        printf("  -s   Use show() instead of dump().\n");
        printf("  -r   Recursive show(). Implies -s\n");
        printf("  -e   Extended show(). Implies -s\n");
        printf("  -o   Dump ONIE data only.\n");
        printf("  -x   Dump Platform Info only.\n");
        printf("  -j   Dump ONIE data in JSON format.\n");
        printf("  -m   Run platform manager.\n");
        printf("  -i   Iterate OIDs.\n");
        printf("  -p   Show SFP presence.\n");
        printf("  -t <file>  Decode TlvInfo data.\n");
        return rv;
    }

    if(t) {
        int rv;
        onlp_onie_info_t onie;
        rv = onlp_onie_decode_file(&onie, t);
        if(rv >= 0) {
            onlp_onie_show(&onie, &aim_pvs_stdout);
            onlp_onie_info_free(&onie);
            return 0;
        }
        else {
            aim_printf(&aim_pvs_stdout, "Decode failed.");
            return 1;
        }
    }

    onlp_init();

    if(i) {
        iterate_oids__();
        return 0;
    }

    if(o || x) {
        onlp_sys_info_t si;
        if(onlp_sys_info_get(&si) < 0) {
            fprintf(stderr, "onlp_sys_info_get() failed.");
            return 1;
        }

        if(o) {
            if(j) {
                onlp_onie_show_json(&si.onie_info, &aim_pvs_stdout);
            }
            else {
                onlp_onie_show(&si.onie_info, &aim_pvs_stdout);
            }
        }

        if(x) {
            if(j) {
                onlp_platform_info_show_json(&si.platform_info, &aim_pvs_stdout);
            }
            else {
                onlp_platform_info_show(&si.platform_info, &aim_pvs_stdout);
            }
        }

        onlp_sys_info_free(&si);
        return 0;
    }

    if(show >= 0) {
        if(show == 0) {
            /* Default to full dump */
            onlp_platform_dump(&aim_pvs_stdout,
                               ONLP_OID_DUMP_F_RECURSE | ONLP_OID_DUMP_F_EVEN_IF_ABSENT);
        }
        else {
            onlp_platform_show(&aim_pvs_stdout,
                               showflags);
        }
    }


    if(m) {
        printf("Running the platform manager for 600 seconds...\n");
        onlp_sys_platform_manage_start();
        sleep(600);
        printf("Stopping the platform manager.\n");
        onlp_sys_platform_manage_stop();
    }

    if(p) {
        onlp_sfp_bitmap_t presence;
        onlp_sfp_bitmap_t_init(&presence);
        int rv = onlp_sfp_presence_bitmap_get(&presence);
        aim_printf(&aim_pvs_stdout, "Presence: ");
        if(rv < 0) {
            aim_printf(&aim_pvs_stdout, "Error %{onlp_status}\n", rv);
        }
        else {
            aim_printf(&aim_pvs_stdout, "%{aim_bitmap}\n", &presence);
        }
    }
    return 0;
}
