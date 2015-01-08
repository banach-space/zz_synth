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

object_files = $(patsubst %.cc, $(ZZBIN)/%.o, $(source_files))

testbench = $(ZZBIN)/testbench$(EXE)

#-----------------------
#  TARGETS 
#-----------------------
all: $(testbench) $(chkdirs) 
	@echo dupa

new: clean $(OUTPUT)

clean:
	-rm $(OUTPUT)

chkdirs:
	@$(MKDIR) $(ZZBIN)

$(testbench): $(object_files) $(lib_common)
	$(LINK.o) $^ -o $@

#-----------------------
#  DEPENDENCIES 
#-----------------------
testbench.cc: \
	$(ZZINC)/common/zz_global.h\
	$(ZZINC)/common/zz_WavFile.h
