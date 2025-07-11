@echo off
echo Building FileOrganizer...
echo.

REM Create build directory if it doesn't exist
if not exist build mkdir build

REM Compile with static linking to avoid dynamic library issues
echo Compiling FileOrganizerWithUndo...
g++ -std=c++17 -static -o build/FileOrganizerWithUndo.exe src/main_simple_cli_with_undo.cpp

REM Check if compilation was successful
if %errorlevel% equ 0 (
    echo.
    echo ✓ Build successful!
    echo ✓ Executable: build/FileOrganizerWithUndo.exe
    echo.
    echo Usage:
    echo   build\FileOrganizerWithUndo.exe --help
    echo   build\FileOrganizerWithUndo.exe --interactive
) else (
    echo.
    echo ✗ Build failed!
    echo Make sure you have g++ with C++17 support installed.
    echo You can install it via MinGW-w64 or MSYS2.
)

echo.
pause