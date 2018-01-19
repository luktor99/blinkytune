//
// Created by luktor99 on 15.01.18.
//
#include <boost/test/unit_test.hpp>

#include <SamplesCollector.h>

//Simple worker class for collecting samples from stream:

BOOST_AUTO_TEST_SUITE(SamplesCollectorTest)

BOOST_AUTO_TEST_CASE(CheckIfInitializesStream) {
	Pa_Initialize();
	FIFOQueue<StereoSamplesBuffer> fifo(5);
	AudioInputStream audioStream(AudioDevice(Pa_GetDefaultInputDevice()), SAMPLE_RATE, FRAMES_PER_BUFFER);
	BOOST_CHECK_NO_THROW(SamplesCollector(audioStream,fifo));
}
    
BOOST_AUTO_TEST_SUITE_END()