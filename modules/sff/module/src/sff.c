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

    if (SFF8472_MODULE_SFP(idprom)
        && SFF8472_MEDIA_XGE_ER(idprom))
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
        return -1;
    }
    rv->sfp_type_name = sff_sfp_type_desc(rv->sfp_type);

    rv->module_type = sff_module_type_get(rv->eeprom);
    if(rv->module_type == SFF_MODULE_TYPE_INVALID) {
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
    return 0;
}


