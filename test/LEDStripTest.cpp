//
// Created by luktor99 on 15.01.18.
//
#include <boost/test/unit_test.hpp>

#include <LEDStrip.h>

BOOST_AUTO_TEST_SUITE(LEDStripTest)

//Warning!! User has to open PORT 4200 for these tests!!
BOOST_AUTO_TEST_CASE(CheckIfConnects) {
	
	BOOST_CHECK_NO_THROW(LEDStrip("127.0.0.1", 60));
}

BOOST_AUTO_TEST_CASE(CheckIfThrowsWhenCantConnect) {

	BOOST_CHECK_THROW(LEDStrip("0.0.0.0", 60), std::exception);
}

BOOST_AUTO_TEST_CASE(CheckIfSettersWorksWell) {
	LEDStrip led("127.0.0.1", 60);
	BOOST_CHECK_NO_THROW(led.setHSV(1, 0, -1, -1));
	BOOST_CHECK_NO_THROW(led.setHSV(1, 0, 1, 1));
	BOOST_CHECK_NO_THROW(led.setHSV(1, 60, 2, 2));
	BOOST_CHECK_NO_THROW(led.setHSV(1, 120, 1, 1));
	BOOST_CHECK_NO_THROW(led.setHSV(1, 180, 1, 1));
	BOOST_CHECK_NO_THROW(led.setHSV(1, 240, 1, 1));
	BOOST_CHECK_NO_THROW(led.setHSV(1, 300, 1, 1));
	BOOST_CHECK_NO_THROW(led.setHSV(1, 360, 1, 1));
	BOOST_CHECK_NO_THROW(led.setRGB(1,0,0,0));
}

BOOST_AUTO_TEST_CASE(CheckIfSetsGoodLength) {
	LEDStrip led("127.0.0.1", 60);
	BOOST_CHECK_EQUAL(led.getLength(), 60);
}

BOOST_AUTO_TEST_CASE(CheckIfSendingWorksWell) {
	LEDStrip led("127.0.0.1", 60);
	BOOST_CHECK_NO_THROW(led.update());
}
    
BOOST_AUTO_TEST_SUITE_END()