//
// Created by luktor99 on 15.01.18.
//
#include <boost/test/unit_test.hpp>

#include <AudioDevice.h>


BOOST_AUTO_TEST_SUITE(AudioDeviceTest)

BOOST_AUTO_TEST_CASE(CheckIfCreatesDefaultDevice) {
	Pa_Initialize();
	const AudioDevice device = AudioDevice();
	const PaDeviceInfo* deviceInfo = Pa_GetDeviceInfo(Pa_GetDefaultInputDevice());
	BOOST_CHECK_EQUAL(device.getID(), static_cast<int>(Pa_GetDefaultInputDevice()));
	BOOST_CHECK_EQUAL(device.getInputChannels(), deviceInfo->maxInputChannels);
	BOOST_CHECK_EQUAL(device.getName(), deviceInfo->name);
	Pa_Terminate();
}

	BOOST_AUTO_TEST_CASE(CheckIfCreatesDeviceOfSelectedID) {
		Pa_Initialize();
		BOOST_CHECK_EQUAL(AudioDevice(Pa_GetDefaultInputDevice()).getID(), static_cast<int>(Pa_GetDefaultInputDevice()));
		Pa_Terminate();
	}

    BOOST_AUTO_TEST_CASE(CheckIfThrowsOnWrongAudioDeviceIndex) {
		Pa_Initialize();
		BOOST_CHECK_THROW(AudioDevice(paNoDevice), std::out_of_range);
		Pa_Terminate();
    }

    
BOOST_AUTO_TEST_SUITE_END()