#========================================================================
# FILE:
#   src/unit_tests/read_write_wav/Makefile
#
# AUTHOR:
#   zimzum@github 
#
# DESCRIPTION:
#   This is a makefile for the src/unit_tests/read_write_wav directory.
#   Note that this Makefile was not designed to be used as a standalone
#   build script and will not work unless the specified dependencies from
#   other directories are already built. Instead, you can build the
#   testbench specified here by typing the following in the root
#   directory by:
#
#   ~/zz_synth$ make unit_tests/read_write_wav
#
#   This is the recommended way of using this script. Check the main
#   Makefile for available options.
#
# License: GNU GPL v2.0 
#========================================================================
ZZDIR = ~/github/zz_synth
include ../../include/zz_synth.mk

.PHONY: all new clean chkdirs

#-----------------------
#  SOURCE/OBJECT FILES 
#-----------------------
source_files = testbench.cc
libraries = $(ZZDIR)/lib/libcommon.a $(ZZDIR)/lib/libglobal.a
testbench = $(ZZBIN)/testbench_rww$(EXE)

include ../../include/zz_synth_rules.mk

#-----------------------
#  TARGETS 
#-----------------------
all: $(testbench) $(chkdirs) 

new: clean all

clean:
	-rm $(testbench) $(object_files)

chkdirs:
	@$(MKDIR) $(ZZBIN)

#-----------------------
#  DEPENDENCIES 
#-----------------------
testbench.cc: \
	$(ZZINC)/common/wave_file.h\
    $(ZZINC)/common/synth_config.h
