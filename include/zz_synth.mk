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
ZZBIN=$(ZZDIR)/bin
ZZINC=$(ZZDIR)/include/common
ZZLIB=$(ZZDIR)/lib

# The Common zz_synth library:
LIBPREFIX=lib
CMNLIB=$(ZZLIB)/$(LIBPREFIX)Common.a

#-----------------------
#  COMPILE VARIABLES 
#-----------------------
# Extension for executables 
EXE=.out

# CPPFLAGS
ifeq ($(COMPILE_FLAGS),)
CPPFLAGS= -I $(ZZINC) $(OPTFLAG)
$(info Standard compile flags...)
else
CPPFLAGS= -I $(ZZINC) $(OPTFLAG) -Wall -pedantic
$(info Pedantic compile flags...)
endif

# The compiler
CPP=g++

#-----------------------
#  IMPLICIT RULES 
#-----------------------
%.o: %.cc
	@echo Compiling $<
	@$(CPP) -c $(CPPFLAGS) $<

$(ODIR)/%.o: %.cc
	@echo Compiling $<
	@$(CPP) -c $(CPPFLAGS) $< -o $@

#-----------------------
#  MACROS
#-----------------------
define build-msg
 @printf "#\n# [Make:] Building $@\n#\n"
endef

#-----------------------
#  SHELL COMMANDS 
#-----------------------
RANLIB = ranlib
AR = ar rv
RM = rm -rf
