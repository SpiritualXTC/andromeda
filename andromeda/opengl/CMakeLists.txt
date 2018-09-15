# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.6)

message("Building Andromeda OpenGL")



include(../../common.cmake)
include(${PROJECT_ROOT}/common/addGLM.cmake)
include(${PROJECT_ROOT}/common/addBoost.cmake)

set(ANDROMEDA_OPENGL_SOURCE
	../shared/graphics.h

	# TODO: Source Groups

	index_buffer.h
	index_buffer.cpp
	geometry.h
	geometry.cpp
	mapping.h
	opengl.h
	opengl.cpp
	texture.h
	texture.cpp
	vertex_buffer.h
	vertex_buffer.cpp
	)

add_library(andromeda_opengl ${ANDROMEDA_OPENGL_SOURCE})

include(../../common/addGLEW.cmake)
include_directories(${PROJECT_SOURCE_DIR}/andromeda)
target_link_libraries(andromeda_opengl andromeda_common andromeda_core)




message("Finished Andromeda OpenGL")