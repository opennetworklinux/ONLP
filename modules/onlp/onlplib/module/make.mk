###############################################################################
#
# 
#
###############################################################################
THIS_DIR := $(dir $(lastword $(MAKEFILE_LIST)))
onlplib_INCLUDES := -I $(THIS_DIR)inc
onlplib_INTERNAL_INCLUDES := -I $(THIS_DIR)src
onlplib_DEPENDMODULE_ENTRIES := init:onlplib ucli:onlplib

