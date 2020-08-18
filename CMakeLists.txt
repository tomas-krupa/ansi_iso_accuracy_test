cmake_minimum_required(VERSION 3.10)

project("ansiiso_accuracy_test"
        DESCRIPTION "Innovatrics ANSI&ISO accuracy and performance test"
        HOMEPAGE_URL "git remote add origin https://github.com/tomas-krupa/ansi_iso_accuracy_test"
        VERSION 0.0.1
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(ANSIISO_ACCURACY_TEST_ENABLE_UNIT_TESTS ON
        CACHE BOOL "Perform unit tests of the application")
set(ANSIISO_ACCURACY_TEST_ENABLE_STATIC_ANALYSIS ON
        CACHE BOOL "Perform static analyse of the application")

set(ANSSIISO_ACCURACY_TEST_PRODUCT_STRING
        "${PROJECT_NAME} v${PROJECT_VERSION}" CACHE STRING "Product string")
set(ANSSIISO_ACCURACY_TEST_ABI_VERSION
        "${PROJECT_NAME}-${PROJECT_VERSION_MAJOR}" CACHE STRING "ABI version")
string(REGEX REPLACE "[&, ]" "_"
        ANSSIISO_ACCURACY_TEST_ABI_VERSION ${ANSSIISO_ACCURACY_TEST_ABI_VERSION})

if (EXISTS ${CMAKE_CURRENT_BINARY_DIR}/conan_paths.cmake)
    message(STATUS "Running Conan-powered build")
    include(${CMAKE_CURRENT_BINARY_DIR}/conan_paths.cmake)
else ()
    message(FATAL_ERROR "No Conan paths found")
endif ()

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_LIST_DIR}/cmake)

include(clang-format)
include(clang-tidy)

configure_file(src/config.hpp.in innovatrics/config.hpp @ONLY)
list(APPEND EXPORT_HEADERS
        ${CMAKE_CURRENT_BINARY_DIR}/innovatrics/config.hpp)

find_package(iengine_ansi_iso REQUIRED)
find_package(Boost REQUIRED COMPONENTS log filesystem system iostreams program_options)

#########################################################
######################### BUILD #########################
#########################################################

add_library(accuracy_test_lib INTERFACE)
add_library(ansiiso::accuracy_test_lib ALIAS accuracy_test_lib)

target_link_libraries(accuracy_test_lib
        INTERFACE
        iengine_ansi_iso::iengine_ansi_iso)

target_include_directories(accuracy_test_lib
        INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
        $<INSTALL_INTERFACE:include>)

set(ansiiso_accuracy_test_SOURCES
        src/AnsiIso/AnsiIso.cpp
        src/Application.cpp
)

add_executable(ansiiso_accuracy_test
        src/Main.cpp
        ${ansiiso_accuracy_test_SOURCES}
        )

target_link_libraries(ansiiso_accuracy_test
        PRIVATE
        ansiiso::accuracy_test_lib
        Boost::program_options
        Boost::log
        Boost::iostreams
        )

list(APPEND EXPORT_HEADERS
        ${CMAKE_CURRENT_SOURCE_DIR}/include/innovatrics/ansiiso.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/include/innovatrics/ansiiso_accuracy_test.hpp)

install(TARGETS ansiiso_accuracy_test
        RUNTIME DESTINATION bin
        COMPONENT runtime)

install(TARGETS accuracy_test_lib
        EXPORT ansiiso_accuracy_test_lib-targets
        DESTINATION include
        COMPONENT development)

# Export targets
include(CMakePackageConfigHelpers)
install(EXPORT ansiiso_accuracy_test_lib-targets
        FILE ansiiso_accuracy_test_lib-targets.cmake
        NAMESPACE ansiiso::
        DESTINATION lib/cmake/ansiiso_accuracy_test_lib
        COMPONENT development)

write_basic_package_version_file(ansiiso_accuracy_test_lib-config-version.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion)

configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/cmake/ansiiso_accuracy_test_lib-config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/ansiiso_accuracy_test_lib-config.cmake
        INSTALL_DESTINATION lib/cmake/ansiiso_accuracy_test_lib)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/ansiiso_accuracy_test_lib-config.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/ansiiso_accuracy_test_lib-config-version.cmake
        DESTINATION lib/cmake/ansiiso_accuracy_test_lib
        COMPONENT development)

#########################################################
######################### TEST ##########################
#########################################################

if (ANSIISO_ACCURACY_TEST_ENABLE_UNIT_TESTS)

    find_package(Catch2 QUIET)

    if (Catch2_FOUND)
        message(STATUS "Catch2 - FOUND")

        enable_testing()

        add_subdirectory(test)
    else ()
        message(STATUS "Catch2 - NOT FOUND")
    endif ()
