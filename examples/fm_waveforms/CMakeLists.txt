add_executable(fm_waveforms
  ${CMAKE_CURRENT_SOURCE_DIR}/fm_waveforms.cc)

target_link_libraries(fm_waveforms PRIVATE
  common
  global
  envelope
  oscillator)

target_include_directories(fm_waveforms PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

# TODO Should be a parameter rather than hard-coded
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/examples/fm_waveforms/sounds")
