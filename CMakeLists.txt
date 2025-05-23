cmake_minimum_required(VERSION 3.10)
project(LongNumberProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(long_number STATIC long_number.cpp)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(long_number_test long_number_test.cpp)
target_link_libraries(long_number_test long_number gtest gtest_main pthread)

add_test(NAME LongNumberTest COMMAND long_number_test)
