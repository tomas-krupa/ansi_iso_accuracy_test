cmake_minimum_required(VERSION 3.10)

if (DEFINED TargetDocumentationGuard)
    return()
endif()

set(TargetDocumentationGuard yes)

find_program(DOXYGEN doxygen)
set(DOCUMENTATION_SCRIPTS_ROOT_DIR ${CMAKE_CURRENT_LIST_DIR})

macro(parse_arguments prefix options oneArg multiArg multiOccurrence args)
    cmake_policy(PUSH)
    cmake_policy(SET CMP0054 NEW) # turn off implicit expansions in if statement
    
    set(defaultArgs ${args})
    
    foreach(occurrence ${multiOccurrence})
        set(otherOccurrencies ${multiOccurrence})
        list(REMOVE_ITEM otherOccurrencies ${occurrence})
        set(allOtherArgs ${options} ${oneArg} ${multiArg} ${otherOccurrencies})
            
        set(occurrenceAllOutput "")
        set(occurrenceOutput "")
        set(add no)
        foreach(arg ${defaultArgs})
            if ("${arg}" STREQUAL "${occurrence}")
                if (add)
                    string(REPLACE "${occurrenceOutput}" "" defaultArgs "${defaultArgs}")
                    string(REPLACE ";" "," occurrenceOutput "${occurrenceOutput}")
                    list(APPEND occurrenceAllOutput ${occurrenceOutput})
                    set(occurrenceOutput "")
                endif()
                set(add yes)
            endif()
            
            list(FIND allOtherArgs ${arg} isFound)

            if(isFound EQUAL -1 AND add)
                list(APPEND occurrenceOutput ${arg})
            else()
                if (add)
                    string(REPLACE "${occurrenceOutput}" "" defaultArgs "${defaultArgs}")
                    string(REPLACE ";" "," occurrenceOutput "${occurrenceOutput}")
                    list(APPEND occurrenceAllOutput ${occurrenceOutput})
                    set(add no)
                    set(occurrenceOutput "")
                endif()
            endif()
        endforeach()
        
         if (add)
            string(REPLACE "${occurrenceOutput}" "" defaultArgs "${defaultArgs}")
            string(REPLACE ";" "," occurrenceOutput "${occurrenceOutput}")
            list(APPEND occurrenceAllOutput ${occurrenceOutput})
        endif()
                
        set(${prefix}_${occurrence} ${occurrenceAllOutput})
    endforeach()
    
    cmake_policy(POP)
    
    CMAKE_PARSE_ARGUMENTS(${prefix} "${options}" "${oneArg}" "${multiArg}" "${defaultArgs}")
endmacro()



