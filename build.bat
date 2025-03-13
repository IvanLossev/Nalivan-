@echo off
setlocal EnableDelayedExpansion
::
:: Вид сборки / суффикс в названии каталога сборки
::
:: "Ninja" / "ninja"
::
set BUILD_TYPE=Ninja
set BUILD_SUFFIX=ninja

chcp 65001

set BUILD_FOLDER=build_%BUILD_SUFFIX%
set SOURCE_FOLDER=projects

if not exist %BUILD_FOLDER% mkdir %BUILD_FOLDER%

cd %BUILD_FOLDER%

set PARAMS="-DCPR_USE_SYSTEM_CURL=ON -DBUILD_SHARED_LIBS=OFF"

cmake -G %BUILD_TYPE% ..\%SOURCE_FOLDER% "%PARAMS%"
cmake --build .

copy ..\%SOURCE_FOLDER%\bubble_sort\run_bubble_sort.bat .\bubble_sort