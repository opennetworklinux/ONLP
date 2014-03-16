###############################################################################
#
# 
#
###############################################################################
THIS_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
onlpie_INCLUDES := -I $(THIS_DIR)inc
onlpie_INTERNAL_INCLUDES := -I $(THIS_DIR)src
onlpie_DEPENDMODULE_ENTRIES := init:onlpie ucli:onlpie

