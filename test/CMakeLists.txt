# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.6)

message("Building Andromeda Test")


include(../common.cmake)
include(${PROJECT_ROOT}/common/addGLM.cmake)
include(${PROJECT_ROOT}/common/addGLEW.cmake)
include(${PROJECT_ROOT}/common/addBoost.cmake)

set(TEST_SOURCE 
	main.cpp 
	app/app.h
	app/app.cpp
	app/test.h
)
add_executable(tester ${TEST_SOURCE})

include_directories(${PROJECT_SOURCE_DIR}/andromeda)
add_dependencies(tester andromeda_common andromeda_core andromeda_opengl)
target_link_libraries(tester andromeda_common andromeda_core andromeda_opengl)

# OpenGL
target_link_libraries(tester glew32s ${OPENGL_gl_LIBRARY})

# Platform
if(WIN_32)
	target_link_libraries(tester andromeda_windows andromeda_opengl)
endif()

message("Finished Andromeda Test")
message(${OPENGL_gl_LIBRARY})