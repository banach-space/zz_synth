add_executable(adsr_envelope_note
  ${CMAKE_CURRENT_SOURCE_DIR}/adsr_envelope_note.cc)

target_link_libraries(adsr_envelope_note PRIVATE
  common
  global
  envelope
  oscillator)

target_include_directories(adsr_envelope_note PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

# TODO Should be a parameter rather than hard-coded
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/examples/adsr_envelope_note/sounds")
