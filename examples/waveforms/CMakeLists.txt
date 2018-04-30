add_executable(waveforms
  ${CMAKE_CURRENT_SOURCE_DIR}/waveforms.cc)

target_link_libraries(waveforms PRIVATE
  common
  global
  envelope
  oscillator)

target_include_directories(waveforms PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

# TODO Should be a parameter rather than hard-coded
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/examples/waveforms/sounds")
