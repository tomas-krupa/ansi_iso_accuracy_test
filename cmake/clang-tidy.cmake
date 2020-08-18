
find_program(
  CLANG_TIDY_EXE
  NAMES "clang-tidy"
  DOC "Path to clang-tidy executable"
  )

if(NOT CLANG_TIDY_EXE)
  message(STATUS "clang-tidy not found.")
else()
  option(CLANG_TIDY_ENABLED "Enable clang-tidy" OFF)

  message(STATUS "clang-tidy found: ${CLANG_TIDY_EXE}")
  set(CLANG_TIDY_OPTIONS "-checks= -config= -format-style=file -p=${CMAKE_CURRENT_BINARY_DIR} -fix -fix-errors")

  if(NOT TARGET clang-tidy)
    add_custom_target(clang-tidy)
  endif()
  file(GLOB_RECURSE CLANG_TIDY_SOURCES LIST_DIRECTORIES false "*.cpp" "*.cxx" "*.c" ".cc" ".mm" "*.hpp" "*.hxx" "*.h" "*.cc")
  add_custom_target(
    clang-tidy-${PROJECT_NAME}
    COMMAND "${CLANG_TIDY_EXE}" "${CLANG_TIDY_OPTIONS}" ${CLANG_TIDY_SOURCES}
    WORKING_DIRECTORY ${CMAKE_CURRENT_PROJECT_DIR}
    COMMENT "Applying clang-tidy to project: ${PROJECT_NAME}"
  )
  add_dependencies(clang-tidy clang-tidy-${PROJECT_NAME})
endif()

# Use clang tidy to report issues when compiling
if(CLANG_TIDY_ENABLED)
  set(CMAKE_CXX_CLANG_TIDY "${CLANG_TIDY_EXE}" ${CLANG_TIDY_OPTIONS})
else()
  unset(CMAKE_CXX_CLANG_TIDY)
endif()
