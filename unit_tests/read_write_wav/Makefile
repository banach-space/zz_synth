#=============================================================
# FILE:
#   src/unit_tests/read_write_wav/Makefile
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
source_files = testbench.cc
libraries = $(ZZDIR)/lib/libcommon.a
testbench = $(ZZBIN)/testbench$(EXE)

include ../../include/zz_synth_rules.mk

#-----------------------
#  TARGETS 
#-----------------------
all: $(testbench) $(chkdirs) 
	@echo pupaPUPA

new: clean $(OUTPUT)

clean:
	@echo pupa
	@echo $(testbench)
	-rm $(OUTPUT)

chkdirs:
	@$(MKDIR) $(ZZBIN)

#-----------------------
#  DEPENDENCIES 
#-----------------------
testbench.cc: \
	$(ZZINC)/common/zz_WavFile.h\
    $(ZZINC)/common/zz_SynthConfig.h
