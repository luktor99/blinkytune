include_directories(../kfr/include)
include_directories(../src/)

set(SOURCE_FILES MelFilterBankTest.cpp ../src/MelFilterBank.cpp ../src/MelFilterBank.h)

find_package(Boost 1.55.0 REQUIRED)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

add_executable(Tests ${SOURCE_FILES})

#if(WIN32)
target_link_libraries(Tests ${boost_UNIT_TEST_FRAMEWORK_LIBRARY})
#else()
#	target_link_libraries(Tests boost_unit_test_framework)
#endif()
add_test(NAME boostUnitTestsRun COMMAND Tests)

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