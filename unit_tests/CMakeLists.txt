add_executable(UnitSynth
  ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/src/gtest-all.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/source/main.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/source/envelope.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/source/oscillator.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/source/fm_synthesiser.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/source/read_write_wav.cc
  ${CMAKE_CURRENT_SOURCE_DIR}/source/segment.cc)

target_include_directories(UnitSynth PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../include
  ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/
  ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googlemock/include
  ${CMAKE_CURRENT_SOURCE_DIR}/googletest/googletest/include)

target_link_libraries(UnitSynth PRIVATE
  common
  global
  envelope
  fm_synthesiser
  oscillator)

if(UNIX)
  target_link_libraries(UnitSynth PRIVATE pthread dl)
endif()
