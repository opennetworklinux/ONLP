###############################################################################
#
#
#
###############################################################################
include ../../../../init.mk
MODULE := onlp_utest
TEST_MODULE := onlp
DEPENDMODULES := AIM onlplib onlp_platform_defaults onlpie IOF
GLOBAL_CFLAGS += -DAIM_CONFIG_INCLUDE_MODULES_INIT=1
GLOBAL_CFLAGS += -DAIM_CONFIG_INCLUDE_MAIN=1
GLOBAL_CFLAGS += -DONLP_CONFIG_INCLUDE_PLATFORM_STATIC=1
GLOBAL_CFLAGS += -DONLP_CONFIG_PLATFORM_STATIC=\"onlpie\"
include $(BUILDER)/build-unit-test.mk
GLOBAL_LINK_LIBS += -lpthread