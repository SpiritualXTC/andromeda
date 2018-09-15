# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.6)

message("Building Andromeda Common")

include(${PROJECT_ROOT}/common/addGLM.cmake)
include(${PROJECT_ROOT}/common/addBoost.cmake)

set(ANDROMEDA_COMMON_SOURCE 
	class.h
	class.cpp
	exception.h
	debug.h
	glm.h
	log.h
	observer.h
	observer.cpp
	singleton.h
	types.h
	)

add_library(andromeda_common ${ANDROMEDA_COMMON_SOURCE})

# For now Common is a Header-Only Library... so can play hell with CMake
set_target_properties(andromeda_common PROPERTIES LINKER_LANGUAGE CXX)

include(../../common.cmake)

message("Finished Andromeda Common")