
message("Boooooost")

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)

find_package(boost 1.67.0 REQUIRED)

if (Boost_FOUND)
	message("Boost Found")
	include_directories(${Boost_INCLUDE_DIRS})
else()
	message("Boost not Found")
endif()