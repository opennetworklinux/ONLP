###############################################################################
#
#
#
###############################################################################
include ../../../init.mk
MODULE := onlp_utest
TEST_MODULE := onlp
DEPENDMODULES := AIM onlpie
GLOBAL_CFLAGS += -DAIM_CONFIG_INCLUDE_MODULES_INIT=1
GLOBAL_CFLAGS += -DAIM_CONFIG_INCLUDE_MAIN=1
GLOBAL_CFLAGS += -DONLP_CONFIG_INCLUDE_SHLOCK_GLOBAL_INIT=0
GLOBAL_CFLAGS += -DONLP_CONFIG_INCLUDE_PLATFORM_ERROR_CHECK=0
GLOBAL_LINK_LIBS += -lpthread

include $(BUILDER)/build-unit-test.mk

