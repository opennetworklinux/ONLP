/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 *
 *
 ***********************************************************/
#include <sff/sff.h>
#include <sff/8472.h>
#include <sff/8436.h>
#include "sff_log.h"

sff_sfp_type_t
sff_sfp_type_get(const uint8_t* idprom)
{
    if(idprom) {
        if(SFF8472_MODULE_SFP(idprom)) {
            return SFF_SFP_TYPE_SFP;
        }
        if(SFF8436_MODULE_QSFP_PLUS_V2(idprom)) {
            return SFF_SFP_TYPE_QSFP_PLUS;
        }
    }
    return SFF_SFP_TYPE_INVALID;
}

sff_module_type_t
sff_module_type_get(const uint8_t* idprom)
{
    if (SFF8436_MODULE_QSFP_PLUS_V2(idprom)
        && SFF8436_MEDIA_40GE_CR4(idprom))
        return SFF_MODULE_TYPE_40G_BASE_CR4;

    if (SFF8436_MODULE_QSFP_PLUS_V2(idprom)
        && SFF8436_MEDIA_40GE_SR4(idprom))
        return SFF_MODULE_TYPE_40G_BASE_SR4;

    if (SFF8436_MODULE_QSFP_PLUS_V2(idprom)
        && SFF8436_MEDIA_40GE_LR4(idprom))
        return SFF_MODULE_TYPE_40G_BASE_LR4;

    if (SFF8436_MODULE_QSFP_PLUS_V2(idprom)
        && SFF8436_MEDIA_40GE_ACTIVE(idprom))
        return SFF_MODULE_TYPE_40G_BASE_ACTIVE;

    if (SFF8436_MODULE_QSFP_PLUS_V2(idprom)
        && SFF8436_MEDIA_40GE_CR(idprom))
        return SFF_MODULE_TYPE_40G_BASE_CR;

    /* pre-standard finisar optics */
    if (SFF8436_MODULE_QSFP_PLUS_V2(idprom)
        && _sff8436_qsfp_40g_pre(idprom)
        && (SFF8436_TECH_FC_FIBER_LONG(idprom)
            || SFF8436_MEDIA_FC_FIBER_SM(idprom)))
        return SFF_MODULE_TYPE_40G_BASE_LR4;

    if (SFF8436_MODULE_QSFP_PLUS_V2(idprom)
        && _sff8436_qsfp_40g_pre(idprom)
        && (SFF8436_TECH_FC_FIBER_SHORT(idprom)
            || SFF8436_MEDIA_FC_FIBER_MM(idprom)))
        return SFF_MODULE_TYPE_40G_BASE_SR4;

    if (SFF8472_MODULE_SFP(idprom)
        && SFF8472_MEDIA_XGE_SR(idprom))
        return SFF_MODULE_TYPE_10G_BASE_SR;

    if (SFF8472_MODULE_SFP(idprom)
        && SFF8472_MEDIA_XGE_LR(idprom))
        return SFF_MODULE_TYPE_10G_BASE_LR;

    if (SFF8472_MODULE_SFP(idprom)
        && SFF8472_MEDIA_XGE_LRM(idprom))
        return SFF_MODULE_TYPE_10G_BASE_LRM;

    /*
     * XXX roth -- PAN-934 -- DAC cable erroneously reports ER,
     * so we need to disallow infiniband features when matching here.
     * See also _sff8472_media_cr_passive, which encodes some
     * additional workarounds for these cables.
     */
    if (SFF8472_MODULE_SFP(idprom)
        && SFF8472_MEDIA_XGE_ER(idprom)
        && !_sff8472_inf_1x_cu_active(idprom)
        && !_sff8472_inf_1x_cu_passive(idprom))
        return SFF_MODULE_TYPE_10G_BASE_ER;

    /* XXX roth - not sure on this one */
    if (SFF8472_MODULE_SFP(idprom)
        && _sff8472_media_cr_passive(idprom))
        return SFF_MODULE_TYPE_10G_BASE_CR;

    if (SFF8472_MODULE_SFP(idprom)
        && _sff8472_media_cr_active(idprom))
        return SFF_MODULE_TYPE_10G_BASE_CR;

    if (SFF8472_MODULE_SFP(idprom)
        && SFF8472_MEDIA_GBE_SX(idprom))
        return SFF_MODULE_TYPE_1G_BASE_SX;

    if (SFF8472_MODULE_SFP(idprom)
        && SFF8472_MEDIA_GBE_LX(idprom))
        return SFF_MODULE_TYPE_1G_BASE_LX;

    if (SFF8472_MODULE_SFP(idprom)
        && SFF8472_MEDIA_GBE_CX(idprom))
        return SFF_MODULE_TYPE_1G_BASE_CX;

    if (SFF8472_MODULE_SFP(idprom)
        && SFF8472_MEDIA_GBE_T(idprom))
        return SFF_MODULE_TYPE_1G_BASE_T;

    if (SFF8472_MODULE_SFP(idprom)
        && SFF8472_MEDIA_GBE_LX(idprom))
        return SFF_MODULE_TYPE_1G_BASE_LX;

    if (SFF8472_MODULE_SFP(idprom)
        && SFF8472_MEDIA_CBE_LX(idprom))
        return SFF_MODULE_TYPE_100_BASE_LX;

    if (SFF8472_MODULE_SFP(idprom)
        && SFF8472_MEDIA_CBE_FX(idprom))
        return SFF_MODULE_TYPE_100_BASE_FX;

    /* non-standard (e.g. Finisar) ZR media */
    if (SFF8472_MODULE_SFP(idprom)
        && _sff8472_media_zr(idprom))
        return SFF_MODULE_TYPE_10G_BASE_ZR;

    /* non-standard (e.g. Finisar) SRL media */
    if (SFF8472_MODULE_SFP(idprom)
        && _sff8472_media_srlite(idprom))
        return SFF_MODULE_TYPE_10G_BASE_SRL;

    return SFF_MODULE_TYPE_INVALID;
}

