cmake_minimum_required(VERSION 2.8)

function(DecorateRemoveDeletedFunctions content modifiedContent)

    set(lines "")
    string(REPLACE ";" "_^_" lines "${content}")
    string(REPLACE "\n" ";" lines "${content}")
    set(linesWithoutDeletedFunctions "")
    foreach(line ${lines})
        if (NOT "${line}" MATCHES ".*=[ \t]*(delete|default)[ \t]*$")
            list(APPEND linesWithoutDeletedFunctions "${line}")
        endif()
    endforeach()
    string(REPLACE ";" "\n" linesWithoutDeletedFunctions "${linesWithoutDeletedFunctions}")
    string(REPLACE "_^_" ";" linesWithoutDeletedFunctions "${linesWithoutDeletedFunctions}")

    set(${modifiedContent} "${linesWithoutDeletedFunctions}" PARENT_SCOPE)
endfunction()
 

