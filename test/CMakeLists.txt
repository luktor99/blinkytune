find_package(Boost COMPONENTS system unit_test_framework REQUIRED)

include_directories(../kfr/include)

add_executable(Tests MelFilterBankTest.cpp)
target_link_libraries(Tests ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(boostUnitTestsRun Tests)

if (CMAKE_CONFIGURATION_TYPES)
    message("Start testing: ")
    add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
            --force-new-ctest-process --output-on-failure
            --build-config "$<CONFIGURATION>"
            DEPENDS Tests)
else()
    message("Start testing: ")
    add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
            --force-new-ctest-process --output-on-failure
            DEPENDS Tests)
endif()