//
// Created by marcin on 11.12.17.
//
#ifndef WIN32
#define BOOST_TEST_DYN_LINK
#endif

#define BOOST_TEST_MODULE MelFilterBankTest
#include <iostream>
#include "../src/MelFilterBank.h"
#include <boost/test/included/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(MelFilterBankTest)

BOOST_AUTO_TEST_CASE( invalid )
{
    BOOST_CHECK(false);
    BOOST_CHECK_EQUAL(2,1);
}
BOOST_AUTO_TEST_SUITE_END()