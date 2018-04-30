add_executable(testbench_fm_synthesiser
  ${CMAKE_CURRENT_SOURCE_DIR}/../googletest/googletest/src/gtest-all.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/testbench.cc)

target_include_directories(testbench_fm_synthesiser PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../../include
  ${CMAKE_CURRENT_SOURCE_DIR}/../googletest/googletest/
  ${CMAKE_CURRENT_SOURCE_DIR}/../googletest/googlemock/include
  ${CMAKE_CURRENT_SOURCE_DIR}/../googletest/googletest/include)

target_link_libraries(testbench_fm_synthesiser PRIVATE
  common
  global
  fm_synthesiser
  oscillator)

if(UNIX)
  target_link_libraries(testbench_fm_synthesiser PRIVATE pthread dl)
endif()
