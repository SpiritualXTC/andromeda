# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.6)

message("Building Andromeda Windows")

include(${PROJECT_ROOT}/common/addGLM.cmake)
include(${PROJECT_ROOT}/common/addBoost.cmake)

# TODO: Split by source_groups ("Shared" "Windows")
set(ANDROMEDA_WINDOWS_SOURCE
	../shared/context.h
	../shared/graphics.h
	../shared/platform.h
	../shared/platform.cpp

	windows_gui.h
	windows_gui.cpp
	windows_opengl.h
	windows_opengl.cpp
	windows_platform.h
	windows_platform.cpp
)

include(../../common/addGLEW.cmake)

include_directories(${PROJECT_SOURCE_DIR}/andromeda)
add_library(andromeda_windows ${ANDROMEDA_WINDOWS_SOURCE})
target_link_libraries(andromeda_windows andromeda_common andromeda_opengl)

include(../../common.cmake)

message("Finished Andromeda Windows")