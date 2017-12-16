find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
include_directories(${Qt5_INCLUDE_DIR})
link_directories(${Qt5_LIBRARY_DIRS})

find_package(Boost 1.55.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

set(PROJECT_SOURCE_DIR ../kfr)
include(../kfr/sources.cmake)
include_directories(../kfr/include)
include_directories(../portaudio/include)

set(SOURCE_FILES main.cpp UDPSender.cpp UDPSender.h AudioInterface.cpp AudioInterface.h AudioDevice.cpp AudioDevice.h
        AudioInputStream.cpp AudioInputStream.h AudioStream.cpp AudioStream.h ${KFR_SRC} FIFOQueue.h StereoSamplesBuffer.h
        Worker.h SpectrumGenerator.cpp SpectrumGenerator.h DSPParameters.h SamplesCollector.cpp SamplesCollector.h
        SpectrumAnalyzer.cpp SpectrumAnalyzer.h StereoSpectrumBuffer.h MainWindow.cpp MainWindow.h MelFilterBank.h
        MelFilterBank.cpp StereoAnalysisBuffer.h)
add_executable(blinkytune ${SOURCE_FILES})

add_dependencies(blinkytune check)

if(WIN32)
	set(boost_libs ${boost_system} ${boost_thread})
else()
	set(boost_libs boost_system boost_thread)
endif()

target_link_libraries(blinkytune ${boost_libs} portaudio_static Qt5::Core Qt5::Widgets Qt5::Gui)
