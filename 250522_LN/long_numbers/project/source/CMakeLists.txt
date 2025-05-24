set(SOURCES
        long_number.cpp
)

set(HEADERS
        long_number.hpp
)

add_library(${LONG_NUMBER_LIB} ${HEADERS} ${SOURCES})   

target_include_directories(${LONG_NUMBER_LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
