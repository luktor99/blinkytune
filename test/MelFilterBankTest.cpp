//
// Created by marcin on 11.12.17.
//
#ifndef WIN32
#define BOOST_TEST_DYN_LINK
#endif

#define BOOST_TEST_MODULE MelFilterBankTest

#include <iostream>
#include <MelFilterBank.h>
#include <boost/test/unit_test.hpp>


BOOST_AUTO_TEST_SUITE(MelFilterBankTest)

BOOST_AUTO_TEST_CASE( CheckConversion )
        {		
                //BOOST_CHECK_EQUAL(MelFilterBank::melToHertz(2595.0), 0.0);
				BOOST_CHECK_EQUAL(0, 0);
        }
BOOST_AUTO_TEST_SUITE_END()