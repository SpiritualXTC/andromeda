# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.6)

message("Building Andromeda Core")

include(${PROJECT_ROOT}/common/addGLM.cmake)
include(${PROJECT_ROOT}/common/addBoost.cmake)

# Add Some Filters

set(ANDROMEDA_CORE_SOURCE 
	andromeda.h
	andromeda.cpp
)

set(ANDROMEDA_CORE_TYPES_SOURCE
	color.h
	region.h
)


set(ANDROMEDA_CORE_ENGINE_SOURCE
	Engine/config.h
	Engine/config.cpp
	Engine/display.h
	Engine/engine.h
	Engine/engine.cpp
	Engine/module.h
	Engine/module.cpp
	Engine/scene.h
	Engine/scene.cpp
	Engine/timing.h
	Engine/timing.cpp
)

# TODO: Mouse and Keyboard are both generic, however shouldn't necessarily exist across all platforms
# Make it better .. then again, so long as they compile it shouldn't matter. Just don't instantiate an instance
set(ANDROMEDA_CORE_INPUT_SOURCE
	Input/input.h
	Input/input.cpp

	Input/keyboard.h
	Input/keyboard.cpp
	Input/generic_keyboard.h
	Input/generic_keyboard.cpp
	Input/mouse.h
	Input/mouse.cpp
	Input/generic_mouse.h
	Input/generic_mouse.cpp
)

set(ANDROMEDA_CORE_GEOMETRY_SOURCE
	Geometry/geometry.h
	Geometry/geometry.cpp
	Geometry/geometry_builder.h
	Geometry/geometry_builder.cpp
	Geometry/geometry_cube.h
	Geometry/geometry_cube.cpp
	Geometry/geometry_cylinder.h
	Geometry/geometry_cylinder.cpp
	Geometry/geometry_desc.h
	Geometry/geometry_desc.cpp
	Geometry/geometry_ellipse.h
	Geometry/geometry_ellipse.cpp
	Geometry/geometry_generate.h
	Geometry/geometry_generate.cpp
	Geometry/geometry_polygon.h
	Geometry/geometry_polygon.cpp
	Geometry/geometry_surface.h
	Geometry/geometry_surface.cpp
	Geometry/geometry_surface_function.h
	Geometry/geometry_torus.h
	Geometry/geometry_torus.cpp
	Geometry/primitive_builder.h
	Geometry/primitive_builder.cpp
	Geometry/shape.h
	Geometry/shape.cpp
	Geometry/tesselation.h
	Geometry/tesselation.cpp
)

set(ANDROMEDA_CORE_GRAPHICS_SOURCE
	Graphics/buffer.h
	Graphics/graphics.h
	Graphics/graphics.cpp
	Graphics/geometry.h
	Graphics/material.h
	Graphics/mesh.h
	Graphics/mesh.cpp
	Graphics/renderer.h
	Graphics/renderer.cpp
	Graphics/shader.h
	Graphics/texture.h
	Graphics/types.h
	Graphics/view.h
	Graphics/view.cpp
)

set(ANDROMEDA_CORE_MATH_SOURCE
# Some of these may be better off in common
	Math/glm_conversion.h
	Math/glm_extension.h
	Math/glm_infinity.h

	Math/camera_matrix.h
	Math/math.h
	Math/matrix_stack.h
	Math/plane.h
	Math/projection_matrix.h
	Math/view_matrix.h
)

set(ANDROMEDA_SHARED_SOURCE
	../shared/context.h
	../shared/graphics.h
	../shared/platform.h
)



source_group("Andromeda" FILES ${ANDROMEDA_CORE_SOURCE})
source_group("Engine" FILES ${ANDROMEDA_CORE_ENGINE_SOURCE})
source_group("Geometry" FILES ${ANDROMEDA_CORE_GEOMETRY_SOURCE})
source_group("Graphics" FILES ${ANDROMEDA_CORE_GRAPHICS_SOURCE})
source_group("Input" FILES ${ANDROMEDA_CORE_INPUT_SOURCE})
source_group("Math" FILES ${ANDROMEDA_CORE_MATH_SOURCE})

source_group("Types" FILES ${ANDROMEDA_CORE_TYPES_SOURCE})

source_group("Shared" FILES ${ANDROMEDA_SHARED_SOURCE})

add_library(andromeda_core
	${ANDROMEDA_CORE_SOURCE} 
	${ANDROMEDA_CORE_ENGINE_SOURCE}
	${ANDROMEDA_CORE_INPUT_SOURCE}
	${ANDROMEDA_CORE_GEOMETRY_SOURCE}
	${ANDROMEDA_CORE_GRAPHICS_SOURCE}
	${ANDROMEDA_CORE_MATH_SOURCE}
	${ANDROMEDA_CORE_TYPES_SOURCE}
	${ANDROMEDA_SHARED_SOURCE}
)

include_directories(${PROJECT_SOURCE_DIR}/andromeda)
target_link_libraries(andromeda_core andromeda_common)

if (WIN32)
	target_link_libraries(andromeda_core andromeda_windows)
endif()



include(../../common.cmake)


message("Finished Andromeda Core")