cmake_minimum_required(VERSION 3.31.5)
set(CMAKE_CXX_STANDARD 17)

project(long_number)

set(LONG_NUMBER_LIB "long_number_lib")
	
enable_testing()
add_subdirectory(lib/googletest)

add_subdirectory(source)
add_subdirectory(test)