sff_media_type_t
sff_media_type_get(const uint8_t* idprom)
{
    sff_module_type_t mt = sff_module_type_get(idprom);

    switch(mt)
        {
        case SFF_MODULE_TYPE_40G_BASE_CR4:
        case SFF_MODULE_TYPE_40G_BASE_CR:
        case SFF_MODULE_TYPE_10G_BASE_CR:
        case SFF_MODULE_TYPE_1G_BASE_CX:
        case SFF_MODULE_TYPE_1G_BASE_T:
            return SFF_MEDIA_TYPE_COPPER;

        case SFF_MODULE_TYPE_40G_BASE_SR4:
        case SFF_MODULE_TYPE_40G_BASE_LR4:
        case SFF_MODULE_TYPE_40G_BASE_ACTIVE:
        case SFF_MODULE_TYPE_10G_BASE_SR:
        case SFF_MODULE_TYPE_10G_BASE_LR:
        case SFF_MODULE_TYPE_10G_BASE_LRM:
        case SFF_MODULE_TYPE_10G_BASE_ER:
        case SFF_MODULE_TYPE_10G_BASE_SX:
        case SFF_MODULE_TYPE_10G_BASE_LX:
        case SFF_MODULE_TYPE_10G_BASE_ZR:
        case SFF_MODULE_TYPE_10G_BASE_SRL:
        case SFF_MODULE_TYPE_1G_BASE_SX:
        case SFF_MODULE_TYPE_1G_BASE_LX:
        case SFF_MODULE_TYPE_100_BASE_LX:
        case SFF_MODULE_TYPE_100_BASE_FX:
            return SFF_MEDIA_TYPE_FIBER;

        case SFF_MODULE_TYPE_COUNT:
        case SFF_MODULE_TYPE_INVALID:
            return SFF_MEDIA_TYPE_INVALID;
        }

    return SFF_MEDIA_TYPE_INVALID;
}


void
sff_module_show(const uint8_t* idprom, aim_pvs_t* pvs)
{

    if (SFF8436_MODULE_QSFP_PLUS_V2(idprom)) {
        aim_printf(pvs,
                   "%-12.12s  %-16.16s  %-16.16s  %-16.16s\n",
                   sff_module_type_desc(sff_module_type_get(idprom)),
                   idprom+148, idprom+168, idprom+196);
    } else {
        aim_printf(pvs,
                   "%-12.12s  %-16.16s  %-16.16s  %-16.16s\n",
                   sff_module_type_desc(sff_module_type_get(idprom)),
                   idprom+20, idprom+40, idprom+68);
    }
}


