###############################################################################
#
# 
#
###############################################################################
THIS_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
onlp_INCLUDES := -I $(THIS_DIR)inc
onlp_INTERNAL_INCLUDES := -I $(THIS_DIR)src
onlp_DEPENDMODULE_ENTRIES := init:onlp ucli:onlp

