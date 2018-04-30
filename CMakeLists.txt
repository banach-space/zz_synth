cmake_minimum_required(VERSION 3.4.3 FATAL_ERROR)

project(zz_synth)

set(COMPILER_OPTIONS_GNU -Wall -Wno-error=sign-compare -std=c++11 -fPIC)
set(COMPILER_OPTIONS_CLANG -Wall -Wno-error=sign-compare -std=c++11 -fPIC
  -fcolor-diagnostics -Wno-overloaded-virtual -Wno-unused-private-field
  -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS)

add_compile_options(
  "$<$<CXX_COMPILER_ID:GNU>:${COMPILER_OPTIONS_GNU}>"
  "$<$<CXX_COMPILER_ID:Clang>:${COMPILER_OPTIONS_CLANG}>")

add_subdirectory(src)
add_subdirectory(unit_tests)
add_subdirectory(examples)
