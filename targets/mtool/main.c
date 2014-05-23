/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * 
 *           Copyright 2014 Big Switch Networks, Inc.          
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
 * Physical Memory Tool
 *
 ***********************************************************/
#include <onlplib/mmap.h>
#include <onlplib/onie.h>

int
aim_main(int argc, char* argv[])
{
    /*
     * Fixme -- this is just a hacked placeholder for
     * a more fully-functional tool.
     */
    uint32_t pa;
    int size;
    uint8_t* va = NULL;

#define USAGE()                                                         \
    do {                                                                \
        fprintf(stderr, "usage: mtool dump PHYSADDR BYTES\n");          \
        fprintf(stderr, "usage: mtool odump PHYSADDR [json]\n");        \
        return 1;                                                       \
    } while(0)

    if(argc < 3) {
        USAGE();
    }

    if(sscanf(argv[2], "0x%x", &pa) != 1) {
        USAGE();
    }

    if(!strcmp(argv[1], "dump")) {
        if(argv[3] == NULL || sscanf(argv[3], "%d", &size) != 1) {
            USAGE();
        }
        va = onlp_mmap(pa, size, "mtool");
        if(va) {
            aim_printf(&aim_pvs_stdout, "%{data}\n", va, size);
        }
    }
    else if(!strcmp(argv[1], "odump")) {
        size = 1024*512; /* arbitrary */
        va = onlp_mmap(pa, size, "mtool");
        if(va) {
            onlp_onie_info_t info;
            if(onlp_onie_decode(&info, va, size) == 0) {
                if(argv[3] && !strcmp(argv[3], "json")) {
                    onlp_onie_show_json(&info, &aim_pvs_stdout);
                }
                else {
                    onlp_onie_show(&info, &aim_pvs_stdout);
                }
                onlp_onie_info_free(&info);
            }
            else {
                int dsize = 128;
                aim_printf(&aim_pvs_stdout, "Here are the first %d bytes:\n%{data}\n", dsize, va, dsize);
            }
        }
    }
    else {
        USAGE();
    }
    if(va) {
        munmap(va, size);
    }
    return 0;
}

