add_executable(mmh_test test_long_number.cpp)
include(GoogleTest)

target_link_libraries(mmh_test
    gtest_main
    ${LONG_NUMBER_LIB}
)

gtest_discover_tests(mmh_test)

