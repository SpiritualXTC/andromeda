message("Adding GLEW")

message("$ENV{CMAKE_PREFIX_PATH}/glew-2.1.0")

set(GLEW_INCLUDE_DIR $ENV{CMAKE_PREFIX_PATH}/glew-2.1.0)
set(GLEW_LIBRARY $ENV{CMAKE_PREFIX_PATH}/glew-2.1.0/lib/Release/Win32/)
find_package(GLEW REQUIRED)

include_directories(${GLEW_INCLUDE_DIRS}/include)
link_directories(${GLEW_LIBRARIES})

message("GLEW: ${GLEW_INCLUDE_DIRS}/include")
message("GLEW: ${GLEW_LIBRARIES}")