function(add_documentation)
    # check if coverity is available on system
    if(NOT DOXYGEN)
        message(STATUS "Could not find doxygen. Skipping documentation.")
        return()
    else()
        if(NOT TARGET documentation)
            message(STATUS "Adding documentation target.")
        endif()
    endif()
    
    parse_arguments(doc "AddIssuesLinks;" "AddPlantUmlStyle;FileName;Type" "Targets" "Config" "${ARGN}")
    
    # use doxygen defaults
    include(${DOCUMENTATION_SCRIPTS_ROOT_DIR}/defaultDoxygenConfig.cmake)
    # replace defaults with defaults for this project
    set(DOX_PROJECT_NAME ${PROJECT_NAME})
    set(DOX_PROJECT_NUMBER ${PROJECT_VERSION})
    set(DOX_PROJECT_BRIEF "")
    set(DOX_ALIASES "maintainer=\"@author\" created=\"@date\"")
    set(DOX_OUTPUT_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}/documentation/${doc_Type}/output")
    set(DOX_FILE_PATTERNS "*.page *.c *.cc *.cxx *.cpp *.c++ *.java *.ii *.ixx *.ipp *.i++ *.inl *.idl *.ddl *.odl *.h *.hh *.hxx *.hpp *.h++ *.cs *.d *.php *.php4 *.php5 *.phtml *.inc *.m *.markdown *.md *.mm *.dox *.py *.f90 *.f *.for *.tcl *.vhd *.vhdl *.ucf *.qsf *.as *.js")
    set(DOX_RECURSIVE YES)
    set(DOX_GENERATE_TAGFILE "${CMAKE_CURRENT_BINARY_DIR}/documentation/${doc_Type}/${PROJECT_NAME}.tag")
    set(DOX_LATEX_BATCHMODE yes)
    # create INPUT
    set(DOX_STRIP_FROM_PATH ${CMAKE_CURRENT_SOURCE_DIR})
    set(DOX_EXCLUDE_PATTERNS "*/test/*")
    set(DOX_INPUT "${CMAKE_CURRENT_SOURCE_DIR}")
    # create INCLUDE_PATH but not serach for includes
    set(DOX_ENABLE_PREPROCESSING YES)
    set(DOX_SEARCH_INCLUDES      NO)
    foreach(t ${doc_Targets})
        set(dirs "")
        get_target_property(dirs ${t} INTERFACE_INCLUDE_DIRECTORIES)
        foreach(dir ${dirs})
            if(IS_ABSOLUTE ${dir})
                list(APPEND incDirs ${dir})
            else()
                list(APPEND incDirs ${CMAKE_CURRENT_SOURCE_DIR}/${dir})
            endif()
            list(REMOVE_DUPLICATES incDirs)
        endforeach()
    endforeach()
    
    # not using include paths due to includes in include paths are added after build
    # and up to now they are not relevant for documentation
    #set(DOX_INCLUDE_PATH "\\ \n")
    #foreach(d ${incDirs})
    #    string(CONCAT DOX_INCLUDE_PATH "${DOX_INCLUDE_PATH}" "    ${d} \\ \n")
    #endforeach()
    #string(CONCAT DOX_INCLUDE_PATH "${DOX_INCLUDE_PATH}" "   \n")
    
    # check for macros used by targets
    set(predefined "")
    foreach(t ${doc_Targets})
        set(defines "")
        get_target_property(defines ${t} INTERFACE_COMPILE_DEFINITIONS)
        foreach(d ${defines})
            string(CONCAT predefined "${predefined}" "${d} ")
        endforeach()
    endforeach()    
    get_property(defines DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY COMPILE_DEFINITIONS)
    foreach(d ${defines})
        string(CONCAT predefined "${predefined}" "${d} ")
    endforeach()    
    string(TOUPPER "${CMAKE_BUILD_TYPE}" bt)
    string(CONCAT predefined "${predefined}" "${CMAKE_CXX_FLAGS_${bt}_INIT} ")
    string(REGEX MATCHALL "-[Dd][^ \t]+" predefined "${predefined}")
    string(REGEX REPLACE "-[Dd]" "" predefined "${predefined}") 
    string(REPLACE ";" " " predefined "${predefined}")
    set(DOX_PREDEFINED "${predefined}")
    
    # setup INPUT_FILTER
    set(cmc "${CMAKE_COMMAND}")
    set(script "${DOCUMENTATION_SCRIPTS_ROOT_DIR}/DecorateDoxygen.cmake")
    set(tc "${CMAKE_TOOLCHAIN_FILE}")
    set(mp "${CMAKE_MODULE_PATH}")
    set(id "${DOCUMENTATION_SCRIPTS_ROOT_DIR}")
    set(cf "${CMAKE_CURRENT_BINARY_DIR}/documentation/${doc_Type}/${doc_Type}.cmake")
    
    set(DOX_INPUT_FILTER "\"${cmc}  -DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE} -DCMAKE_TOOLCHAIN_FILE=${tc} -DCMAKE_MODULE_PATH=\\\"${mp}\\\" -DMODULE_PATH=${DOCUMENTATION_SCRIPTS_ROOT_DIR} -DConfigFile=${cf} -P ${script}\"")

    find_program(DOT dot)
    if(DOT)
        set(DOX_HAVE_DOT YES)
    endif()
    # replace defaults and also project defaults with given configuration pairs
    foreach(cfg ${doc_Config})
        # get config info
        string(REPLACE "," ";" cfgDesc "${cfg}")
        cmake_parse_arguments(c "" "Key" "Value" "" "${cfgDesc}")
        # quoted values when contains spaces
        set(quotedValues "")
        foreach(v ${c_Value})
            # replace " with \" to provide compatible input for doxygen
            string(REPLACE "\"" "\\\"" v "${v}")
            if("${v}" MATCHES ".* .*")
                string(CONCAT quotedValues "${quotedValues}" "\"${v}\" ")
            else()
                string(CONCAT quotedValues "${quotedValues}" "${v} ")
            endif() 
        endforeach()
        string(STRIP "${quotedValues}" quotedValues)
        set(DOX_${c_Key} "${quotedValues}")
    endforeach()
    
    set(TAGSFILE "${CMAKE_CURRENT_BINARY_DIR}/documentation/${doc_Type}/${PROJECT_NAME}.tag")
    set(OUTPUTDIR "${DOX_OUTPUT_DIRECTORY}")
    set(HTMLOUTPUTDIR "")
    if (DOX_GENERATE_HTML)
        set(HTMLOUTPUTDIR "${DOX_OUTPUT_DIRECTORY}/html")
    endif()
    if (DOX_GENERATE_LATEX)
        set(PDFOUTPUTDIR "${DOX_OUTPUT_DIRECTORY}/pdf")
        set(PDFNAME ${doc_FileName}.pdf)
    endif()    
    set(TYPE ${doc_Type})
    
    configure_file(${DOCUMENTATION_SCRIPTS_ROOT_DIR}/DocumentationConfig.in ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Documentation_${doc_Type}Config.cmake @ONLY)
    set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}Documentation_${doc_Type}Config.cmake)
    
    # if config file is given, then configure it.
    # Following variables can be used
    # - History
    # - Reviewer
    # - Releaser
    if(NOT "" STREQUAL "${DOX_LATEX_HEADER}")
        set(History "")
        set(Author "")
        set(Reviewer "")
        string(CONCAT History "${History}" " & & & \\\\\n")

        # unquote 
        configure_file(${DOX_LATEX_HEADER} "${CMAKE_CURRENT_BINARY_DIR}/documentation/${doc_Type}/latex_header.tex" @ONLY)
        set(DOX_LATEX_HEADER ${CMAKE_CURRENT_BINARY_DIR}/documentation/${doc_Type}/latex_header.tex)
    endif()
    
    # store data for finalazing doxygen configuration
    set(Type ${doc_Type})
    set(OutputFileName ${doc_FileName})
    if(DEFINED doc_AddPlantUmlStyle)
        set(PlantUmlStyle ${CMAKE_CURRENT_SOURCE_DIR}/${doc_AddPlantUmlStyle})
    endif()
    set(AddIssuesLinks NO)
    if(DEFINED doc_AddIssuesLinks)
        set(AddIssuesLinks YES)
    endif()    
    configure_file(${DOCUMENTATION_SCRIPTS_ROOT_DIR}/doxygenConfig.in "${CMAKE_CURRENT_BINARY_DIR}/documentation/${doc_Type}/${doc_Type}.cmake" @ONLY)
    configure_file(${DOCUMENTATION_SCRIPTS_ROOT_DIR}/DoxygenCMakeLists.txt.in "${CMAKE_CURRENT_BINARY_DIR}/documentation/${doc_Type}/CMakeLists.txt" @ONLY)
    
    # create arguments for configuring
    set(configurationArgs "")
    list(APPEND configurationArgs "-G" "${CMAKE_GENERATOR}")
    if(DEFINED CMAKE_BUILD_TYPE)
        list(APPEND configurationArgs "-DCMAKE_BUILD_TYPE=${CMAKE_BUILD_TYPE}")
    endif()
    if(DEFINED CMAKE_TOOLCHAIN_FILE)
        list(APPEND configurationArgs "-DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}")
    endif()
    if(DEFINED CMAKE_MODULE_PATH)
        list(APPEND configurationArgs "-DCMAKE_MODULE_PATH=\"${CMAKE_MODULE_PATH}\"")
    endif()
    list(APPEND configurationArgs "-DDataFile=${CMAKE_CURRENT_BINARY_DIR}/documentation/${doc_Type}/${doc_Type}.cmake")
            
    add_custom_command(
        OUTPUT documentation-${doc_Type}.config
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_CURRENT_BINARY_DIR}/documentation/${doc_Type}/build
        COMMAND
            ${CMAKE_COMMAND} -E chdir ${CMAKE_CURRENT_BINARY_DIR}/documentation/${doc_Type}/build
            ${CMAKE_COMMAND} ${configurationArgs} ${CMAKE_CURRENT_BINARY_DIR}/documentation/${doc_Type}
        COMMAND ${CMAKE_COMMAND} -E touch documentation-${doc_Type}.config
        DEPENDS 
            ${CMAKE_CURRENT_BINARY_DIR}/documentation/${doc_Type}/${doc_Type}.cmake
            ${CMAKE_CURRENT_BINARY_DIR}/documentation/${doc_Type}/CMakeLists.txt
            documentation-${doc_Type}.always
        COMMENT "Configuring ${doc_Type} documentation")
        
    # because doxygen doesn't know its dependencies (source files) do documentation always
    add_custom_command(
        OUTPUT documentation-${doc_Type}.always
        COMMENT ""
    )
    add_custom_command(
        OUTPUT documentation-${doc_Type}.build
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_CURRENT_BINARY_DIR}/documentation/${doc_Type}/build --use-stderr
        COMMAND ${CMAKE_COMMAND} -E touch documentation-${doc_Type}.build
        DEPENDS documentation-${doc_Type}.config documentation-${doc_Type}.always
        COMMENT "Building ${doc_Type} Documentation")
                
    add_custom_target(documentation-${doc_Type} DEPENDS documentation-${doc_Type}.build)
        
    if(NOT TARGET documentation)
        add_custom_target(documentation)            
    endif()
    add_dependencies(documentation documentation-${doc_Type})
    
    set_property(DIRECTORY APPEND PROPERTY ADDITIONAL_MAKE_CLEAN_FILES ${CMAKE_CURRENT_BINARY_DIR}/documentation/${doc_Type})  
endfunction()
