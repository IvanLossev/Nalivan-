cmake_minimum_required(VERSION 3.2...3.27.5)

project(kmms_prog_2024)

enable_testing()
add_subdirectory(lib/googletest)

add_subdirectory(unit_test_example)

set(CMAKE_SUPPRESS_REGENERATION true)
