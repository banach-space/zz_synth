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
#   the components of the library. 
#
#   -------------------------------------
#   [1] Sample usage
#   -------------------------------------
#   To build type the following in the root directory:
#
#   ~/zz_synth$ make [sub-directory to build]
#
#   All output is moved to the bin/ (binary files) and lib/ (libraries)
#	sub-directories. 
#	
#   -------------------------------------
#   [2] The type of the target 
#   -------------------------------------
#   To specify the target type define TARGET when invoking make,
#   for example:
#
#   ~/zz_synth$ make [sub-directory to build] TARGET=target_type
#
#   target_type can be any of:
#       - clean		(deletes existing binaries/libraries)
#       - all		(builds everything + chkdirs)
#       - new		(clean+all)
#       - chkdirs   (creates sub-directories for output, e.g. wave files) 
#
#   Note that some targets (e.g. those in the examples sub-directory)
#   require sub-directories for output. These directories are created
#   with the 'TARGET=chkdirs' flag. You can also pass 'TARGET=all', which
#   will build the corresponding target and create sub-directories if
#   required.
#
#   -------------------------------------
#   [3] Recursive make clean and make all 
#   -------------------------------------
#   In order to run 'make clean (or all)' recursively, type:
#
#   ~/zz_synth$ make clean_recursively (all_recursively) 
#
#   -------------------------------------
#   [4] Compiler flags 
#   -------------------------------------
#   It is possible to specify compiler flags by defining the 
#   COMPILE_FLAGS variable, for instance:
#
#   ~/zz_synth/$ make [sub-directory to build] COMPILE_FLAGS=compile_flag
#
#   Supported options:
#       - DEBUG		(debug flags)
#       - PEDANTIC	(very harsh and resrtictive compiler flags)
#
#   -------------------------------------
#   [5] Vim tags 
#   -------------------------------------
#   There is one special target defined here, TAGS, that is used for
#   creating a ctags file for Vim. Very useful if Vim is your default
#   editor.
#
# License: GNU GPL v2.0 
#========================================================================
ZZDIR = ~/github/zz_synth

include include/zz_synth.mk

lib_common         := $(ZZSRC)/common
lib_global         := $(ZZSRC)/global
lib_envelope       := $(ZZSRC)/envelope
lib_oscillator     := $(ZZSRC)/oscillator
lib_fm_synthesiser := $(ZZSRC)/fm_synthesiser

libraries      :=	 \
	$(lib_common)	 \
	$(lib_envelope)	 \
	$(lib_global)	 \
	$(lib_oscillator)\
    $(lib_fm_synthesiser)


unit_test_rww := unit_tests/read_write_wav
unit_test_env := unit_tests/envelope
unit_test_seg := unit_tests/segment
unit_test_osc := unit_tests/oscillator
unit_tests    := unit_tests/

example_plain_note         := examples/plain_note
example_ar_envelope_note   := examples/ar_envelope_note
example_adsr_envelope_note := examples/adsr_envelope_note
example_waveforms          := examples/waveforms
example_fm_waveforms       := examples/fm_waveforms
examples                   := examples/

.PHONY:				\
	all				\
	all_recursive	\
	clean_recursive	\
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

all_recursive: $(libraries) $(unit_tests) $(examples)
	@$(build-msg)
	$(MAKE) $^ TARGET=all 

clean_recursive: $(libraries) $(unit_tests)
	@$(build-msg)
	$(MAKE) $^ TARGET=clean 

$(lib_common):
	@$(build-msg)
	$(MAKE) --directory=$@ $(TARGET)
	$(if $(TARGET), $(MAKE) $(TARGET))

$(lib_global):
	@$(build-msg)
	$(MAKE) --directory=$@ $(TARGET)
	$(if $(TARGET), $(MAKE) $(TARGET))

$(lib_envelope):
	@$(build-msg)
	$(MAKE) --directory=$@ $(TARGET)
	$(if $(TARGET), $(MAKE) $(TARGET))

$(lib_oscillator):
	@$(build-msg)
	$(MAKE) --directory=$@ $(TARGET)
	$(if $(TARGET), $(MAKE) $(TARGET))

$(lib_fm_synthesiser):
	@$(build-msg)
	$(MAKE) --directory=$@ $(TARGET)
	$(if $(TARGET), $(MAKE) $(TARGET))

$(unit_test_rww): $(lib_common)
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

$(unit_test_osc): $(libraries)
	@$(build-msg)
	$(MAKE) --directory=$@ $(TARGET)
	$(if $(TARGET), $(MAKE) $(TARGET))

$(example_plain_note): $(libraries)
	@$(build-msg)
	$(MAKE) --directory=$@ $(TARGET)
	$(if $(TARGET), $(MAKE) $(TARGET))

$(example_ar_envelope_note): $(libraries)
	@$(build-msg)
	$(MAKE) --directory=$@ $(TARGET)
	$(if $(TARGET), $(MAKE) $(TARGET))

$(example_adsr_envelope_note): $(libraries)
	@$(build-msg)
	$(MAKE) --directory=$@ $(TARGET)
	$(if $(TARGET), $(MAKE) $(TARGET))

$(example_waveforms): $(libraries)
	echo dupa
	@$(build-msg)
	$(MAKE) --directory=$@ $(TARGET)
	$(if $(TARGET), $(MAKE) $(TARGET))

$(example_fm_waveforms): $(lib_oscillator) $(lib_fm_synthesiser) $(lib_common) $(lib_global)
	@$(build-msg)
	$(MAKE) --directory=$@ $(TARGET)
	$(if $(TARGET), $(MAKE) $(TARGET))

$(lib_common_bin): $(lib_common)

$(lib_global_bin): $(lib_global)

$(lib_envelope_bin): $(lib_envelope)

$(unit_tests): $(unit_test_rww) $(unit_test_env) $(unit_test_seg)

$(examples):\
	$(example_plain_note)\
	$(example_ar_envelope_note)\
	$(example_adrs_envelope)\
	$(example_waveforms)\
	$(example_fm_waveforms)

TAGS: 
	@$(build-msg)
	@find . -type f -name "*.h" -or -name "*.cc" > files_ctags
	@ctags -L files_ctags --language-force=C++ --C++-kinds=+pxf > tags

