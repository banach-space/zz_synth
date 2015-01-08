#=============================================================
# FILE:
#   inclue/zz_synth.cfg 
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

lib_common := $(ZZLIB)/libcommon.a

# The Common zz_synth library:
LIBPREFIX=lib
CMNLIB=$(ZZLIB)/$(LIBPREFIX)Common.a

#-----------------------
#  COMPILE VARIABLES 
#-----------------------
# Extension for executables 
EXE=.out

# CPPFLAGS
CPPFLAGS = $(OPTFLAG)
ifeq "$(COMPILE_FLAGS)" "PEDANTIC"
CPPFLAGS += -Wall -pedantic
$(info Pedantic compile flags...)
endif

INCLUDES = -I $(ZZINC)
CXX = g++

# The compiler
COMPILE.cpp = $(CXX) $(CFLAGS) $(INCLUDES) $(CPPFLAGS) $(TARGET_ARCH) -c

#-----------------------
#  IMPLICIT RULES 
#-----------------------
%.o: %.cc
	@echo Compiling $<
	$(COMPILE.cpp) $<

$(ZZBIN)/%.o: %.cc
	@echo Compiling $<
	$(COMPILE.cpp) $< -o $@

#-----------------------
#  MACROS
#-----------------------
define build-msg
 @printf "#\n# [Make:] Building $@\n#\n"
endef

#-----------------------
#  SHELL COMMANDS 
#-----------------------
RANLIB  = ranlib
AR      = ar rv
RM      = rm -rf
MKDIR   = mkdir -p
