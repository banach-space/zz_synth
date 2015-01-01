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
include ../../include/zz_synth.cfg

.PHONY: all new clean chkdirs

chkdirs:
	@echo Building from $(ZZDIR)
	@test -d $(ZZBIN) || mkdir $(ZZBIN)

OUTPUT=$(ZZBIN)/testbench$(EXE)

$(OUTPUT): chkdirs testbench.cpp 
	$(CPP) $(CPPFLAGS) -o $@ testbench.cpp  -lm 

all: $(OUTPUT)

new: clean $(OUTPUT)

clean:
	-rm $(OUTPUT)

testbench.cpp: $(ZZINC)/zz_global.h $(ZZINC)/zz_WavFile.h
