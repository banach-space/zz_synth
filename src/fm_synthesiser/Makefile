#========================================================================
# FILE:
#   src/fm_synthesiser/Makefile
#
# AUTHOR:
#   zimzum@github 
#
# DESCRIPTION:
#   This is a makefile for the following directory:
#
#     [dir_name] = src/fm_synthesiser/Makefile
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
ZZDIR   = ~/github/zz_synth
library := $(ZZDIR)/lib/libfmsynthesiser.a
include ../../include/zz_synth.mk

.PHONY: all new clean chkdirs

#-----------------------
#  SOURCE FILES -->  RULES 
#-----------------------
source_files = fm_synthesiser.cc

include ../../include/zz_synth_rules.mk

#-----------------------
#  TARGETS 
#-----------------------
all: chkdirs $(library)

clean:
	$(RM) $(object_files)
	$(RM) $(library)

new: clean all

chkdirs:
	@$(MKDIR) $(ZZLIB)

#-----------------------
#  DEPENDENCIES 
#-----------------------
fm_synthesiser.cc: \
	$(ZZINC)/fm_synthesiser/fm_synthesiser.h
