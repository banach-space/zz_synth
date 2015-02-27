#=============================================================
# FILE:
#   inclue/compiler_flags_clang.mk 
#
# AUTHOR:
#   zimzum@github 
#
# DESCRIPTION:
#   Compiler flags when using Clang
#
# License: GNU GPL v2.0 
#=============================================================
#------------------------
#  PEDANTIC (very strict) 
#------------------------
CPPFLAGS_PEDANTIC += -Weverything -Wno-c++98-compat
#------------------------
#  EXTRA DEBUGGING INFO
#------------------------
CPPFLAGS_DEBUG += -g -ggdb
