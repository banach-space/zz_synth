add_executable(testbench_segment
  ${CMAKE_CURRENT_SOURCE_DIR}/../googletest/googletest/src/gtest-all.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/testbench.cc)

target_include_directories(testbench_segment PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../../include
  ${CMAKE_CURRENT_SOURCE_DIR}/../googletest/googletest/
  ${CMAKE_CURRENT_SOURCE_DIR}/../googletest/googlemock/include
  ${CMAKE_CURRENT_SOURCE_DIR}/../googletest/googletest/include)

target_link_libraries(testbench_segment PRIVATE
  common
  global
  envelope
  oscillator)

if(UNIX)
  target_link_libraries(testbench_segment PRIVATE pthread dl)
endif()
