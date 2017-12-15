cmake_minimum_required(VERSION 3.7)
project(blinkytune)
include(CTest)
enable_testing()

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -D_GLIBCXX_USE_CXX11_ABI=0")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

include(FindPkgConfig)
add_subdirectory(src)
add_subdirectory(test)

