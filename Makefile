#=============================================================
# FILE:
#   Makefile
#
# AUTHOR:
#   zimzum@github 
#
# DESCRIPTION:
#   The master Makefile
#
# License: GNU GPL v2.0 
#=============================================================
ZZDIR = ~/github/zz_synth
include include/zz_synth.mk

lib_common  := src/common
libraries   := $(lib_common)

.PHONY: all $(libraries) $(lib_common) TAGS build_msg

$(lib_common):
	@$(build-msg)
	$(MAKE) --directory=$@ $(TARGET)
	$(if $(TARGET), $(MAKE) $(TARGET))

# Tags for Vim
TAGS: 
	@$(build-msg)
	@find . -type f -name "*.h" -or -name "*.cc" > files_ctags
	@ctags -L files_ctags --language-force=C++ --C++-kinds=+pxf > tags
