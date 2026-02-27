cmake_minimum_required(VERSION 3.16)
project(CalculatorApp)

# Находим пакет Qt6 Widgets (только Widgets, без QML)
find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)  # Автоматически запускает moc для Qt-классов

set(SOURCES
    main.cpp
    mainwindow.cpp
    calculatorwindow.cpp
)

set(HEADERS
    mainwindow.hpp
    calculatorwindow.hpp
)
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Подключаем Qt библиотеки
target_link_libraries(${PROJECT_NAME} Qt6::Widgets)

# Если нужны дополнительные модули Qt, добавьте их здесь
# target_link_libraries(${PROJECT_NAME} Qt6::Core Qt6::Gui Qt6::Widgets)
