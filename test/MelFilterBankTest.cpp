//
// Created by marcin on 11.12.17.
//

//Link to Boost
#define BOOST_TEST_DYN_LINK

//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "BaseClassModule"

//VERY IMPORTANT - include this last
#include <boost/test/unit_test.hpp>

#include "../MelFilterBank.h"
// ------------- Tests Follow --------------
BOOST_AUTO_TEST_CASE( constructors )
{

//Check default constructor
//Use BOOST_CHECK for small equal checks - true or false
}
