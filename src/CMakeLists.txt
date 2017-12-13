include(FindPkgConfig)
pkg_check_modules(PORTAUDIO portaudio-2.0)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

set(PROJECT_SOURCE_DIR ../kfr)
include(../kfr/sources.cmake)
include_directories(../kfr/include)

set(SOURCE_FILES main.cpp UDPSender.cpp UDPSender.h AudioInterface.cpp AudioInterface.h AudioDevice.cpp AudioDevice.h
        AudioInputStream.cpp AudioInputStream.h AudioStream.cpp AudioStream.h ${KFR_SRC} FIFOQueue.h StereoSamplesBuffer.h
        Worker.h SpectrumGenerator.cpp SpectrumGenerator.h DSPParameters.h SamplesCollector.cpp SamplesCollector.h
        SpectrumAnalyzer.cpp SpectrumAnalyzer.h StereoSpectrumBuffer.h MainWindow.cpp MainWindow.h MelFilterBank.h
        MelFilterBank.cpp StereoAnalysisBuffer.h)
add_executable(blinkytune ${SOURCE_FILES})

target_link_libraries(blinkytune pthread boost_system boost_thread portaudio Qt5::Core Qt5::Widgets Qt5::Gui)