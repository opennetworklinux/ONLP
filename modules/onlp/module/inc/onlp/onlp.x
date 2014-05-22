/**************************************************************************//**
 *
 *
 *
 *****************************************************************************/
#include <onlp/onlp_config.h>


/* <auto.start.xmacro(ALL).define> */
#ifdef ONLP_OID_TYPE_ENTRY
ONLP_OID_TYPE_ENTRY(SYS, 1)
ONLP_OID_TYPE_ENTRY(THERMAL, 2)
ONLP_OID_TYPE_ENTRY(FAN, 3)
ONLP_OID_TYPE_ENTRY(PSU, 4)
ONLP_OID_TYPE_ENTRY(LED, 5)
ONLP_OID_TYPE_ENTRY(MODULE, 6)
ONLP_OID_TYPE_ENTRY(RTC, 7)
#undef ONLP_OID_TYPE_ENTRY
#endif
/* <auto.end.xmacro(ALL).define> */

/* <auto.start.xenum(ALL).define> */
#ifdef ONLP_ENUMERATION_ENTRY
ONLP_ENUMERATION_ENTRY(onlp_status, "")
ONLP_ENUMERATION_ENTRY(onlp_psu_status, "")
ONLP_ENUMERATION_ENTRY(onlp_led_caps, "")
ONLP_ENUMERATION_ENTRY(onlp_led_status, "")
ONLP_ENUMERATION_ENTRY(onlp_thermal_status, "")
ONLP_ENUMERATION_ENTRY(onlp_oid_type, "")
ONLP_ENUMERATION_ENTRY(onlp_fan_caps, "")
ONLP_ENUMERATION_ENTRY(onlp_fan_status, "")
ONLP_ENUMERATION_ENTRY(onlp_sfp_status, "")
ONLP_ENUMERATION_ENTRY(onlp_fan_dir, "")
ONLP_ENUMERATION_ENTRY(onlp_fan_mode, "")
ONLP_ENUMERATION_ENTRY(onlp_psu_caps, "")
ONLP_ENUMERATION_ENTRY(onlp_led_mode, "")
#undef ONLP_ENUMERATION_ENTRY
#endif
/* <auto.end.xenum(ALL).define> */


