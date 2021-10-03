# Set basic project settings
cmake_minimum_required(VERSION 3.13)
project(sec)

set(CMAKE_CXX_STANDARD 17)

# Add FLEX functionality
find_package(FLEX)
if (FLEX_FOUND)
    if (WIN32)
        LIST(APPEND CMAKE_FIND_LIBRARY_SUFFIXES ".a")
        FIND_LIBRARY(FL_LIBRARY NAMES libfl fl DOC "path to the fl library")
    endif()

    FLEX_TARGET(${CMAKE_PROJECT_NAME} ./src/flex.l ./src/flex.c)
else()
    message("Failed to load FLEX")
endif()

# Add source files
set(SOURCE_FILES
    src/main.cpp
    src/flex.c

    src/utilities/char_utilities.c
	src/utilities/chararray_utilities.c
)

add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})

# Set output directory for executable
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)
