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
source_files = synth_config.cc wave_file.cc zz_global.cc oscillator.cc
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
synth_config.cc: \
	$(ZZINC)/common/synth_config.h\
	$(ZZINC)/common/zz_global_include.h

zz_global.cc: \
	$(ZZINC)/common/zz_global.h

wave_file.cc: \
	$(ZZINC)/common/wave_file.h\
	$(ZZINC)/common/zz_global_include.h\
	$(ZZINC)/common/zz_global.h

oscillator.cc: \
	$(ZZINC)/common/oscillator.h\
	$(ZZINC)/common/zz_global_include.h\
