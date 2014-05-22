###############################################################################
#
#
#
###############################################################################

include ../../../init.mk
MODULE := onlpie_utest
TEST_MODULE := onlpie
DEPENDMODULES := AIM IOF onlp onlplib onlp_platform_defaults
GLOBAL_CFLAGS += -DAIM_CONFIG_INCLUDE_MODULES_INIT=1
GLOBAL_CFLAGS += -DAIM_CONFIG_INCLUDE_MAIN=1
include $(BUILDER)/build-unit-test.mk
