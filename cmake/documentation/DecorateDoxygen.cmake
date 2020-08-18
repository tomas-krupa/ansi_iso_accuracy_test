cmake_minimum_required(VERSION 2.8)

if ("" STREQUAL "${FILE_TO_CHECK}")
    math(EXPR fileArgIndex "${CMAKE_ARGC} - 1")
    set(FILE_TO_CHECK ${CMAKE_ARGV${fileArgIndex}})
endif()    

if("" STREQUAL "${FILE_TO_CHECK}" OR NOT EXISTS ${FILE_TO_CHECK})
    return()
endif()

if (NOT "" STREQUAL "${ConfigFile}")
    include("${ConfigFile}" OPTIONAL)
endif()    

include(${DOCUMENTATION_SCRIPTS_ROOT_DIR}/DecoratePlantUMLForDoxygen.cmake)
include(${DOCUMENTATION_SCRIPTS_ROOT_DIR}/DecorateRemoveDeletedFunctions.cmake)

# get file content
file(READ ${FILE_TO_CHECK} content)

DecoratePlantUML("${content}" modifiedContent "${PlantUmlStyle}")
DecorateRemoveDeletedFunctions("${modifiedContent}" modifiedContent)

set(begin 0)
string(LENGTH "${modifiedContent}" mcLength)
string(SUBSTRING "${modifiedContent}" ${begin} 2000 part)
if(WIN32)
    # replace LF with CR, otherwise on windows empty lines are added
    string(REPLACE "\n" "\r" part "${part}")
endif()
while(NOT "" STREQUAL "${part}")
    execute_process(COMMAND ${CMAKE_COMMAND} -E echo_append "${part}")
    math(EXPR begin "${begin} + 2000")
    if(${begin} GREATER ${mcLength})
        set(part "")
    else()
        string(SUBSTRING "${modifiedContent}" ${begin} 2000 part)
        if(WIN32)
            # replace LF with CR, otherwise on windows empty lines are added
            string(REPLACE "\n" "\r" part "${part}")
        endif()        
    endif()
endwhile()    
 

