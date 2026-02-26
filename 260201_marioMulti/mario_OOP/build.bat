@echo off
REM Скрипт сборки проекта Mario Game с CMake

setlocal enabledelayedexpansion

REM Создать папку build, если её нет
if not exist build mkdir build

REM Перейти в папку build
cd build

REM Запустить CMake для генерации файлов проекта (для MinGW)
cmake -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release ..

REM Если CMake завершился успешно, запустить mingw32-make
if %ERRORLEVEL% equ 0 (
    echo.
    echo ========================================
    echo Компиляция проекта...
    echo ========================================
    mingw32-make
    
    if %ERRORLEVEL% equ 0 (
        echo.
        echo ========================================
        echo Сборка успешна! Запуск игры...
        echo ========================================
        mario_game.exe
    ) else (
        echo.
        echo Ошибка при компиляции!
        pause
    )
) else (
    echo.
    echo Ошибка при генерации конфигурации CMake!
    pause
)

cd ..
pause
