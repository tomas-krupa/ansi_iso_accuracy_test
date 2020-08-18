cmake_minimum_required(VERSION 3.10)

function(add_catch_test TEST_NAME SOURCE_FILE)
    add_executable(${TEST_NAME}
            ${SOURCE_FILE})

    add_test(NAME ${TEST_NAME}
            COMMAND $<TARGET_FILE:${TEST_NAME}>
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/)

    target_link_libraries(${TEST_NAME}
            PRIVATE
            ansiiso::accuracy_test_lib
            Boost::system
            Catch2::Catch2)
    target_include_directories(${TEST_NAME}
            PRIVATE
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>)
    install(TARGETS ${TEST_NAME}
            RUNTIME DESTINATION bin/test
            COMPONENT test)
endfunction()

#########################################################
##################### UNIT TESTS ########################
#########################################################

add_catch_test(ansiiso_accuracy_unit_test_base
        TestBase.cpp)

add_catch_test(ansiiso_accuracy_test_storage
        Storage/Test_FileStorage.cpp)

add_catch_test(ansiiso_accuracy_test_cli_configuration
        Configuration/Test_CLIconfiguration.cpp)

    target_link_libraries(ansiiso_accuracy_test_cli_configuration
            PRIVATE
            Boost::program_options Boost::filesystem)