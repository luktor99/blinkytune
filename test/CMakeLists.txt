include_directories(../kfr/include)
include_directories(../src/)
include_directories(../portaudio/include)

find_package(Qt5 COMPONENTS Widgets REQUIRED)
include_directories(${Qt5_INCLUDE_DIR})
link_directories(${Qt5_LIBRARY_DIRS})

find_package(Boost 1.55.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})


set(Tests MelFilterBankTest FIFOQueueTest AudioDeviceTest AudioInputStreamTest AudioInterfaceTest EffectsControllerTest
    EffectsFactoryTest EffectsRendererTest FilterTest LEDStripTest SamplesCollectorTest SpectrumAnalyzerTest SpectrumGeneratorTest 
	StereoAnalysisBufferTest StereoSamplesBufferTest StereoSpectrumBufferTest TickGeneratorTest )

add_executable(MelFilterBankTest TestsMain.cpp MelFilterBankTest.cpp ../src/MelFilterBank.cpp)
add_test(MelFilterBankTest MelFilterBankTest)
add_executable(FIFOQueueTest TestsMain.cpp FIFOQueueTest.cpp)
add_test(FIFOQueueTest FIFOQueueTest)
add_executable(AudioDeviceTest TestsMain.cpp AudioDeviceTest.cpp ../src/AudioDevice.cpp)
add_test(AudioDeviceTest AudioDeviceTest)
add_executable(AudioInputStreamTest TestsMain.cpp AudioInputStreamTest.cpp ../src/AudioInputStream.cpp ../src/AudioStream.cpp ../src/AudioDevice.cpp)
add_test(AudioInputStreamTest AudioInputStreamTest)
add_executable(AudioInterfaceTest TestsMain.cpp AudioInterfaceTest.cpp ../src/AudioDevice.cpp ../src/AudioInterface.cpp)
add_test(AudioInterfaceTest AudioInterfaceTest)
#add_executable(EffectsControllerTest TestsMain.cpp EffectsControllerTest.cpp)
#add_test(EffectsControllerTest EffectsControllerTest)
add_executable(EffectsFactory TestsMain.cpp EffectsFactoryTest.cpp ../src/LEDStrip.cpp ../src/UDPSender.cpp ../src/EffectsFactory.cpp ../src/effects/StillColor.cpp ../src/effects/ColorBeat.cpp ../src/effects/Rainbow.cpp ../src/effects/ColorSpectrum.cpp)
add_test(EffectsFactoryTest EffectsFactory)
#add_executable(EffectsRendererTest TestsMain.cpp EffectsRendererTest.cpp)
#add_test(EffectsRendererTest EffectsRendererTest)
add_executable(FilterTest TestsMain.cpp FilterTest.cpp ../src/Filter.cpp)
add_test(FilterTest FilterTest)
add_executable(LEDStripTest TestsMain.cpp LEDStripTest.cpp ../src/LEDStrip.cpp ../src/UDPSender.cpp)
add_test(LEDStripTest LEDStripTest)
add_executable(SamplesCollectorTest TestsMain.cpp SamplesCollectorTest.cpp ../src/SamplesCollector.cpp ../src/AudioInputStream.cpp ../src/AudioStream.cpp ../src/AudioDevice.cpp )
add_test(SamplesCollectorTest SamplesCollectorTest)
#add_executable(SpectrumAnalyzerTest TestsMain.cpp SpectrumAnalyzerTest.cpp)
#add_test(SpectrumAnalyzerTest SpectrumAnalyzerTest)
#add_executable(SpectrumGeneratorTest TestsMain.cpp SpectrumGeneratorTest.cpp)
#add_test(SpectrumGeneratorTest SpectrumGeneratorTest)
#add_executable(TickGeneratorTest TestsMain.cpp TickGeneratorTest.cpp)
#add_test(TickGeneratorTest TickGeneratorTest)


