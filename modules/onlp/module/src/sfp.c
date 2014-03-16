/************************************************************
 *
 ***********************************************************/
#include <onlp/sfp.h>
#include <onlp/platformi/sfpi.h>

static onlp_sfpi_vectors_t sfpi__ = { NULL };
static onlp_sfp_bitmap_t sfpi_bitmap__;

int
onlp_sfp_init(void)
{
    /*
     * Open every shared library in the current platform libdir
     * and look for the SFPI init function.
     */
    onlp_sfpi_vectors_create_f vectors_create = NULL;

#if ONLP_CONFIG_INCLUDE_DYNAMIC_PLATFORM_LIBRARIES == 1
    {
        int rv;
        rv = onlp_dsymbol_find('onlp_sfpi_vectors_create',
                               (onlp_dsymbol_function_ptr_t*)&vectors_create);
    }
#else
    vectors_create = onlp_sfpi_vectors_create;
#endif

    if(vectors_create(&sfpi__) == 0) {
        sfpi__.init();
        if(sfpi__.bitmap_get) {
            sfpi__.bitmap_get(&sfpi_bitmap__);
        }
        else {
            AIM_BITMAP_CLR_ALL(&sfpi_bitmap__);
        }
    }
    return 0;
}

int
onlp_sfp_denit(void)
{
    if(sfpi__.denit) {
        return sfpi__.denit();
    }
    return 0;
}

int
onlp_sfp_bitmap_get(onlp_sfp_bitmap_t* bmap)
{
    AIM_BITMAP_ASSIGN(bmap, &sfpi_bitmap__);
    return 0;
}

#define ONLP_SFP_PORT_VALIDATE(_port)                    \
    do {                                                 \
        if(AIM_BITMAP_GET(&sfpi_bitmap__, _port) == 0) { \
            return -1;                                   \
        }                                                \
    } while(0)

int
onlp_sfp_is_present(int port)
{
    ONLP_SFP_PORT_VALIDATE(port);
    if(sfpi__.is_present) {
        return sfpi__.is_present(port);
    }
    return -1;
}

int
onlp_sfp_port_valid(int port)
{
    return AIM_BITMAP_GET(&sfpi_bitmap__, port);
}

int
onlp_sfp_eeprom(int port, uint8_t** rv)
{
    ONLP_SFP_PORT_VALIDATE(port);

    if(sfpi__.eeprom) {
        uint8_t* data = aim_zmalloc(256);
        sfpi__.eeprom(port, data);
        *rv = data;
        return 256;
    }
    else {
        return -1;
    }
}


