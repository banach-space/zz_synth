#========================================================================
# FILE:
#   src/envelope/Makefile
#
# AUTHOR:
#   zimzum@github 
#
# DESCRIPTION:
#   This is a makefile for the src/envelope directory. Note
#   that this Makefile was not designed to be used as a standalone
#   build script and will not work unless the specified dependencies from
#   other directories are already built. Instead, you can build the
#   Envelope library specified here by typing the following in the root
#   directory by:
#
#   ~/zz_synth$ make src/envelope
#
#   This is the recommended way of using this script. Check the main
#   Makefile for available options.
#
# License: GNU GPL v2.0 
#========================================================================
ZZDIR   = ~/github/zz_synth
library := $(ZZDIR)/lib/libenvelope.a
include ../../include/zz_synth.mk

.PHONY: all new clean chkdirs

#-----------------------
#  SOURCE FILES -->  RULES 
#-----------------------
source_files = \
               envelope.cc\
			   segment.cc

include ../../include/zz_synth_rules.mk
INCLUDES += -lm

#-----------------------
#  TARGETS 
#-----------------------
all: chkdirs $(library)

clean:
	@$(RM) $(object_files)
	@$(RM) $(library)

new: clean all

chkdirs:
	@$(MKDIR) $(ZZLIB)

#-----------------------
#  DEPENDENCIES 
#-----------------------
envelope.cc: \
	$(ZZINC)/envelope/envelope.h\
	$(ZZSRC)/envelope/segment.cc\
	$(ZZINC)/common/zz_global_include.h

segment.cc: \
	$(ZZINC)/envelope/segment.h\
	$(ZZINC)/common/zz_global_include.h\
