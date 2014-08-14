###############################################################################
#
#
#
###############################################################################

include ../../../init.mk
MODULE := sff_utest
TEST_MODULE := sff
DEPENDMODULES := AIM BigList
GLOBAL_CFLAGS += -DAIM_CONFIG_INCLUDE_MODULES_INIT=1
GLOBAL_CFLAGS += -DAIM_CONFIG_INCLUDE_MAIN=1
GLOBAL_CFLAGS += -DSFF_CONFIG_INCLUDE_EXT_CC_CHECK=1
include $(BUILDER)/build-unit-test.mk
