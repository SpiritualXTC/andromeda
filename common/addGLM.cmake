
set(glm_DIR $ENV{CMAKE_PREFIX_PATH}/glm-0.9.9.0/build)
find_package(glm 0.9.9.0)

if(GLM_INCLUDE_DIRS)
	message("GLM Found")

	include_directories(${GLM_INCLUDE_DIRS})
else(GLM_INCLUDE_DIRS)
	message("GLM not found")
endif(GLM_INCLUDE_DIRS)
