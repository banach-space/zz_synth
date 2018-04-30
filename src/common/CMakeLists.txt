add_library(common
  ${CMAKE_CURRENT_SOURCE_DIR}/wave_file.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/synth_config.cc)

target_include_directories(common PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
