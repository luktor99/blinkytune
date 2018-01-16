//
// Created by marcin on 11.12.17.
//
#include <boost/test/unit_test.hpp>

#include <MelFilterBank.h>

BOOST_AUTO_TEST_SUITE(MelFilterBankTest)

    BOOST_AUTO_TEST_CASE(CheckConversionFromZero) {
        BOOST_CHECK_EQUAL(MelFilterBank::hertzToMel(0.0), 0.0);
        BOOST_CHECK_EQUAL(MelFilterBank::melToHertz(0.0), 0.0);
    }

	BOOST_AUTO_TEST_CASE(CreateObjectAndCheckOutputSize) {
		MelFilterBank filterBank = MelFilterBank(1);
		kfr::univector<float, SPECTRUM_LENGTH> freqValues = { 1., 2. };
		BOOST_CHECK_EQUAL(filterBank.compute(freqValues, SAMPLE_RATE, 0, SAMPLE_RATE / 2).size(), 1);
	}

	BOOST_AUTO_TEST_CASE(CreateObjectAndCheckOutputValueForZero) {
		MelFilterBank filterBank = MelFilterBank(1);
		kfr::univector<float, SPECTRUM_LENGTH> freqValues = { 0., 0. };
		BOOST_CHECK_EQUAL(filterBank.compute(freqValues, SAMPLE_RATE, 0, SAMPLE_RATE / 2)[0], 0.0);
	}

BOOST_AUTO_TEST_SUITE_END()