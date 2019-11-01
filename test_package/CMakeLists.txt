cmake_minimum_required(VERSION 2.8.12)
project(test_package)

set(CMAKE_VERBOSE_MAKEFILE "OFF" CACHE BOOL "Verbose build output")

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(ansi-iso-accuracy-test REQUIRED)

add_executable(${PROJECT_NAME} test_package.cpp)

target_link_libraries(${PROJECT_NAME}
        PRIVATE
        ansiiso::accuracy_test_lib)