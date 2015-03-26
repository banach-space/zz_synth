#========================================================================
# FILE:
#   examples/waveforms/Makefile
#
# AUTHOR:
#   zimzum@github 
#
# DESCRIPTION:
#   This is a makefile for the examples/waveforms/ directory.
#   Note that this Makefile was not designed to be used as a standalone
#   build script and will not work unless the specified dependencies from
#   other directories are already built. Instead, you can build the
#   testbench specified here by typing the following in the root
#   directory by:
#
#   ~/zz_synth$ make examples/waveforms/
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
source_files = waveforms.cc
libraries    =\
	$(ZZDIR)/lib/libcommon.a\
	$(ZZDIR)/lib/libglobal.a\
	$(ZZDIR)/lib/liboscillator.a
example      = $(ZZBIN)/waveforms$(EXE)

ZZEXAMPLES = $(ZZDIR)/examples/waveforms/sounds

include ../../include/zz_synth_rules.mk

#-----------------------
#  TARGETS 
#-----------------------
all: $(example) chkdirs

new: clean all

clean:
	-rm $(example) $(object_files)

chkdirs:
	$(MKDIR) $(ZZBIN)
	$(MKDIR) $(ZZEXAMPLES)

#-----------------------
#  DEPENDENCIES 
#-----------------------
waveforms.cc: \
	$(ZZINC)/common/wave_file.h\
	$(ZZINC)/global/global_variables.h\
	$(ZZINC)/oscillator/oscillator.h\
    $(ZZINC)/common/synth_config.h
