//
// Created by marcin on 11.12.17.
//
#include <boost/test/unit_test.hpp>

#include <MelFilterBank.h>

BOOST_AUTO_TEST_SUITE(MelFilterBankTest)

    BOOST_AUTO_TEST_CASE(CheckConversion) {
        BOOST_CHECK_EQUAL(MelFilterBank::hertzToMel(0.0), 0.0);
        BOOST_CHECK_EQUAL(MelFilterBank::melToHertz(0.0), 0.0);
    }

BOOST_AUTO_TEST_SUITE_END()