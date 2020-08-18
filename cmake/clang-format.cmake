find_program(
  CLANG_FORMAT_EXE
  NAMES "clang-format"
  DOC "Path to clang-format executable"
  )

if(NOT CLANG_FORMAT_EXE)
  message(STATUS "clang-format not found.")
else()
  message(STATUS "clang-format found: ${CLANG_FORMAT_EXE}")
  if(NOT TARGET clang-format)
    add_custom_target(clang-format)
  endif()
  file(GLOB_RECURSE CLANG_FORMAT_SOURCES LIST_DIRECTORIES false "*.cpp" "*.cxx" "*.c" ".cc" ".mm" "*.hpp" "*.hxx" "*.h" "*.cc")
  add_custom_target(
    clang-format-${PROJECT_NAME}
    COMMAND ${CLANG_FORMAT_EXE} -i -style=file ${CLANG_FORMAT_SOURCES}
    WORKING_DIRECTORY ${CMAKE_CURRENT_PROJECT_DIR}
    COMMENT "Applying clang-format to project: ${PROJECT_NAME}"
  )
  add_dependencies(clang-format clang-format-${PROJECT_NAME})
endif()
