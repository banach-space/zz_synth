#========================================================================
# FILE:
#   src/unit_tests/oscillator/Makefile
#
# AUTHOR:
#   zimzum@github 
#
# DESCRIPTION:
#   This is a makefile for the following directory:
#
#     [dir_name] = unit_tests/oscillator
#
#   This Makefile was not designed to be used as a standalone
#   build script and will not work unless the specified dependencies from
#   other directories are already built. Instead, you can build the
#   testbench specified here by typing the following in the root
#   directory:
#
#   $ make  [dir_name]
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
libraries    = \
	$(lib_common_bin)\
	$(lib_global_bin)\
	$(lib_oscillator_bin)

testbench    = $(ZZBIN)/testbench_oscillator$(EXE)

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
	$(ZZINC)/oscillator/oscillator.h\
    $(ZZINC)/common/synth_config.h
