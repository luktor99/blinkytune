cmake_minimum_required(VERSION 3.7)
project(blinkytune)
include(CTest)
enable_testing()


set(CMAKE_CXX_STANDARD 14)
if(CMAKE_COMPILER_IS_GNUCXX)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W0 /Od")
endif()

include(FindPkgConfig)

find_package(Boost 1.55.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

add_subdirectory(portaudio)
add_subdirectory(src)
add_subdirectory(test)


