# Set basic project settings
cmake_minimum_required(VERSION 3.13)
project(sec)

set(CMAKE_CXX_STANDARD 17)

message("START CMAKE")

# Add BISON functionality
find_package(BISON)
if (BISON_FOUND)
    BISON_TARGET(MyParser src/bison/bison.y ${CMAKE_CURRENT_SOURCE_DIR}/src/bison/parser.c DEFINES_FILE ${CMAKE_CURRENT_SOURCE_DIR}/src/flex/parser.h)
else()
    message("Failed to load BISON")
endif()

# Add FLEX functionality
find_package(FLEX)
if (FLEX_FOUND)
    if (WIN32)
        LIST(APPEND CMAKE_FIND_LIBRARY_SUFFIXES ".a")
        FIND_LIBRARY(FL_LIBRARY NAMES libfl fl DOC "path to the fl library")
    endif()

    FLEX_TARGET(MyLexer src/flex/flex.l ${CMAKE_CURRENT_SOURCE_DIR}/src/flex/lexer.c)
else()
    message("Failed to load FLEX")
endif()

# Add source files
set(SOURCE_FILES
    src/main.cpp

    src/flex/lexer.c
    src/flex/utilities/char_utilities.c
    src/flex/utilities/chararray_utilities.c

    src/bison/parser.c
    src/bison/tree_creators.c
    src/bison/print_tree_nodes.c

    src/EiffelModel/EiffelCore/eprogram.cpp
    src/EiffelModel/EiffelCore/eclass.cpp
    src/EiffelModel/EiffelCore/econstanttable.cpp
    src/EiffelModel/EiffelCore/efeature.cpp
    src/EiffelModel/EiffelCore/etype.cpp
    src/EiffelModel/EiffelAttributeInfo/eattribute.cpp
    src/EiffelModel/EiffelRoutineInfo/eroutine.cpp
    src/EiffelModel/EiffelRoutineInfo/einnervariable.cpp
    src/EiffelModel/EiffelErrors/semantic_error.cpp
)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

# Set output directory for executable
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
