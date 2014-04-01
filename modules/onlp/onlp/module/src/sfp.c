/************************************************************
 *
 ***********************************************************/
#include <onlp/sfp.h>
#include <onlp/platformi/sfpi.h>
#include "onlp_log.h"

/**
 * All port numbers will be validated before calling the SFP driver.
 */
static onlp_sfp_bitmap_t sfpi_bitmap__;

int
onlp_sfp_init(void)
{
    AIM_BITMAP_CLR_ALL(&sfpi_bitmap__);

    int rv = onlp_sfpi_init();
    if(rv < 0) {
        if(rv == ONLP_STATUS_E_UNSUPPORTED) {
            /*
             * There are no SFPs on this platform.
             * Not necessarily an error condition.
             */
        }
        else {
            AIM_LOG_ERROR("Error initializing the SFPI driver: %{onlp_status}", rv);
        }
        return rv;
    }
    else {
        /* SFPI initialized. Get the bitmap */
        rv = onlp_sfpi_bitmap_get(&sfpi_bitmap__);
        if(rv < 0) {
            AIM_LOG_ERROR("onlp_sfpi_bitmap_get(): %{onlp_status}", rv);
            return rv;
        }
        return ONLP_STATUS_OK;
    }
}

int
onlp_sfp_bitmap_get(onlp_sfp_bitmap_t* bmap)
{
    AIM_BITMAP_ASSIGN(bmap, &sfpi_bitmap__);
    return ONLP_STATUS_OK;
}

int
onlp_sfp_denit(void)
{
    return onlp_sfpi_denit();
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
    return onlp_sfpi_is_present(port);
}

int
onlp_sfp_port_valid(int port)
{
    return AIM_BITMAP_GET(&sfpi_bitmap__, port);
}

int
onlp_sfp_eeprom_read(int port, uint8_t** rv)
{
    uint8_t* data;
    ONLP_SFP_PORT_VALIDATE(port);

    data = aim_zmalloc(256);
    onlp_sfpi_eeprom_read(port, data);
    *rv = data;
    return 256;
}

int
onlp_sfp_reset(int port)
{
    ONLP_SFP_PORT_VALIDATE(port);
    return onlp_sfpi_reset(port);
}


void
onlp_sfp_dump(aim_pvs_t* pvs)
{
    int p;

    if(AIM_BITMAP_COUNT(&sfpi_bitmap__) == 0) {
        aim_printf(pvs, "There are no SFP capable ports.\n");
        return;
    }

    AIM_BITMAP_ITER(&sfpi_bitmap__, p) {
        int rv = onlp_sfp_is_present(p);
        aim_printf(pvs, "Port %.2d: ", p);
        if(rv == 0) {
            /* Missing, OK */
            aim_printf(pvs, "Missing.\n");
        }
        else if(rv == 1) {
            /* Present, OK */
            aim_printf(pvs, "Present.\n");
        }
        else {
            /* Error */
            aim_printf(pvs, "Error: %{onlp_status}\n");
        }
        if(rv == 1) {
            uint8_t* idprom = NULL;
            rv = onlp_sfp_eeprom_read(p, &idprom);
            if(rv < 0) {
                aim_printf(pvs, "Error reading eeprom: %{onlp_status}\n");
            }
            else {
                aim_printf(pvs, "eeprom:\n%{data}\n", idprom, 256);
                aim_free(idprom);
            }
        }
    }
    return;
}

