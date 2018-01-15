include_directories(../kfr/include)
include_directories(../src/)

find_package(Boost 1.55.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

set(Tests MelFilterBankTest FIFOQueueTest)
add_executable(MelFilterBankTest TestsMain.cpp MelFilterBankTest.cpp ../src/MelFilterBank.cpp )
add_test(MelFilterBankTest MelFilterBankTest)
add_executable(FIFOQueueTest TestsMain.cpp FIFOQueueTest.cpp )
add_test(FIFOQueueTest FIFOQueueTest)

if(WIN32)
    target_link_libraries(MelFilterBankTest ${boost_UNIT_TEST_FRAMEWORK_LIBRARY})
    target_link_libraries(FIFOQueueTest ${boost_UNIT_TEST_FRAMEWORK_LIBRARY})
else()
    target_link_libraries(MelFilterBankTest boost_unit_test_framework)
    target_link_libraries(FIFOQueueTest boost_unit_test_framework)
endif()

if (CMAKE_CONFIGURATION_TYPES)
    add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
            --force-new-ctest-process --output-on-failure
            --build-config "$<CONFIGURATION>"
            DEPENDS ${Tests})
else()
    add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
            --force-new-ctest-process --output-on-failure
            DEPENDS ${Tests})
endif()