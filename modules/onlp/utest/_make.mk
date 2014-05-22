###############################################################################
#
# onlp Unit Test Makefile.
#
###############################################################################
UMODULE := onlp
UMODULE_SUBDIR := $(dir $(lastword $(MAKEFILE_LIST)))
include $(BUILDER)/utest.mk
