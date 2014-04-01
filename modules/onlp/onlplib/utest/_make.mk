###############################################################################
#
# onlplib Unit Test Makefile.
#
###############################################################################
UMODULE := onlplib
UMODULE_SUBDIR := $(dir $(lastword $(MAKEFILE_LIST)))
include $(BUILDER)/utest.mk
