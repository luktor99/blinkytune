find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)
include_directories(${Qt5_INCLUDE_DIR})
link_directories(${Qt5_LIBRARY_DIRS})

find_package(Boost 1.55.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

set(CMAKE_AUTOMOC ON)

set(PROJECT_SOURCE_DIR ../kfr)
include(../kfr/sources.cmake)
include_directories(SYSTEM ../kfr/include)

set(SOURCE_FILES main.cpp UDPSender.cpp UDPSender.h AudioInterface.cpp AudioInterface.h AudioDevice.cpp AudioDevice.h
        AudioInputStream.cpp AudioInputStream.h AudioStream.cpp AudioStream.h ${KFR_SRC} FIFOQueue.h StereoSamplesBuffer.h
        Worker.h SpectrumGenerator.cpp SpectrumGenerator.h Settings.h SamplesCollector.cpp SamplesCollector.h
        SpectrumAnalyzer.cpp SpectrumAnalyzer.h StereoSpectrumBuffer.h MainWindow.cpp MainWindow.h MelFilterBank.h
        MelFilterBank.cpp StereoAnalysisBuffer.h CollapseWidget.cpp CollapseWidget.h IndicatorWidget.cpp IndicatorWidget.h
		DeviceCard.cpp DeviceCard.h LedStripWidget.cpp LedStripWidget.h Filter.cpp Filter.h LEDStrip.cpp LEDStrip.h EffectsRenderer.cpp 
		EffectsRenderer.h Effect.h SoundEffect.h  NoSoundEffect.h effects/ColorBeat.cpp effects/ColorBeat.h EffectsController.cpp 
		EffectsController.h TickGenerator.cpp TickGenerator.h effects/StillColor.cpp effects/StillColor.h EffectsFactory.cpp 
		EffectsFactory.h effects/Rainbow.cpp effects/Rainbow.h effects/ColorSpectrum.cpp effects/ColorSpectrum.h)

add_executable(blinkytune ${SOURCE_FILES})

add_dependencies(blinkytune check)

if(WIN32)
    set(boost_libs ${boost_system} ${boost_thread})
else()
    set(boost_libs boost_system boost_thread)
endif()

target_link_libraries(blinkytune ${boost_libs} portaudio_static Qt5::Core Qt5::Widgets Qt5::Gui)

if(WIN32)
	add_custom_command(
        TARGET blinkytune POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Qt5_DIR}/../../../bin/Qt5Widgetsd.dll $<TARGET_FILE_DIR:blinkytune>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Qt5_DIR}/../../../bin/Qt5Cored.dll $<TARGET_FILE_DIR:blinkytune>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Qt5_DIR}/../../../bin/Qt5Guid.dll $<TARGET_FILE_DIR:blinkytune>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Qt5_DIR}/../../../bin/Qt5Widgets.pdb $<TARGET_FILE_DIR:blinkytune>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Qt5_DIR}/../../../bin/Qt5Core.pdb $<TARGET_FILE_DIR:blinkytune>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Qt5_DIR}/../../../bin/Qt5Gui.pdb $<TARGET_FILE_DIR:blinkytune>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Qt5_DIR}/../../../bin/Qt5Widgets.dll $<TARGET_FILE_DIR:blinkytune>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Qt5_DIR}/../../../bin/Qt5Core.dll $<TARGET_FILE_DIR:blinkytune>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Qt5_DIR}/../../../bin/Qt5Gui.dll $<TARGET_FILE_DIR:blinkytune>)
endif(WIN32)
