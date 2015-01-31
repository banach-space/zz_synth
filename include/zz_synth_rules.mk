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
CPPFLAGS = $(OPTFLAG) -std=c++11

ifeq "$(COMPILE_FLAGS)" "PEDANTIC"
#CPPFLAGS += -Wall -pedantic -Wextra
CPPFLAGS += -pedantic -Wall -Wextra -Wcast-align -Wcast-qual\
   	-Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self\
   	-Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept\
   	-Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow\
   	-Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5\
   	-Wswitch-default -Wundef -Werror -Wno-unused
$(info Pedantic compile flags...)
endif

INCLUDES    = -I $(ZZINC)
CXX         = g++
COMPILE.cpp = $(CXX) $(CFLAGS) $(INCLUDES) $(CPPFLAGS) $(TARGET_ARCH) -c

# The following are extra include flags needed by the Google Unit Testing
# framework.
INCLUDES_UT = -lgtest -lgtest_main -lpthread

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
	$(COMPILE.cpp) $< -o $@

$(library): $(object_files)
	@echo $<
	@echo $(source_files)
	$(AR) $@ $^
	@$(RANLIB) $@

$(testbench): $(object_files) $(libraries)
	$(LINK.cc) $(INCLUDES_UT) $^ -o $@
