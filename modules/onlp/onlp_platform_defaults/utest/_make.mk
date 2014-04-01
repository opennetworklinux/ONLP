###############################################################################
#
# onlp_platform_defaults Unit Test Makefile.
#
###############################################################################
UMODULE := onlp_platform_defaults
UMODULE_SUBDIR := $(dir $(lastword $(MAKEFILE_LIST)))
include $(BUILDER)/utest.mk
