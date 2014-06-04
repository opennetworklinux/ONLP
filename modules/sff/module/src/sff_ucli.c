/**************************************************************************//**
 *
 *
 *
 *****************************************************************************/
#include <sff/sff_config.h>

#if SFF_CONFIG_INCLUDE_UCLI == 1

#include <uCli/ucli.h>
#include <uCli/ucli_argparse.h>
#include <uCli/ucli_handler_macros.h>

static ucli_status_t
sff_ucli_ucli__config__(ucli_context_t* uc)
{
    UCLI_HANDLER_MACRO_MODULE_CONFIG(sff)
}

/* <auto.ucli.handlers.start> */
/* <auto.ucli.handlers.end> */

static ucli_module_t
sff_ucli_module__ =
    {
        "sff_ucli",
        NULL,
        sff_ucli_ucli_handlers__,
        NULL,
        NULL,
    };

ucli_node_t*
sff_ucli_node_create(void)
{
    ucli_node_t* n;
    ucli_module_init(&sff_ucli_module__);
    n = ucli_node_create("sff", NULL, &sff_ucli_module__);
    ucli_node_subnode_add(n, ucli_module_log_node_create("sff"));
    return n;
}

#else
void*
sff_ucli_node_create(void)
{
    return NULL;
}
#endif

