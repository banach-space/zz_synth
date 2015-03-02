#=============================================================
# FILE:
#   src/global/Makefile
#
# AUTHOR:
#   zimzum@github 
#
# DESCRIPTION:
#   This is a makefile for the src/global directory. Note
#   that this Makefile was not designed to be used as a standalone
#   build script and will not work unless the specified dependencies from
#   other directories are already built. Instead, you can build the
#   sources listed here by typing the following in the root
#   directory by:
#
#   ~/zz_synth$ make src/global
#
#   This is the recommended way of using this script. Check the main
#   Makefile for available options.
#
# License: GNU GPL v2.0 
#=============================================================
ZZDIR   = ~/github/zz_synth
library := $(ZZDIR)/lib/libglobal.a
include ../../include/zz_synth.mk

.PHONY: all new clean chkdirs

#-----------------------
#  SOURCE FILES -->  RULES 
#-----------------------
source_files = global_variables.cc

include ../../include/zz_synth_rules.mk

#-----------------------
#  TARGETS 
#-----------------------
all: clean chkdirs $(library)

clean:
	@$(RM) $(object_files)
	@$(RM) $(library)

new: clean all

chkdirs:
	@$(MKDIR) $(ZZLIB)

#-----------------------
#  DEPENDENCIES 
#-----------------------
global_variables.cc: \
	$(ZZINC)/global/global_variables.h
