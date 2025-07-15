@echo off
setlocal

echo File Organizer Build System
echo ==========================
echo.

:: Check for CMake
cmake --version >nul 2>&1
if %errorlevel% neq 0 (
    echo CMake not found. Trying direct compilation...
    goto direct_build
)

:: CMake build
echo Using CMake build system...
if not exist build mkdir build
cd build

echo Configuring...
cmake .. -DCMAKE_BUILD_TYPE=Release
if %errorlevel% neq 0 goto cmake_error

echo Building...
cmake --build . --config Release
if %errorlevel% neq 0 goto cmake_error

echo.
echo Build successful!
echo Executable: build\bin\file-organizer.exe
echo.
echo To run: build\bin\file-organizer.exe --help
goto end

:cmake_error
echo CMake build failed. Trying direct compilation...
cd ..

:direct_build
echo Direct compilation...
if not exist build mkdir build

echo Checking compiler...
g++ --version >nul 2>&1
if %errorlevel% neq 0 (
    echo Error: g++ compiler not found
    echo Please install MinGW-w64 or Visual Studio
    goto error
)

echo Compiling...
g++ -std=c++17 -Wall -O2 -o build/file-organizer.exe src/main.cpp src/file_organizer.cpp

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