add_executable(plain_note
  ${CMAKE_CURRENT_SOURCE_DIR}/plain_note.cc)

target_link_libraries(plain_note PRIVATE
  common
  global
  envelope
  oscillator)

target_include_directories(plain_note PRIVATE
  ${CMAKE_CURRENT_SOURCE_DIR}/../../include)

# TODO Should be a parameter rather than hard-coded
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/examples/plain_note/sounds")
