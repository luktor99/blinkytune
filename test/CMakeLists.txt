find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(Tests MelFilterBankTest.cpp)
target_link_libraries(Tests ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})

add_test(boostUnitTestsRun Tests)

if (CMAKE_CONFIGURATION_TYPES)
    add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
            --force-new-ctest-process --output-on-failure
            --build-config "$<CONFIGURATION>"
            DEPENDS Tests)
else()
    add_custom_target(check COMMAND ${CMAKE_CTEST_COMMAND}
            --force-new-ctest-process --output-on-failure
            DEPENDS Tests)
endif()