/**
 * @brief Initialize an SFF module information structure.
 * @param rv [out] Receives the data.
 * @param eeprom Raw EEPROM data.
 * @note if eeprom is != NULL it will be copied into rv->eeprom first.
 * @note if eeprom is NULL it is assumed the rv->eeprom buffer
 * has already been initialized.
 */
int
sff_info_init(sff_info_t* rv, uint8_t* eeprom)
{
    if(rv == NULL) {
        return -1;
    }
    if(eeprom) {
        SFF_MEMCPY(rv->eeprom, eeprom, 256);
    }

    rv->sfp_type = sff_sfp_type_get(rv->eeprom);
    if(rv->sfp_type == SFF_SFP_TYPE_INVALID) {
        AIM_LOG_ERROR("sff_info_init() failed: invalid sfp type");
        return -1;
    }
    rv->sfp_type_name = sff_sfp_type_desc(rv->sfp_type);

    rv->module_type = sff_module_type_get(rv->eeprom);
    if(rv->module_type == SFF_MODULE_TYPE_INVALID) {
        AIM_LOG_ERROR("sff_info_init() failed: invalid module type");
        return -1;
    }
    rv->module_type_name = sff_module_type_desc(rv->module_type);

    rv->media_type = sff_media_type_get(rv->eeprom);
    rv->media_type_name = sff_media_type_desc(rv->media_type);

    rv->length = -1;
    if(rv->media_type == SFF_MEDIA_TYPE_COPPER) {
        switch(rv->sfp_type)
            {
            case SFF_SFP_TYPE_QSFP_PLUS:
                rv->length = rv->eeprom[146];
                break;
            case SFF_SFP_TYPE_SFP:
                rv->length = rv->eeprom[18];
                break;

            case SFF_SFP_TYPE_QSFP:
            case SFF_SFP_TYPE_COUNT:
            case SFF_SFP_TYPE_INVALID:
                break;
            }
    }

    const uint8_t *vendor, *model, *serial;

    switch(rv->sfp_type)
        {
        case SFF_SFP_TYPE_QSFP_PLUS:
            vendor=rv->eeprom+148;
            model=rv->eeprom+168;
            serial=rv->eeprom+196;
            break;

        case SFF_SFP_TYPE_SFP:
        default:
            vendor=rv->eeprom+20;
            model=rv->eeprom+40;
            serial=rv->eeprom+68;
            break;
        }

    aim_strlcpy(rv->vendor, (char*)vendor, sizeof(rv->vendor));
    aim_strlcpy(rv->model, (char*)model, sizeof(rv->model));
    aim_strlcpy(rv->serial, (char*)serial, sizeof(rv->serial));

    if(rv->length == -1) {
        rv->length_desc[0] = 0;
    }
    else {
        SFF_SNPRINTF(rv->length_desc, sizeof(rv->length_desc), "%dm", rv->length);
    }
    return 0;
}

void
sff_info_show(sff_info_t* info, aim_pvs_t* pvs)
{
    aim_printf(pvs, "Vendor: %s Model: %s SN: %s Type: %s Module: %s Media: %s Length: %d\n",
               info->vendor, info->model, info->serial, info->sfp_type_name,
               info->module_type_name, info->media_type_name, info->length);
}

int
sff_info_init_file(sff_info_t* info, const char* fname)
{
    int rv;
    FILE* fp;

    SFF_MEMSET(info, 0, sizeof(*info));

    if( (fp = fopen(fname, "r")) == NULL) {
        AIM_LOG_ERROR("Failed to open eeprom file %s: %{errno}");
        return -1;
    }

    if( (rv = fread(info->eeprom, 1, 256, fp)) > 0) {
        if( (rv=sff_info_init(info, NULL)) < 0) {
            AIM_LOG_ERROR("sff_init() failed on data from file %s: %d\n", fname, rv);
            rv = -1;
        }
        rv = 0;
    }
    else {
        rv = -1;
    }
    fclose(fp);
    return rv;
}