if(WIN32)
    target_link_libraries(MelFilterBankTest ${boost_UNIT_TEST_FRAMEWORK_LIBRARY})
    target_link_libraries(FIFOQueueTest ${boost_UNIT_TEST_FRAMEWORK_LIBRARY})
	target_link_libraries(AudioDeviceTest ${boost_UNIT_TEST_FRAMEWORK_LIBRARY} portaudio_static)
	target_link_libraries(AudioInputStreamTest ${boost_UNIT_TEST_FRAMEWORK_LIBRARY} portaudio_static)
	target_link_libraries(AudioInterfaceTest ${boost_UNIT_TEST_FRAMEWORK_LIBRARY} portaudio_static)
#	target_link_libraries(EffectsControllerTest ${boost_UNIT_TEST_FRAMEWORK_LIBRARY})
	target_link_libraries(EffectsFactory ${boost_UNIT_TEST_FRAMEWORK_LIBRARY} Qt5::Widgets Qt5::Core)
#	target_link_libraries(EffectsRendererTest ${boost_UNIT_TEST_FRAMEWORK_LIBRARY})
	target_link_libraries(FilterTest ${boost_UNIT_TEST_FRAMEWORK_LIBRARY})
	target_link_libraries(SamplesCollectorTest ${boost_UNIT_TEST_FRAMEWORK_LIBRARY} portaudio_static)
#	target_link_libraries(SpectrumAnalyzerTest ${boost_UNIT_TEST_FRAMEWORK_LIBRARY})
#	target_link_libraries(SpectrumGeneratorTest ${boost_UNIT_TEST_FRAMEWORK_LIBRARY})
#	target_link_libraries(TickGeneratorTest ${boost_UNIT_TEST_FRAMEWORK_LIBRARY})
else()
    target_link_libraries(MelFilterBankTest boost_unit_test_framework)
    target_link_libraries(FIFOQueueTest boost_unit_test_framework)
	target_link_libraries(AudioDeviceTest boost_unit_test_framework portaudio_static)
	target_link_libraries(AudioInputStreamTest boost_unit_test_framework portaudio_static)
	target_link_libraries(AudioInterfaceTest boost_unit_test_framework portaudio_static)
#	target_link_libraries(EffectsControllerTest boost_unit_test_framework)
	target_link_libraries(EffectsFactory boost_unit_test_framework Qt5::Widgets)
#	target_link_libraries(EffectsRendererTest boost_unit_test_framework)
	target_link_libraries(FilterTest boost_unit_test_framework)
	target_link_libraries(SamplesCollectorTest boost_unit_test_framework portaudio_static)
#	target_link_libraries(SpectrumAnalyzerTest boost_unit_test_framework)
#	target_link_libraries(SpectrumGeneratorTest boost_unit_test_framework)
#	target_link_libraries(TickGeneratorTest boost_unit_test_framework)

endif()

if(WIN32)
	add_custom_command(
        TARGET EffectsFactory PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Qt5_DIR}/../../../bin/Qt5Widgetsd.dll $<TARGET_FILE_DIR:EffectsFactory>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Qt5_DIR}/../../../bin/Qt5Cored.dll $<TARGET_FILE_DIR:EffectsFactory>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Qt5_DIR}/../../../bin/Qt5Guid.dll $<TARGET_FILE_DIR:EffectsFactory>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Qt5_DIR}/../../../bin/Qt5Widgets.pdb $<TARGET_FILE_DIR:EffectsFactory>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Qt5_DIR}/../../../bin/Qt5Core.pdb $<TARGET_FILE_DIR:EffectsFactory>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Qt5_DIR}/../../../bin/Qt5Gui.pdb $<TARGET_FILE_DIR:EffectsFactory>
        COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Qt5_DIR}/../../../bin/Qt5Widgets.dll $<TARGET_FILE_DIR:EffectsFactory>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Qt5_DIR}/../../../bin/Qt5Core.dll $<TARGET_FILE_DIR:EffectsFactory>
		COMMAND ${CMAKE_COMMAND} -E copy_if_different ${Qt5_DIR}/../../../bin/Qt5Gui.dll $<TARGET_FILE_DIR:EffectsFactory>)
endif(WIN32)


if (CMAKE_CONFIGURATION_TYPES)
    add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
            --force-new-ctest-process --output-on-failure
            --build-config "$<CONFIGURATION>"
            DEPENDS ${Tests})
else()
    add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
            --force-new-ctest-process --output-on-failure
            DEPENDS ${Tests})
endif()