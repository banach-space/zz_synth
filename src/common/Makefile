#=============================================================
# FILE:
#   src/common/Makefile
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
source_files = zz_SynthConfig.cc

object_files =$(patsubst %.cc, $(ODIR)/%.o, $(source_files))

#-----------------------
#  TARGETS 
#-----------------------
all: chkdirs $(lib_common) 
	@echo $(object_files) 

new: clean all

chkdirs:
	@test -d $(ODIR) || mkdir $(ODIR)
	
clean:
	-@rm $(OBJS)
	-@rm $(lib_common)

$(lib_common): $(objects)
	@test $@ || rm $@
	@ar r $@ $(OBJS)
	@ranlib $@

#-----------------------
#  DEPENDENCIES 
#-----------------------
zz_SynthConfig.cc: \
	$(ZZINC)/zz_SynthConfig.h\
	$(ZZINC)/zz_global_include.h
