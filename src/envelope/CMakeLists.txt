add_library(envelope
  ${CMAKE_CURRENT_SOURCE_DIR}/segment.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/envelope.cc)

target_include_directories(envelope PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../../include)
