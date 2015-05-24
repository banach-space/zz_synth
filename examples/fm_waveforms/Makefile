#========================================================================
# FILE:
#   examples/fm_waveforms/Makefile
#
# AUTHOR:
#   zimzum@github 
#
# DESCRIPTION:
#   This is a makefile for the following directory:
#
#     [dir_name] = examples/fm_waveforms
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
source_files = fm_waveforms.cc

libraries    =\
	$(lib_common_bin)\
	$(lib_global_bin)\
	$(lib_fm_synthesiser_bin)\
	$(lib_oscillator_bin)

example      = $(ZZBIN)/fm_waveforms$(EXE)

ZZEXAMPLES = $(ZZDIR)/examples/fm_waveforms/sounds

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
fm_waveforms.cc: \
	$(ZZINC)/common/wave_file.h\
	$(ZZINC)/global/global_variables.h\
	$(ZZINC)/oscillator/oscillator.h\
	$(ZZINC)/fm_synthesiser/fm_synthesiser.h\
    $(ZZINC)/common/synth_config.h
