@echo off
echo Starting FileOrganizer Web Interface...
echo.

:: Check if Node.js is installed
node --version >nul 2>&1
if %errorlevel% neq 0 (
    echo ❌ Node.js is not installed or not in PATH
    echo.
    echo 💡 Please install Node.js from: https://nodejs.org/
    echo    - Download the LTS version
    echo    - Run the installer
    echo    - Restart this script after installation
    echo.
    pause
    exit /b 1
)

:: Check if the C++ executable exists
if not exist "..\build\FileOrganizer.exe" (
    echo ❌ FileOrganizer.exe not found!
    echo.
    echo 💡 Please build the project first:
    echo    1. Run: build.bat  from the main directory
    echo    2. Then run this script again
    echo.
    pause
    exit /b 1
)

:: Display startup message
echo 🚀 Starting FileOrganizer Web Interface...
echo.
echo 📌 Controls:
echo    - Press Ctrl+C to stop the server
echo    - The browser should open automatically
echo    - If not, visit: http://localhost:3000
echo.
echo ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
echo.

:: Start the Node.js server
node server.js
