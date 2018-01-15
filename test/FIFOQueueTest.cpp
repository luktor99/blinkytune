//
// Created by luktor99 on 15.01.18.
//
#include <boost/test/unit_test.hpp>

#include <FIFOQueue.h>

BOOST_AUTO_TEST_SUITE(FIFOQueueTest)

    BOOST_AUTO_TEST_CASE(PushElementToAnEmptyQueueAndPopIt) {
        FIFOQueue<int> queue(5);
        queue.push(new int(123));
        BOOST_CHECK_EQUAL(*queue.pop(), 123);
    }

    BOOST_AUTO_TEST_CASE(PushMultipleElementsToAnEmptyQueueAndPopThem) {
        FIFOQueue<int> queue(3);
        queue.push(new int(1));
        queue.push(new int(2));
        queue.push(new int(3));
        BOOST_CHECK_EQUAL(*queue.pop(), 1);
        BOOST_CHECK_EQUAL(*queue.pop(), 2);
        BOOST_CHECK_EQUAL(*queue.pop(), 3);
    }

    BOOST_AUTO_TEST_CASE(PushElementToAFullQueueAndCheckIfTheLastItemHasBeenOverwritten) {
        FIFOQueue<int> queue(3);
        queue.push(new int(1));
        queue.push(new int(2));
        queue.push(new int(3));
        queue.push(new int(4));
        BOOST_CHECK_EQUAL(*queue.pop(), 2);
        BOOST_CHECK_EQUAL(*queue.pop(), 3);
        BOOST_CHECK_EQUAL(*queue.pop(), 4);
    }

    BOOST_AUTO_TEST_CASE(CheckIfPopTimeout) {
        FIFOQueue<int> queue(3);
        BOOST_CHECK_THROW(queue.pop(), FIFOQueue<int>::TimeoutException);
    }

BOOST_AUTO_TEST_SUITE_END()