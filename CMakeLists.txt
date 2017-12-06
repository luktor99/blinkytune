cmake_minimum_required(VERSION 3.7)
project(blinkytune)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")

include_directories(kfr/include kfr/include/kfr /usr/include/python2.7)
set(SOURCE_FILES src/main.cpp src/UDPSender.cpp src/UDPSender.h src/AudioInterface.cpp src/AudioInterface.h src/AudioDevice.cpp src/AudioDevice.h src/AudioInputStream.cpp src/AudioInputStream.h src/AudioStream.cpp src/AudioStream.h matplotlibcpp.h graph.h)
add_executable(blinkytune ${SOURCE_FILES})

target_link_libraries(blinkytune pthread boost_system boost_thread portaudio python2.7)