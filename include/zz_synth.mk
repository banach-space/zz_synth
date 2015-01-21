#=============================================================
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
#=============================================================

# ZZDIR is the root directory for zz_synth. The main Makefile 
# sets this to the directory of the Makefile. Optionally, set
# this from the command line: make ZZDIR=path
ifeq ($(ZZDIR),)
$(error No value for ZZDIR)
endif

# The directory containing the binaries, include files and
# libraries
ZZBIN = $(ZZDIR)/bin
ZZINC = $(ZZDIR)/include
ZZLIB = $(ZZDIR)/lib

#-----------------------
#  LIBRARIES 
#-----------------------
lib_common  := src/common
#lib_common  := $(ZZLIB)/libcommon.a

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
