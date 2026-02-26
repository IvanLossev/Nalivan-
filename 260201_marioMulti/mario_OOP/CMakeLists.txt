cmake_minimum_required(VERSION 3.2)

project(mario_game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
    add_compile_options(/utf-8)
else()
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -finput-charset=utf-8 -fexec-charset=utf-8")
endif()

set(SOURCES
    main.cpp
    Game.cpp
    GameOver.cpp
)

set(HEADERS
    Game.hpp
    GameOver.hpp
    Map.hpp
    Object.hpp
)

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

if(WIN32)
    target_link_libraries(${PROJECT_NAME} user32 gdi32)
endif()
