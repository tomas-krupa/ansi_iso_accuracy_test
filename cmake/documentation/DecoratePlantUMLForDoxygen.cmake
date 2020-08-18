cmake_minimum_required(VERSION 2.8)

function(DecoratePlantUML content modifiedContent style)
   
    string(REGEX REPLACE 
        "([ \t]*\\**[ \t]*)@startuml[ \t]+([^ \t]+)[ \t]+\"([^\"]+)\"" 
        "\\1@anchor \\2_Figure\n\\1[\\2]: @ref \\2_Figure \"\\3\"\n\\1\n\\1@startuml \"\\3\""
        mc
        "${content}")
        
    if(NOT "" STREQUAL "${style}")
        set(includeStyle "\\1!include ${style}\n")
    endif()        
    # add default scale for @startuml
    string(REGEX REPLACE 
        "([ \t]*\\*+[ \t]*)@startuml[ \t]*\n" 
        "\\1@startuml scale=0.5\n${includeStyle}"
        mc1
        "${mc}")        
    # add default scale for @startuml "title"
    string(REGEX REPLACE 
        "([ \t]*\\**[ \t]*)@startuml[ \t]+\"([^\"]+)\"[ \t]*\n" 
        "\\1@startuml \"\\2\" scale=0.5\n${includeStyle}"
        mc2
        "${mc1}")        
        
    set(${modifiedContent} "${mc2}" PARENT_SCOPE)
endfunction()
 

