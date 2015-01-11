#=============================================================
# FILE:
#   inclue/zz_synth_rules.mk 
#
# AUTHOR:
#   zimzum@github 
#
# DESCRIPTION:
#   Implicit (and directly related variables) rules used in the
#   build system for the zz_synth library. Include this file
#	after the definition of source_files. Otherwise the implict
#	rules will be expanded with object_files, which depend on
#	source_files, yet undefined.
#
#	When building targets pass COMPILE_FLAGS=PEDANTIC option to
#	turn on very strict compiler checks.
#
# License: GNU GPL v2.0 
#=============================================================
#-----------------------
#  COMPILATION VARIABLES 
#-----------------------
CPPFLAGS = $(OPTFLAG)

ifeq "$(COMPILE_FLAGS)" "PEDANTIC"
CPPFLAGS += -Wall -pedantic
$(info Pedantic compile flags...)
endif

INCLUDES    = -I $(ZZINC)
CXX         = g++
COMPILE.cpp = $(CXX) $(CFLAGS) $(INCLUDES) $(CPPFLAGS) $(TARGET_ARCH) -c

#-----------------------
#  SHELL COMMANDS 
#-----------------------
RANLIB  = ranlib
AR      = ar rv
RM      = rm -rf
MKDIR   = mkdir -p

#-----------------------
#  IMPLICIT RULES 
#-----------------------
%.o: %.cc
	@echo Compiling $<
	$(COMPILE.cpp) $<

$(ZZBIN)/%.o: %.cc
	@echo Compiling $<
	@echo $(INCLUDES) 
	$(COMPILE.cpp) $< -o $@

$(library): $(object_files)
	@echo $<
	@echo $(source_files)
	$(AR) $@ $^
	@$(RANLIB) $@

$(testbench): $(object_files) $(libraries)
	$(LINK.cc) $^ -o $@