endif ()

#########################################################
##################### DOCUMENTATION #####################
#########################################################

include(documentation/TargetDocumentation)

add_documentation(
    Type development
    Targets accuracy_test_lib
    AddIssuesLinks
    Config Key INPUT      			  Value ${CMAKE_CURRENT_SOURCE_DIR}/src
    Config Key EXAMPLE_PATH           Value ${CMAKE_CURRENT_SOURCE_DIR}/src
    Config Key LAYOUT_FILE            Value ${CMAKE_CURRENT_SOURCE_DIR}/res/development.xml
    Config Key JAVADOC_AUTOBRIEF      Value YES
    Config Key INTERNAL_DOCS          Value YES
    Config Key EXTRACT_PRIVATE        Value NO
    Config Key GENERATE_LATEX         Value YES

    Config Key EXTRACT_STATIC         Value YES
    Config Key HIDE_UNDOC_MEMBERS     Value NO
    Config Key HIDE_UNDOC_CLASSES     Value NO
    Config Key HIDE_SCOPE_NAMES       Value YES
    Config Key SHOW_INCLUDE_FILES     Value YES
    Config Key GENERATE_TODOLIST      Value YES
    Config Key SHOW_USED_FILES        Value YES
    Config Key SHOW_FILES             Value YES
    Config Key SHOW_NAMESPACES        Value NO
    Config Key REFERENCES_LINK_SOURCE Value YES
    Config Key REFERENCED_BY_RELATION Value YES
    Config Key REFERENCES_RELATION    Value YES
    Config Key ALPHABETICAL_INDEX     Value NO
    Config Key GENERATE_HTML          Value YES
    Config Key CLASS_DIAGRAMS         Value NO
    Config Key HIDE_UNDOC_RELATIONS   Value YES
    Config Key CLASS_GRAPH            Value NO
    Config Key GROUP_GRAPHS           Value NO
    Config Key UML_LOOK               Value YES
    Config Key UML_LIMIT_NUM_FIELDS   Value 3
    Config Key INCLUDE_GRAPH          Value YES
    Config Key INCLUDED_BY_GRAPH      Value YES
    Config Key DIRECTORY_GRAPH        Value YES
    Config Key CALL_GRAPH             Value YES
    Config Key CALLER_GRAPH           Value YES
    Config Key MAX_DOT_GRAPH_DEPTH    Value 1
    Config Key DOT_TRANSPARENT        Value YES
    Config Key DOT_IMAGE_FORMAT       Value svg
    Config Key INTERACTIVE_SVG        Value YES
    Config Key REPEAT_BRIEF           Value NO
    )

#########################################################
######################### PACK ##########################
#########################################################

set(CPACK_PACKAGE_VENDOR "Innovatrics")
set(CPACK_SYSTEM_NAME "${CMAKE_SYSTEM_NAME}.x86_64")
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY
        "Accuracy ad performance benchmark tool for Innovatrics ANSI&ISO SDK.F")
set(CPACK_PACKAGE_MAINTAINER "tomas.krupa@innovatrics.com")
set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(CPACK_PACKAGE_VERSION_PATCH ${PROJECT_VERSION_PATCH})
set(CPACK_PACKAGE_FILE_NAME
        "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION_MAJOR}.${CPACK_PACKAGE_VERSION_MINOR}.\
        ${CPACK_PACKAGE_VERSION_PATCH}-${CPACK_SYSTEM_NAME}")
set(CPACK_MONOLITHIC_INSTALL ON)
set(CPACK_STRIP_FILES yes)

set(CPACK_INSTALL_CMAKE_PROJECTS
        ${CMAKE_BINARY_DIR} ${PROJECT_NAME} "runtime" "/"
        ${CMAKE_BINARY_DIR} ${PROJECT_NAME} "post-runtime" "/"
        ${CMAKE_BINARY_DIR} ${PROJECT_NAME} "documentation" "/")

if (UNIX)
    set(CPACK_GENERATOR TBZ2)
    set(CPACK_RESOURCE_FILE_LICENSE ${CMAKE_CURRENT_SOURCE_DIR}/LICENSE.txt)
endif ()

install(FILES ${EXPORT_HEADERS} DESTINATION include/innovatrics COMPONENT development)
install(FILES CHANGELOG.md DESTINATION doc COMPONENT documentation)
install(FILES README.md DESTINATION . COMPONENT documentation)

#install(TARGETS documentation DESTINATION doc COMPONENT documentation)
#install(TARGETS documentation-development DESTINATION doc COMPONENT documentation)


include(CPack)