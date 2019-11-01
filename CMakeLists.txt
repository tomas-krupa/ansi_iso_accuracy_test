cmake_minimum_required(VERSION 3.10)

project("ANSI&ISO Accuracy Test" VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(ANSIISO_ACCURACY_TEST_ENABLE_UNIT_TESTS ON CACHE BOOL "Perform unit tests of the application")
set(ANSIISO_ACCURACY_TEST_ENABLE_STATIC_ANALYSIS ON CACHE BOOL "Perform static analyse of the application")

set(ANSSIISO_ACCURACY_TEST_PRODUCT_STRING "${PROJECT_NAME} v${PROJECT_VERSION}" CACHE STRING "Product string")
set(ANSSIISO_ACCURACY_TEST_ABI_VERSION "${PROJECT_NAME}-${PROJECT_VERSION_MAJOR}" CACHE STRING "ABI version")
string(REGEX REPLACE "[&, ]" "_" ANSSIISO_ACCURACY_TEST_ABI_VERSION ${ANSSIISO_ACCURACY_TEST_ABI_VERSION})

if(EXISTS ${CMAKE_CURRENT_BINARY_DIR}/conan_paths.cmake)
    message("Detected Conan-powered build")
    include(${CMAKE_CURRENT_BINARY_DIR}/conan_paths.cmake)
endif()

configure_file(src/config.hpp.in config.hpp @ONLY)

find_package(iengine_ansi_iso REQUIRED)

#########################################################
######################### BUILD #########################
#########################################################

add_library(ansiiso_accurracy_test_lib STATIC
    src/Application.cpp )

add_library(ansiiso::accuracy_test_lib ALIAS ansiiso_accurracy_test_lib)

target_link_libraries(ansiiso_accurracy_test_lib PRIVATE iengine_ansi_iso::iengine_ansi_iso)

target_include_directories(ansiiso_accurracy_test_lib
    PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:include>)

add_executable(ansiiso_accurracy_test
    src/Main.cpp)

target_link_libraries(ansiiso_accurracy_test PRIVATE ansiiso::accuracy_test_lib)

install(TARGETS ansiiso_accurracy_test RUNTIME DESTINATION bin COMPONENT runtime)
install(TARGETS ansiiso_accurracy_test_lib EXPORT ansiiso_accurracy_test_lib-targets DESTINATION lib)

# Export targets
include(CMakePackageConfigHelpers)
install(EXPORT ansiiso_accurracy_test_lib-targets
  FILE ansiiso_accurracy_test_lib-targets.cmake
  NAMESPACE ansiiso::
  DESTINATION lib/cmake/ansiiso_accurracy_test_lib)

#########################################################
######################### TEST #########################
#########################################################

if (ANSIISO_ACCURACY_TEST_ENABLE_UNIT_TESTS)

    find_package(Catch2 QUIET)

    if (Catch2_FOUND)
        message(STATUS "Catch2 - FOUND")
        enable_testing()

        add_test(NAME ansiiso_accuracy_unit_test_base
            SOURCES          test/TestMain.cpp
            COMMAND $<TARGET_FILE:ansiiso_accuracy_unit_test_base>
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/test/assets)

        target_link_libraries(ansiiso_accuracy_unit_test_base PRIVATE ansiiso::accuracy_test_lib Catch2::Catch2)
        target_include_directories(ansiiso_accuracy_unit_test_base PRIVATE
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/test>)
        install(TARGETS ansiiso_accuracy_unit_test_base RUNTIME DESTINATION bin/test COMPONENT test)

    else()
        message(STATUS "Catch2 - NOT FOUND")
    endif()
endif()

#########################################################
######################### PACK ##########################
#########################################################

set(CPACK_PACKAGE_VENDOR "Innovatrics")
set(CPACK_SYSTEM_NAME "${CMAKE_SYSTEM_NAME}.x86_64")
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Accuracy ad performmace bechmark tool for Innovatrics ANSI&ISO SDK.")
set(CPACK_PACKAGE_MAINTAINER "tomas.krupa@innovatrics.com")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.${CPACK_PACKAGE_VERSION_PATCH}-${CPACK_SYSTEM_NAME}")
set(CPACK_MONOLITHIC_INSTALL ON)
set(CPACK_STRIP_FILES yes)

set(CPACK_INSTALL_CMAKE_PROJECTS
    ${CMAKE_BINARY_DIR}    ${PROJECT_NAME}  "runtime"       "/"
    ${CMAKE_BINARY_DIR}    ${PROJECT_NAME}  "post-runtime"  "/"
    ${CMAKE_BINARY_DIR}    ${PROJECT_NAME}  "documentation" "/")

if(UNIX)
    set(CPACK_GENERATOR TBZ2)
    set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt)
endif()

install(FILES CHANGELOG.md DESTINATION doc COMPONENT documentation)
install(FILES README.md DESTINATION . COMPONENT documentation)

include(CPack)