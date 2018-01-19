//
// Created by luktor99 on 15.01.18.
//
#include <boost/test/unit_test.hpp>

#include <AudioInputStream.h>
#include <Settings.h>

BOOST_AUTO_TEST_SUITE(AudioInputStreamTest)

   BOOST_AUTO_TEST_CASE(CheckIfStartsStream) {
	Pa_Initialize();
	//Sample rate must be over 1000 for this test
	BOOST_CHECK_NO_THROW(AudioInputStream(AudioDevice(Pa_GetDefaultInputDevice()), SAMPLE_RATE, FRAMES_PER_BUFFER));
	//Pa_Terminate();
    }

	BOOST_AUTO_TEST_CASE(CheckIfThrows) {
	Pa_Initialize();
	//Sample rate must be under 1000 for this test
	BOOST_CHECK_THROW(AudioInputStream(AudioDevice(Pa_GetDefaultInputDevice()), 0, 10), std::runtime_error);
	//Pa_Terminate();
    }

	BOOST_AUTO_TEST_CASE(CheckIfCanReadFromBuffer) {
		static float samplesBufferL[FRAMES_PER_BUFFER] = { 0 };
		static float samplesBufferR[FRAMES_PER_BUFFER] = { 0 };
		static float *samplesBuffer[2] = { samplesBufferL, samplesBufferR };
		Pa_Initialize();
		//Sample rate must be over 1000 for this test
		BOOST_CHECK_NO_THROW(AudioInputStream(AudioDevice(Pa_GetDefaultInputDevice()), SAMPLE_RATE, FRAMES_PER_BUFFER).readSamples(&samplesBuffer));
		//Pa_Terminate();
	}

	BOOST_AUTO_TEST_CASE(CheckIfThrowsIfImpossibleToReadFromBuffer) {
		Pa_Initialize();
		//Sample rate must be over 1000 for this test
		BOOST_CHECK_THROW(AudioInputStream(AudioDevice(Pa_GetDefaultInputDevice()), SAMPLE_RATE, FRAMES_PER_BUFFER).readSamples(NULL), std::runtime_error);
		//Pa_Terminate();
	}

    
BOOST_AUTO_TEST_SUITE_END()