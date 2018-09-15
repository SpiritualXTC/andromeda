

message("Including REDUNDANT common.cmake")

### BOOST LINK ###
# Windows is a bitch!
#set(Boost_NO_BOOST_CMAKE TRUE)
#set(Boost_NO_SYSTEM_PATHS TRUE)

# TODO: This needs to be based on a component style directory setup
#set(BOOST_ROOT F:/Libraries/boost_1_67_0)

#set(Boost_USE_STATIC_LIBS ON)
#set(Boost_USE_MULTITHREADED ON)
#set(Boost_USE_STATIC_RUNTIME OFF)

#find_package(boost 1.67.0 PATHS F:/Libraries/boost_1_67_0)

#if (NOT Boost_FOUND)
#	message("Boost not found")
#else()
#	message("Boost found")
#endif()


#include_directories(${Boost_INCLUDE_DIRS})




### GLM LINK ###
#set(glm_DIR F:/Libraries/glm-0.9.9.0/build)
#find_package(glm 0.9.9.0)

#message(${GLM_INCLUDE_DIRS})
#include_directories(${GLM_INCLUDE_DIRS})


### OPENGL LINK ###
#set(GLEW_INCLUDE_DIR F:/Libraries/glew-2.1.0)
#set(GLEW_LIBRARY F:/Libraries/glew-2.1.0/lib/Release/Win32/)
#find_package(GLEW REQUIRED)
#find_package(OpenGL REQUIRED)

#message("GLEW ${GLEW_INCLUDE_DIRS}/include")
#message("GLEW: ${GLEW_LIBRARIES}")

#include_directories(${GLEW_INCLUDE_DIRS}/include)
#link_directories(${GLEW_LIBRARIES})

#message("GLEW Include": ${GLEW_INCLUDE_DIRS})
#message(${GLEW_LIBRARIES})



if (WIN32)
	# TreatWChar_tAsBuiltInType: true == /Zc:wchar_t  false == /Zc:wchar_t-
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /Zc:wchar_t /UMBCS /D_UNICODE /DUNICODE -DGLEW_STATIC")
endif()