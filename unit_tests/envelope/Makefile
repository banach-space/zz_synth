#========================================================================
# FILE:
#   src/unit_tests/envelope/Makefile
#
# AUTHOR:
#   zimzum@github 
#
# DESCRIPTION:
#   This is a sub-makefile for the Envelope testbench. Note that
#   this Makefile will not work unless the specified dependencies from
#   other directories are already built. Otherwise this testbench should
#   be build from the root directory by calling:
#
#   ~/zz_synth$ make unit_tests/envelope
#
#   This the reccomended way. Check the main Makefile for available options.
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
libraries = $(ZZDIR)/lib/libcommon.a
testbench = $(ZZBIN)/testbench_envelope$(EXE)

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
	$(ZZINC)/common/envelope.h\
	$(ZZINC)/common/segment.h\
    $(ZZINC)/common/synth_config.h
