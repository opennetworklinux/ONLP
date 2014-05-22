###############################################################################
#
# 
#
###############################################################################
THIS_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
onlp_platform_defaults_INCLUDES := -I $(THIS_DIR)inc
onlp_platform_defaults_INTERNAL_INCLUDES := -I $(THIS_DIR)src
onlp_platform_defaults_DEPENDMODULE_ENTRIES := init:onlp_platform_defaults ucli:onlp_platform_defaults

