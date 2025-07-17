@echo off
echo Building FileOrganizer...
echo.

REM Create build directory if it doesn't exist
if not exist build mkdir build

REM Compile with static linking to avoid dynamic library issues
echo Compiling FileOrganizer...
g++ -std=c++17 -static-libgcc -static-libstdc++ -o build/FileOrganizer.exe src/fileorganizer.cpp

REM Check if compilation was successful
if %errorlevel% equ 0 (
    echo.
    echo ✓ Build successful!
    echo ✓ Executable: build/FileOrganizer.exe
    echo.
    echo Usage:
    echo   build\FileOrganizer.exe --help
    echo   build\FileOrganizer.exe --interactive
) else (
    echo.
    echo ✗ Build failed!
    echo Make sure you have g++ with C++17 support installed.
    echo You can install it via MinGW-w64 or MSYS2.
)

echo.
pause
echo.
echo To run: build\bin\file-organizer.exe --help
goto end

:cmake_error
echo CMake build failed. Trying direct compilation...
cd ..

:direct_build
echo Direct compilation...
if not exist build mkdir build


if %errorlevel% equ 0 (
    echo.
    echo Build successful!
    echo Executable: build\file-organizer.exe
    echo.
    echo To run: build\file-organizer.exe --help
) else (
    echo Build failed!
    goto error
)

goto end

:error
echo.
echo Build failed. Please check:
echo 1. C++17 compatible compiler is installed
echo 2. All source files are present
echo 3. No compilation errors in the code
exit /b 1

:end
echo.
pause

echo.
pause