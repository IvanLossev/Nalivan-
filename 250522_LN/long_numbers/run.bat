@echo off
chcp 65001

set BUILD_TYPE=Ninja
set BUILD_SUFFIX=ninja

set BUILD_FOLDER=build_%BUILD_SUFFIX%
set SOURCE_FOLDER=project

if not exist %BUILD_FOLDER% mkdir %BUILD_FOLDER%

cd %BUILD_FOLDER%

cmake -G %BUILD_TYPE% ..\%SOURCE_FOLDER%
cmake --build .

if exist test (
    cd test
    ctest --output-on-failure
    cd ..
)

cd ..

echo === Сборка и тестирование завершены! ===
pause  