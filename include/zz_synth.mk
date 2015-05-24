#========================================================================
# FILE:
#   inclue/zz_synth.mk 
#
# AUTHOR:
#   zimzum@github 
#
# DESCRIPTION:
#   Make variables/macros for compiling and installing zz_synth 
#
# License: GNU GPL v2.0 
#========================================================================
#-----------------------
#  DIRECTORIES 
#-----------------------
# ZZDIR is the root directory for zz_synth. The main Makefile 
# sets this to the directory of the Makefile. Optionally, set
# this from the command line: make ZZDIR=path
ifeq ($(ZZDIR),)
$(error No value for ZZDIR)
endif

ZZBIN = $(ZZDIR)/bin
ZZINC = $(ZZDIR)/include
ZZSRC = $(ZZDIR)/src
ZZLIB = $(ZZDIR)/lib

#-----------------------
#  LIBRARIES 
#-----------------------
lib_common_bin         := $(ZZLIB)/libcommon.a
lib_global_bin         := $(ZZLIB)/libglobal.a
lib_envelope_bin       := $(ZZLIB)/libenvelope.a
lib_oscillator_bin     := $(ZZLIB)/liboscillator.a
lib_fm_synthesiser_bin := $(ZZLIB)/libfm_synthesiser.a

#-----------------------
#  COMPILE VARIABLES 
#-----------------------
# Extension for executables 
EXE =.out

#-----------------------
#  SOURCE/OBJECT FILES 
#-----------------------
object_files = $(patsubst %.cc, $(ZZBIN)/%.o, $(source_files))

#-----------------------
#  MACROS
#-----------------------
define build-msg
 @printf "=====================================================\n"
 @printf "[build-msg]"
 @tput bold
 @printf " Building $@"
 @tput sgr0 
 @printf "\n=====================================================\n"
endef
