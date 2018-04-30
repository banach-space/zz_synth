add_library(fm_synthesiser
  ${CMAKE_CURRENT_SOURCE_DIR}/fm_synthesiser.cc)

target_include_directories(fm_synthesiser PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
