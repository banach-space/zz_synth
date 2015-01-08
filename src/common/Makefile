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
ZZDIR = ~/github/zz_synth
include ../../include/zz_synth.mk

.PHONY: all new clean chkdirs

#-----------------------
#  SOURCE/OBJECT FILES 
#-----------------------
source_files = zz_SynthConfig.cc

object_files = $(patsubst %.cc, $(ZZBIN)/%.o, $(source_files))

#-----------------------
#  TARGETS 
#-----------------------
#lib_common = $(ZZLIB)/libcommon.a

all: chkdirs $(lib_common)

new: clean all

chkdirs:
	@$(MKDIR) $(ZZBIN)
	
clean:
	@$(RM) $(object_files)
	@$(RM) $(lib_common)

$(lib_common): $(object_files)
	@echo $(object_files)
	@$(AR) $@ $?
	@$(RANLIB) $@

#-----------------------
#  DEPENDENCIES 
#-----------------------
zz_SynthConfig.cc: \
	$(ZZINC)/common/zz_SynthConfig.h\
	$(ZZINC)/common/zz_global_include.h
