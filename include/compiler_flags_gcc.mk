#=============================================================
# FILE:
#   include/compiler_flags_gcc.mk 
#
# AUTHOR:
#   zimzum@github 
#
# DESCRIPTION:
#   Compiler flags when using GCC 
#
# License: GNU GPL v2.0 
#=============================================================
#------------------------
#  PEDANTIC (very strict) 
#------------------------
CPPFLAGS_PEDANTIC += -pedantic -Wall -Wextra -Wcast-align -Wcast-qual\
   	-Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self\
   	-Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept\
   	-Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow\
   	-Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5\
   	-Wswitch-default -Wundef -Werror -Wno-unused

#------------------------
#  EXTRA DEBUGGING INFO
#------------------------
CPPFLAGS_DEBUG += -g -ggdb
