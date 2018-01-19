//
// Created by luktor99 on 15.01.18.
//
#include <boost/test/unit_test.hpp>

#include <AudioInterface.h>

BOOST_AUTO_TEST_SUITE(AudioInterfaceTest)

   BOOST_AUTO_TEST_CASE(CheckIfGetsInstance) {
	const AudioInterface& interface= AudioInterface::getInstance();
	BOOST_CHECK_EQUAL(&AudioInterface::getInstance(), &interface);
    }

   BOOST_AUTO_TEST_CASE(CheckIfGetsDefaultDevice) {
	   AudioInterface::getInstance().initialize();
	BOOST_CHECK_EQUAL(Pa_GetDefaultInputDevice(), AudioInterface::getInstance().getDefaultInputDevice().getID());
    }

   BOOST_AUTO_TEST_CASE(CheckIfTerminatesProperly) {
	   Pa_Initialize();
	   BOOST_CHECK_NO_THROW(AudioInterface::getInstance().terminate());
   }

   BOOST_AUTO_TEST_CASE(CheckIfInitializesProperly) {
	   BOOST_CHECK_NO_THROW(AudioInterface::getInstance().initialize());
   }

   BOOST_AUTO_TEST_CASE(CheckIfGetsDevicesList) {
	   std::list<AudioDevice> devices;
	   for (int i = 0; i < Pa_GetDeviceCount(); ++i)
		   devices.push_back(AudioDevice(i));
	   BOOST_CHECK_EQUAL(devices.size(), AudioInterface::getInstance().getDevicesList().size());
   }

   BOOST_AUTO_TEST_CASE(CheckIfGetsInputDevicesList) {
	   std::list<AudioDevice> devices;
	   for (int i = 0; i < Pa_GetDeviceCount(); ++i) {
		   if (Pa_GetDeviceInfo(i)->maxInputChannels > 0)
			   devices.push_back(AudioDevice(i));
	   }
	   BOOST_CHECK_EQUAL(devices.size(), AudioInterface::getInstance().getInputDevicesList().size());
   }
    
BOOST_AUTO_TEST_SUITE_END()