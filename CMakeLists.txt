cmake_minimum_required(VERSION 3.7)
project(blinkytune)
include(CTest)
enable_testing()


set(CMAKE_CXX_STANDARD 14)
if(CMAKE_COMPILER_IS_GNUCXX)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
endif(CMAKE_COMPILER_IS_GNUCXX)

include(FindPkgConfig)

add_subdirectory(portaudio)
add_subdirectory(src)
add_subdirectory(test)


