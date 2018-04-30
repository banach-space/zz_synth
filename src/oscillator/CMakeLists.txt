add_library(oscillator
  ${CMAKE_CURRENT_SOURCE_DIR}/oscillator.cc)

target_include_directories(oscillator PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
