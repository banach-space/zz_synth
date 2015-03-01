#=============================================================
# FILE:
#   inclue/compiler_flags_clang.mk 
#
# AUTHOR:
#   zimzum@github 
#
# DESCRIPTION:
#   Compiler flags when using Clang. Some flags are switched off,
#   which reflects the fact that at this stage I'm not too bothered
#   about performance and memory penalties.
#
# License: GNU GPL v2.0 
#=============================================================
#------------------------
#  PEDANTIC (very strict) 
#------------------------
# The following flags are switched off:
#   (1) exit-time-destructors: the SynthConfig class is implemented as
#       Singleton, so it has a static data member for withc an exit-time-destructor
#       is called. This is acceptable.
#   (2) c++98-compat: Don't care about c++98 compability, not working with
#       legacy code.
#   (3) unused-private-field: SynthConfig has some private fields which are
#       not yet used. Leave it for now.
#   (4) padded: Don't care about padding
#   (5) global-constructor: Gtest and Gmock uses them and I don't worry about
#       performance penalties yet.

CPPFLAGS_PEDANTIC = -Weverything -Wno-exit-time-destructors -Wno-c++98-compat -Wno-unused-private-field -Wno-padded -Wno-global-constructors

#------------------------
#  EXTRA DEBUGGING INFO
#------------------------
CPPFLAGS_DEBUG = -g -ggdb
