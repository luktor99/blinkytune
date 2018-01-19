//
// Created by luktor99 on 15.01.18.
//
#include <boost/test/unit_test.hpp>

#include <EffectsFactory.h>
#include <typeinfo>
#include <iostream>

BOOST_AUTO_TEST_SUITE(EffectsFactoryTest)

   BOOST_AUTO_TEST_CASE(CheckIfGetsSingletonInstance) {
	const EffectsFactory& interface = EffectsFactory::getInstance();
	BOOST_CHECK_EQUAL(&EffectsFactory::getInstance(), &interface);
    }

BOOST_AUTO_TEST_CASE(CheckIfProducesRequiredObject) {
	EffectsFactory& interface = EffectsFactory::getInstance();
	BOOST_CHECK_EQUAL(typeid(*interface.createEffect("Still Color")).name(), "class StillColor");
	BOOST_CHECK_EQUAL(typeid(*interface.createEffect("Color Beat")).name(), "class ColorBeat");
	BOOST_CHECK_EQUAL(typeid(*interface.createEffect("Color Spectrum")).name(), "class ColorSpectrum");
	BOOST_CHECK_EQUAL(typeid(*interface.createEffect("Rainbow")).name(), "class Rainbow");
	BOOST_CHECK_EQUAL(interface.createEffect("Unknown"), nullptr);
}

BOOST_AUTO_TEST_CASE(CheckProducedObjectsNames) {
	EffectsFactory& interface = EffectsFactory::getInstance();
	const std::vector<std::string> noSoundEffects = interface.getNoSoundEffects();
	const std::vector<std::string> soundEffects = interface.getSoundEffects();
	BOOST_REQUIRE(std::find(noSoundEffects.begin(), noSoundEffects.end(), "Still Color") != noSoundEffects.end());
	BOOST_REQUIRE(std::find(noSoundEffects.begin(), noSoundEffects.end(), "Rainbow") != noSoundEffects.end());
	BOOST_REQUIRE(std::find(soundEffects.begin(), soundEffects.end(), "Color Beat") != soundEffects.end());
	BOOST_REQUIRE(std::find(soundEffects.begin(), soundEffects.end(), "Color Spectrum") != soundEffects.end());
}
    
BOOST_AUTO_TEST_SUITE_END()