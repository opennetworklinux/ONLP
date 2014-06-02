###############################################################################
#
# 
#
###############################################################################

include ../../../init.mk
MODULE := sff_utest
TEST_MODULE := sff
DEPENDMODULES := AIM
GLOBAL_CFLAGS += -DAIM_CONFIG_INCLUDE_MODULES_INIT=1
GLOBAL_CFLAGS += -DAIM_CONFIG_INCLUDE_MAIN=1
include $(BUILDER)/build-unit-test.mk
