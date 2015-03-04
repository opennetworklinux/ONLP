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
 *
 *
 ***********************************************************/
#include <onlp/sfp.h>
#include <onlp/platformi/sfpi.h>
#include "onlp_log.h"
#include "onlp_locks.h"

/**
 * All port numbers will be validated before calling the SFP driver.
 */
static onlp_sfp_bitmap_t sfpi_bitmap__;

void
onlp_sfp_bitmap_t_init(onlp_sfp_bitmap_t* bmap)
{
    AIM_BITMAP_INIT(bmap, 255);
    AIM_BITMAP_CLR_ALL(bmap);
}

static int
onlp_sfp_init_locked__(void)
{
    onlp_sfp_bitmap_t_init(&sfpi_bitmap__);

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
ONLP_LOCKED_API0(onlp_sfp_init)



static int
onlp_sfp_bitmap_get_locked__(onlp_sfp_bitmap_t* bmap)
{
    AIM_BITMAP_ASSIGN(bmap, &sfpi_bitmap__);
    return ONLP_STATUS_OK;
}
ONLP_LOCKED_API1(onlp_sfp_bitmap_get, onlp_sfp_bitmap_t*, bmap);


static int
onlp_sfp_denit_locked__(void)
{
    return onlp_sfpi_denit();
}
ONLP_LOCKED_API0(onlp_sfp_denit);


#define ONLP_SFP_PORT_VALIDATE_AND_MAP(_port)            \
    do {                                                 \
        if(AIM_BITMAP_GET(&sfpi_bitmap__, _port) == 0) { \
            return -1;                                   \
        }                                                \
        int _rport;                                      \
        if(onlp_sfpi_port_map(_port, &_rport) >= 0) {  \
            _port = _rport;                              \
        }                                                \
    } while(0)

static int
onlp_sfp_is_present_locked__(int port)
{
    ONLP_SFP_PORT_VALIDATE_AND_MAP(port);
    return onlp_sfpi_is_present(port);
}
ONLP_LOCKED_API1(onlp_sfp_is_present, int, port);

static int
onlp_sfp_presence_bitmap_get_locked__(onlp_sfp_bitmap_t* dst)
{
    return onlp_sfpi_presence_bitmap_get(dst);
}
ONLP_LOCKED_API1(onlp_sfp_presence_bitmap_get, onlp_sfp_bitmap_t*, dst);


static int
onlp_sfp_rx_los_bitmap_get_locked__(onlp_sfp_bitmap_t* dst)
{
    return onlp_sfpi_rx_los_bitmap_get(dst);
}
ONLP_LOCKED_API1(onlp_sfp_rx_los_bitmap_get, onlp_sfp_bitmap_t*, dst);

int
onlp_sfp_port_valid(int port)
{
    return AIM_BITMAP_GET(&sfpi_bitmap__, port);
}

static int
onlp_sfp_eeprom_read_locked__(int port, uint8_t** rv)
{
    uint8_t* data;
    ONLP_SFP_PORT_VALIDATE_AND_MAP(port);

    data = aim_zmalloc(256);
    onlp_sfpi_eeprom_read(port, data);
    *rv = data;
    return 256;
}
ONLP_LOCKED_API2(onlp_sfp_eeprom_read, int, port, uint8_t**, rv);

static int
onlp_sfp_dom_read_locked__(int port, uint8_t** rv)
{
    uint8_t* data;
    ONLP_SFP_PORT_VALIDATE_AND_MAP(port);

    data = aim_zmalloc(256);
    onlp_sfpi_dom_read(port, data);
    *rv = data;
    return 256;
}
ONLP_LOCKED_API2(onlp_sfp_dom_read, int, port, uint8_t**, rv);






static int
onlp_sfp_reset_locked__(int port)
{
    ONLP_SFP_PORT_VALIDATE_AND_MAP(port);
    return onlp_sfpi_reset(port);
}
ONLP_LOCKED_API1(onlp_sfp_reset, int, port);


void
onlp_sfp_dump(aim_pvs_t* pvs)
{
    int p;
    int rv;

    if(AIM_BITMAP_COUNT(&sfpi_bitmap__) == 0) {
        aim_printf(pvs, "There are no SFP capable ports.\n");
        return;
    }

    onlp_sfp_bitmap_t bmap;
    onlp_sfp_bitmap_t_init(&bmap);
    rv = onlp_sfp_presence_bitmap_get(&bmap);
    aim_printf(pvs, "  Presence Bitmap: ");
    if(rv == 0) {
        aim_printf(pvs, "%{aim_bitmap}\n", &bmap);
    }
    else {
        aim_printf(pvs,"Error: %{onlp_status}\n", rv);
    }
    aim_printf(pvs, "  RX_LOS Bitmap: ");
    rv = onlp_sfp_rx_los_bitmap_get(&bmap);
    if(rv == 0) {
        aim_printf(pvs, "%{aim_bitmap}\n", &bmap);
    }
    else {
        aim_printf(pvs, "Error: %{onlp_status}\n", rv);
    }
    aim_printf(pvs, "\n");

    AIM_BITMAP_ITER(&sfpi_bitmap__, p) {
        rv = onlp_sfp_is_present(p);
        aim_printf(pvs, "Port %.2d: ", p);
        if(rv == 0) {
            /* Missing, OK */
            aim_printf(pvs, "Missing.\n");
        }
        else if(rv == 1) {
            /* Present, OK */
            uint32_t status = 0;
            int srv = onlp_sfp_status_get(p, &status);
            if(srv >= 0) {
                aim_printf(pvs, "Present, Status = %{onlp_sfp_status_flags}\n", status);
            }
            else {
                aim_printf(pvs, "Present, Status Unavailable [ %{onlp_status} ]\n", srv);
            }
        }
        else {
            /* Error */
            aim_printf(pvs, "Error: %{onlp_status}\n", rv);
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

static int
onlp_sfp_post_insert_locked__(int port, sff_info_t* info)
{
    ONLP_SFP_PORT_VALIDATE_AND_MAP(port);
    return onlp_sfpi_post_insert(port, info);
}
ONLP_LOCKED_API2(onlp_sfp_post_insert, int, port, sff_info_t*, info);


static int
onlp_sfp_enable_set_locked__(int port, int enable)
{
    ONLP_SFP_PORT_VALIDATE_AND_MAP(port);
    return onlp_sfpi_enable_set(port, enable);
}
ONLP_LOCKED_API2(onlp_sfp_enable_set, int, port, int, enable);

static int
onlp_sfp_enable_get_locked__(int port, int* enable)
{
    ONLP_SFP_PORT_VALIDATE_AND_MAP(port);
    return onlp_sfpi_enable_get(port, enable);
}
ONLP_LOCKED_API2(onlp_sfp_enable_get, int, port, int*, enable);

static int
onlp_sfp_status_get_locked__(int port, uint32_t* flags)
{
    ONLP_SFP_PORT_VALIDATE_AND_MAP(port);
    return onlp_sfpi_status_get(port, flags);
}
ONLP_LOCKED_API2(onlp_sfp_status_get, int, port, uint32_t*, flags);

static int
onlp_sfp_control_set_locked__(int port, onlp_sfp_control_t control, int value)
{
    ONLP_SFP_PORT_VALIDATE_AND_MAP(port);

    if(!ONLP_SFP_CONTROL_VALID(control)) {
        return ONLP_STATUS_E_PARAM;
    }

    switch(control)
        {
        case ONLP_SFP_CONTROL_RX_LOS:
        case ONLP_SFP_CONTROL_TX_FAULT:
            /** These are read-only. */
            return ONLP_STATUS_E_PARAM;
        default:
            break;
        }
    return onlp_sfpi_control_set(port, control, value);
}
ONLP_LOCKED_API3(onlp_sfp_control_set, int, port, onlp_sfp_control_t, control,
                 int, value);

static int
onlp_sfp_control_get_locked__(int port, onlp_sfp_control_t control, int* value)
{
    ONLP_SFP_PORT_VALIDATE_AND_MAP(port);

    if(!ONLP_SFP_CONTROL_VALID(control)) {
        return ONLP_STATUS_E_PARAM;
    }

    return (value) ? onlp_sfpi_control_get(port, control, value) : ONLP_STATUS_E_PARAM;
}
ONLP_LOCKED_API3(onlp_sfp_control_get, int, port, onlp_sfp_control_t, control,
                 int*, value);

int
onlp_sfp_ioctl(int port, ...)
{
    int rv;
    va_list vargs;
    va_start(vargs, port);
    rv = onlp_sfp_vioctl(port, vargs);
    va_end(vargs);
    return rv;
}

int
onlp_sfp_vioctl_locked__(int port, va_list vargs)
{
    return onlp_sfpi_ioctl(port, vargs);
};
ONLP_LOCKED_API2(onlp_sfp_vioctl, int, port, va_list, vargs);


