############################################################
# <bsn.cl fy=2014 v=onl>
#
#        Copyright 2014, 2015 Big Switch Networks, Inc.
#
# Licensed under the Eclipse Public License, Version 1.0 (the
# "License"); you may not use this file except in compliance
# with the License. You may obtain a copy of the License at
#
#        http://www.eclipse.org/legal/epl-v10.html
#
# Unless required by applicable law or agreed to in writing,
# software distributed under the License is distributed on an
# "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND,
# either express or implied. See the License for the specific
# language governing permissions and limitations under the
# License.
#
# </bsn.cl>
############################################################
#
#
#
############################################################
include ../../../init.mk

.DEFAULT_GOAL := onlpdump
DEBUG := 1

MODULE := onlpdump
include $(BUILDER)/standardinit.mk

ifndef ONLPI_MODULE
ONLPI_MODULE := onlpie
endif

DEPENDMODULES := AIM onlp $(ONLPI_MODULE) onlplib onlp_platform_defaults IOF cjson cjson_util sff timer_wheel OS

include $(BUILDER)/dependmodules.mk

BINARY := onlpdump
$(BINARY)_LIBRARIES := $(LIBRARY_TARGETS)
include $(BUILDER)/bin.mk

GLOBAL_CFLAGS += -DAIM_CONFIG_AIM_MAIN_FUNCTION=onlpdump_main
GLOBAL_CFLAGS += -DAIM_CONFIG_INCLUDE_MODULES_INIT=1
GLOBAL_CFLAGS += -DAIM_CONFIG_INCLUDE_MAIN=1
GLOBAL_CFLAGS += -DONLP_CONFIG_API_LOCK_TIMEOUT=1
GLOBAL_CFLAGS += -DONLP_CONFIG_INCLUDE_PLATFORM_STATIC=1
GLOBAL_CFLAGS += -DONLP_CONFIG_PLATFORM_STATIC=\"onlp-example-platform-driver\"

ifdef ONLPSIM_CONFIG_SFP_COUNT
GLOBAL_CFLAGS += -DONLPSIM_CONFIG_SFP_COUNT=$(ONLPSIM_CONFIG_SFP_COUNT)
endif

GLOBAL_LINK_LIBS += -lpthread -lm

include $(BUILDER)/targets.mk

