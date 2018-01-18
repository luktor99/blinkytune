//
// Created by luktor99 on 15.01.18.
//
#include <boost/test/unit_test.hpp>

#include <Filter.h>

BOOST_AUTO_TEST_SUITE(FilterTest)

   BOOST_AUTO_TEST_CASE(CheckIfDefaultValueIsZero) {
	BOOST_CHECK_EQUAL(Filter().get(), 1.0f);
    }

   BOOST_AUTO_TEST_CASE(CheckIfUpdateValueWorks) {
	BOOST_CHECK_CLOSE(Filter().update(2.0), 1.8f, 0.0001);
	BOOST_CHECK_CLOSE(Filter().update(0), 0.2f, 0.0001);
    }

   BOOST_AUTO_TEST_CASE(CheckIfUAssignsProperlyNewFilterValue) {
	   Filter filter;
	   filter = 2.0;
	   BOOST_CHECK_CLOSE(filter.get(), 1.8f, 0.0001);
   }
    
BOOST_AUTO_TEST_SUITE_END()