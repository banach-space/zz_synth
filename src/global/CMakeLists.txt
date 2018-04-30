add_library(global
  ${CMAKE_CURRENT_SOURCE_DIR}/global_variables.cc)

target_include_directories(global PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
