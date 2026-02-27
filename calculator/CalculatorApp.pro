QT += widgets

TEMPLATE = app
TARGET = CalculatorApp

SOURCES = main.cpp \
          mainwindow.cpp \
          calculatorwindow.cpp

HEADERS = mainwindow.hpp \
          calculatorwindow.hpp

CONFIG += c++17
CONFIG += release

# Windows-пути (исправляем проблему с относительными путями)
INCLUDEPATH += D:/msys2/mingw64/include/qt6
INCLUDEPATH += D:/msys2/mingw64/include/qt6/QtWidgets
INCLUDEPATH += D:/msys2/mingw64/include/qt6/QtCore
INCLUDEPATH += D:/msys2/mingw64/include/qt6/QtGui

LIBS += -LD:/msys2/mingw64/lib
LIBS += -lQt6Widgets -lQt6Core -lQt6Gui

# Явно указываем компилятор
QMAKE_CXX = g++
QMAKE_LINK = g++

# Отключаем создание лишних правил
CONFIG -= qtquickcompiler
