#========================================================================
# FILE:
#   Makefile
#
# AUTHOR:
#   zimzum@github 
#
# DESCRIPTION:
#   The master Makefile script for the zz_synth library. The build
#   system for for this synthesiser is recursive and this is the top
#   script that should be invoked whenever trying to build any of
#   the components of the library. Sample usage:
#
#   ~/zz_synth$ make [sub-directory to build]
#
#   All output is moved to the bin/ sub-directory. Target type can be
#   specified by defining the TARGET variable, for example:
#
#   ~/zz_synth$ make [sub-directory to build] TARGET=target_type
#
#   Target type can be any of:
#       - new
#       - clean
#       - all
#
#   It is also possible to specify compiler flags by defining the 
#   COMPILE_FLAGS variable, for instance:
#
#   ~/zz_synth/$ make [sub-directory to build] COMPILE_FLAGS=compile_flag
#
#   Compile flag can be any of:
#       - PEDANTIC
#       - DEBUG
#
#   There is one special target defined here, TAGS, that is used for
#   creating a ctags file for Vim. Very useful if Vim is your default
#   editor.
#
# License: GNU GPL v2.0 
#========================================================================
ZZDIR = ~/github/zz_synth
include include/zz_synth.mk

lib_common     := src/common
libraries      := $(lib_common)
lib_common_bin := $(lib_common)/libcommon.a

unit_test_rww := unit_tests/read_write_wav
unit_test_env := unit_tests/envelope
unit_test_seg := unit_tests/segment
unit_tests    := unit_tests/

.PHONY:				\
	all				\
	new				\
	$(libraries)	\
	$(lib_common)	\
	TAGS			\
	clean			

#-----------------------
#  TARGETS 
#-----------------------
clean new:
	@$(build-msg)
	#@printf "#\n# [Make:] Root directory, nothing to clean\\ build.\n#\n"

$(lib_common):
	@$(build-msg)
	$(MAKE) --directory=$@ $(TARGET)
	$(if $(TARGET), $(MAKE) $(TARGET))

$(unit_test_rww): $(libraries)
	@$(build-msg)
	$(MAKE) --directory=$@ $(TARGET)
	$(if $(TARGET), $(MAKE) $(TARGET))

$(unit_test_env): $(libraries)
	@$(build-msg)
	$(MAKE) --directory=$@ $(TARGET)
	$(if $(TARGET), $(MAKE) $(TARGET))

$(unit_test_seg): $(libraries)
	@$(build-msg)
	$(MAKE) --directory=$@ $(TARGET)
	$(if $(TARGET), $(MAKE) $(TARGET))

$(lib_common_bin): $(lib_common)

$(unit_tests): $(unit_test_rww) $(unit_test_env) $(unit_test_seg)

TAGS: 
	@$(build-msg)
	@find . -type f -name "*.h" -or -name "*.cc" > files_ctags
	@ctags -L files_ctags --language-force=C++ --C++-kinds=+pxf > tags

