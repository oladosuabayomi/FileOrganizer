cmake_minimum_required(VERSION 3.12)
project(FileOrganizer VERSION 1.0.0 LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set build type if not specified
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

# Compiler-specific options
if(MSVC)
    add_compile_options(/W4 /permissive-)
    add_compile_definitions(_CRT_SECURE_NO_WARNINGS)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
    if(CMAKE_BUILD_TYPE STREQUAL "Release")
        add_compile_options(-O2)
    endif()
endif()

# Source files
set(SOURCES
    src/main.cpp
    src/file_organizer.cpp
)

set(HEADERS
    src/file_organizer.h
)

# Create executable
add_executable(file-organizer ${SOURCES} ${HEADERS})

# Link filesystem library if needed (GCC < 9.0)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS "9.0")
    target_link_libraries(file-organizer stdc++fs)
endif()

# Set output directory
set_target_properties(file-organizer PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# Installation
install(TARGETS file-organizer
    RUNTIME DESTINATION bin
)

# CPack configuration for packaging
set(CPACK_PACKAGE_NAME "FileOrganizer")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Automatic file organization by type")
set(CPACK_PACKAGE_VENDOR "FileOrganizer Project")

include(CPack)
