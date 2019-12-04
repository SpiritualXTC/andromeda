# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.6)

message("Building Andromeda Effect")

include(../../common.cmake)
include(${PROJECT_ROOT}/common/addGLM.cmake)
include(${PROJECT_ROOT}/common/addBoost.cmake)

set(ANDROMEDA_EFFECT_SOURCE
	effect.h
	effect.cpp
	function.h
	function.cpp
	parser.h
	parser.cpp
	pass.h
	pass.cpp
	section.h
	shader.h
	shader.cpp
	technique.h
	technique.cpp
	uniform.h
	uniform.cpp
)

add_library(andromeda_effect ${ANDROMEDA_EFFECT_SOURCE})

include(../../common/addGLEW.cmake)
include_directories(${PROJECT_SOURCE_DIR}/andromeda)
target_link_libraries(andromeda_effect andromeda_common andromeda_core)


message("Finished Andromeda OpenGL")