################################################################
# <bsn.cl fy=2013 v=onl>
# </bsn.cl>
################################################################

#
# The root of of our repository is here:
#
ROOT := $(abspath $(dir $(lastword $(MAKEFILE_LIST))))

#
# Resolve submodule dependencies.
#
ifndef SUBMODULE_INFRA
  ifdef SUBMODULES
    SUBMODULE_INFRA := $(SUBMODULES)/infra
  else
    SUBMODULE_INFRA := $(ROOT)/submodules/infra
  endif
endif

ifndef SUBMODULE_BIGCODE
  ifdef SUBMODULES
    SUBMODULE_BIGCODE := $(SUBMODULES)/bigcode
  else
    SUBMODULE_BIGCODE := $(ROOT)/submodules/bigcode
  endif
endif

export SUBMODULE_INFRA
export BUILDER := $(SUBMODULE_INFRA)/builder/unix

MODULE_DIRS := $(ROOT)/modules $(SUBMODULE_INFRA)/modules $(SUBMODULE_BIGCODE)/modules

.show-submodules:
	@echo infra @ $(SUBMODULE_INFRA)
	@echo bigcode @ $(SUBMODULE_BIGCODE)














