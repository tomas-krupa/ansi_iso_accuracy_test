cmake_minimum_required(VERSION 2.8)

function(MDPagesAsGroup content modifiedContent file originalSourcePath)
    get_filename_component(mdExt "${file}" EXT)

    message(STATUS "Changing page ${file}")

    set(result "")
    string(APPEND result "/**\n")

    get_filename_component(mdName "${file}" NAME_WE)
    get_filename_component(mdPath "${file}" DIRECTORY)
    get_filename_component(mdDirectory "${mdPath}" NAME)

    # create group hierarchy
    get_filename_component(mdHierarchy "${mdPath}" DIRECTORY)
    get_filename_component(mdHierarchyName "${mdHierarchy}" NAME)
    set(parentDirectories "")
    while (NOT "" STREQUAL "${mdHierarchy}" AND NOT "src" STREQUAL "${mdHierarchyName}")
        if (EXISTS "${mdHierarchy}/${mdHierarchyName}.mdpage")
            list(APPEND parentDirectories "${mdHierarchyName}")
        elseif (EXISTS "${mdHierarchy}/README.mdpage")
            list(APPEND parentDirectories "${mdHierarchyName}")
        elseif (EXISTS "${mdHierarchy}/ReadMe.mdpage")
            list(APPEND parentDirectories "${mdHierarchyName}")
        elseif (EXISTS "${mdHierarchy}/Readme.mdpage")
            list(APPEND parentDirectories "${mdHierarchyName}")
        elseif (EXISTS "${mdHierarchy}/readme.mdpage")
            list(APPEND parentDirectories "${mdHierarchyName}")
        else()
            break()
        endif()

        get_filename_component(mdHierarchy "${mdHierarchy}" DIRECTORY)
        get_filename_component(mdHierarchyName "${mdHierarchy}" NAME)
    endwhile()

    list(REVERSE parentDirectories)
    set(groupId "g")
    foreach(pd ${parentDirectories})
        string(APPEND groupId "_${pd}")
    endforeach()
    if (NOT "g" STREQUAL "${groupId}")
        string(APPEND result "@ingroup ${groupId}\n")
    endif()

    set(directoryContent "")
    string( TOLOWER "${mdName}" mdNameLowerCase)
    if ("src" STREQUAL "${mdDirectory}" AND ("Main" STREQUAL "${mdName}" OR "readme" STREQUAL "${mdNameLowerCase}"))
        # this main md page
        string(APPEND result "@mainpage\n")
    elseif ("${mdName}" STREQUAL "${mdDirectory}" OR "readme" STREQUAL "${mdNameLowerCase}")
        # this main md page for group
        string(APPEND result "@defgroup ${groupId}_${mdDirectory} ${mdDirectory}\n")
        # get first sentence as brief
        string(REGEX MATCH "[^.\n]+\\." brief "${content}")
        if ("" STREQUAL "${brief}")
            # if it has no sentence, then take first line as brief
            string(REGEX MATCH "[^.\n]+" brief "${content}")
        endif()
        string(APPEND result "@brief ${brief}\n\n")
        # reuse documetation in directory
        string(REGEX REPLACE "^.*/src/" "" relativeDoxygenPath "${mdPath}")
        string(APPEND directoryContent "@dir ${originalSourcePath}/${relativeDoxygenPath}\n")
        string(APPEND directoryContent "@ingroup ${groupId}_${mdDirectory}\n")
        string(APPEND directoryContent "@copybrief ${groupId}_${mdDirectory}\n")
        string(APPEND directoryContent "@copydoc ${groupId}_${mdDirectory}\n")
    endif()

    # replace links to directories in md pages with links to groups
    string(REGEX MATCHALL "\\[[^]]+\\]\\([^)]+\\)" links "${content}")
    #string(REGEX MATCHALL "http" links "${content}")
    if (NOT ""  STREQUAL "${links}")
        list(REMOVE_DUPLICATES links)
        set(directoryLinks "")
        foreach(link ${links})
            if (NOT "${link}" MATCHES "\\(http.*")
                list(APPEND directoryLinks ${link})
            endif()
        endforeach()
        foreach(link ${directoryLinks})
            if("${link}" MATCHES "\\[[^]]+\\]\\(([^)]+)\\)")
                set(DirInPage "${CMAKE_MATCH_1}")
                string(REPLACE "/" "_" DirInPageAsGroup "${DirInPage}")
                string(REPLACE "(${DirInPage})" "(@ref g_${DirInPageAsGroup})" content "${content}")
            endif()
        endforeach()
    endif()


    string(APPEND result "${content}")
    string(APPEND result "\n**/\n")
    string(APPEND result "\n/**\n")
    string(APPEND result "${directoryContent}")
    string(APPEND result "\n**/\n")
    set(${modifiedContent} "${result}" PARENT_SCOPE)
endfunction()
 

