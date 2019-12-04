# Specify the minimum version for CMake

# Andromeda Build

cmake_minimum_required(VERSION 3.6)
cmake_policy(SET CMP0015 NEW)

message("CMAKE: ${CMAKE_PREFIX_PATH}")
message("ENVIRO: $ENV{LIB_ROOT}")
message(${CMAKE_CURRENT_SOURCE_DIR})

set(PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR}) #TODO, is this a variable already?

# Project's name
project(andromeda)

# Set the output folder where your program will be created
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")

add_subdirectory(${PROJECT_SOURCE_DIR}/andromeda/common)
add_subdirectory(${PROJECT_SOURCE_DIR}/andromeda/core)
add_subdirectory(${PROJECT_SOURCE_DIR}/andromeda/opengl)
add_subdirectory(${PROJECT_SOURCE_DIR}/andromeda/effect)

if (WIN32)
	add_subdirectory(${PROJECT_SOURCE_DIR}/andromeda/windows)
endif()

# Testing
add_subdirectory(${PROJECT_SOURCE_DIR}/test)

# TODO: Mesh Viewer 
# TODO: Other Utilities


# Windows is still a bitch
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT tester)
set(CMAKE_DEFAULT_STARTUP_PROJECT tester)

#c:\Program Files (x86)\Windows Kits\10\Include\10.0.16299.0\um\gl\GL.h