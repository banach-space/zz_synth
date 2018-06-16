cmake_minimum_required(VERSION 3.4.3 FATAL_ERROR)

project(andrzej_pa)

set(COMPILER_OPTIONS_GNU -Wall -Wno-error=sign-compare -std=c++11 -fPIC)
set(COMPILER_OPTIONS_CLANG -Wall -Wno-error=sign-compare -std=c++11 -fPIC
  -fcolor-diagnostics -Wno-overloaded-virtual -Wno-unused-private-field
  -D__STDC_CONSTANT_MACROS -D__STDC_LIMIT_MACROS)

add_compile_options(
  "$<$<CXX_COMPILER_ID:GNU>:${COMPILER_OPTIONS_GNU}>"
  "$<$<CXX_COMPILER_ID:Clang>:${COMPILER_OPTIONS_CLANG}>")

add_executable(andrzej_pa
  ${CMAKE_CURRENT_SOURCE_DIR}/callback.cpp)

target_include_directories(andrzej_pa PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../../portaudio/include)

find_library(PARTAUDIO_LIB portaudio HINTS ${CMAKE_CURRENT_SOURCE_DIR}/../../portaudio/build)
target_link_libraries(andrzej_pa PUBLIC ${PARTAUDIO_LIB})

find_library(NCURSES ncurses)
target_link_libraries(andrzej_pa PUBLIC ${NCURSES})
