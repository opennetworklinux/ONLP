/************************************************************
 * <bsn.cl fy=2014 v=onl>
 * </bsn.cl>
 ************************************************************
 *
 * Dynamic Platform Library Support
 *
 ***********************************************************/
#include <onlp/onlp_config.h>

/**
 * Generic loadable function pointer definition.
 */
typedef void (*onlp_dload_vector_f)(void);

/**
 * @brief Look for a dynamic function symbol in all platform libraries.
 * @param name The name of the symbol.
 * @param rv [out] Receives the vector if found.
 * @param required
 */
int onlp_dload(const char* name, onlp_dload_vector_f* rv, int required);
