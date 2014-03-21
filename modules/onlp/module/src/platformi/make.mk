###############################################################################
#
#
#
###############################################################################
LIBRARY := onlp-platform-defaults
ifndef NO_$(LIBRARY)
$(LIBRARY)_SUBDIR := $(dir $(lastword $(MAKEFILE_LIST)))
$(LIBRARY)_LAST := 1
include $(BUILDER)/lib.mk
endif
