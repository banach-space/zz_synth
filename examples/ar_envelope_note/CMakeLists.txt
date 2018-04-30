add_executable(ar_envelope_note
  ${CMAKE_CURRENT_SOURCE_DIR}/ar_envelope_note.cc)

target_link_libraries(ar_envelope_note PRIVATE
  common
  global
  envelope
  oscillator)

target_include_directories(ar_envelope_note PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

# TODO Should be a parameter rather than hard-coded
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/examples/ar_envelope_note/sounds")
