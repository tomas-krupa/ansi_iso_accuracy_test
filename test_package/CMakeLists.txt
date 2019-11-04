cmake_minimum_required(VERSION 2.8.12)
project(test_package)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

find_package(iengine_ansi_iso REQUIRED)
find_package(ansiiso_accuracy_test_lib REQUIRED)

add_executable(test_package test_package.cpp)

target_link_libraries(test_package
        PRIVATE
        ansiiso::accuracy_test_lib)
