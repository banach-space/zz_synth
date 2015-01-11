#=============================================================
# FILE:
#   src/common/Makefile
#
# AUTHOR:
#   zimzum@github 
#
# DESCRIPTION:
#   "make new" rebuilds all executables
#   "make clean" removes the executable images from $(BSBIN)
#
# License: GNU GPL v2.0 
#=============================================================
ZZDIR   = ~/github/zz_synth
library := $(ZZDIR)/lib/libcommon.a
include ../../include/zz_synth.mk

.PHONY: all new clean chkdirs

#-----------------------
#  SOURCE FILES -->  RULES 
#-----------------------
source_files = zz_SynthConfig.cc
include ../../include/zz_synth_rules.mk
INCLUDES += -lm

#-----------------------
#  TARGETS 
#-----------------------
all: chkdirs $(library)

clean:
	@$(RM) $(object_files)
	@$(RM) $(library)

new: clean all

chkdirs:
	@$(MKDIR) $(ZZLIB)

#-----------------------
#  DEPENDENCIES 
#-----------------------
zz_SynthConfig.cc: \
	$(ZZINC)/common/zz_SynthConfig.h\
	$(ZZINC)/common/zz_global_include.h
