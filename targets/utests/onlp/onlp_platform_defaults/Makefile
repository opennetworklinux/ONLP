###############################################################################
#
#
#
###############################################################################
include ../../../../init.mk
MODULE := onlp_platform_defaults_utest
TEST_MODULE := onlp_platform_defaults
DEPENDMODULES := AIM onlp onlplib
GLOBAL_CFLAGS += -DAIM_CONFIG_INCLUDE_MODULES_INIT=1
GLOBAL_CFLAGS += -DAIM_CONFIG_INCLUDE_MAIN=1
include $(BUILDER)/build-unit-test.mk
