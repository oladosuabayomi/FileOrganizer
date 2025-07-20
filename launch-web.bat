@echo off
title FileOrganizer Web Interface Launcher
color 0A

echo.
echo ╔══════════════════════════════════════════════════════════════════════════════╗
echo ║                     📁 FileOrganizer Web Interface 📁                        ║
echo ║                          Simple. Fast. Beautiful.                           ║
echo ╚══════════════════════════════════════════════════════════════════════════════╝
echo.

:: Check if we're in the correct directory
if not exist "web\server.js" (
    echo ❌ Error: Please run this script from the FileOrganizer main directory
    echo.
    echo 💡 Current directory should contain:
    echo    - web\ folder with the web interface files
    echo    - build\ folder with FileOrganizer.exe
    echo    - src\ folder with source code
    echo.
    pause
    exit /b 1
)

:: Check for Node.js
echo 🔍 Checking Node.js installation...
node --version >nul 2>&1
if %errorlevel% neq 0 (
    echo ❌ Node.js is not installed or not in PATH
    echo.
    echo 💡 To install Node.js:
    echo    1. Visit: https://nodejs.org/
    echo    2. Download the LTS version ^(recommended^)
    echo    3. Run the installer
    echo    4. Restart this script
    echo.
    echo 🌐 Opening Node.js download page...
    start https://nodejs.org/
    pause
    exit /b 1
)

for /f "tokens=*" %%i in ('node --version') do set NODE_VERSION=%%i
echo ✅ Node.js found: %NODE_VERSION%

:: Check for C++ executable
echo 🔍 Checking FileOrganizer executable...
if not exist "build\FileOrganizer.exe" (
    echo ❌ FileOrganizer.exe not found in build\ directory
    echo.
    echo 💡 To build the application:
    echo    1. Run: build.bat
    echo    2. Wait for compilation to complete
    echo    3. Run this script again
    echo.
    echo 🔨 Would you like to build it now? ^(y/n^)
    set /p BUILD_CHOICE=
    if /i "%BUILD_CHOICE%"=="y" (
        echo.
        echo 🔨 Building FileOrganizer...
        call build.bat
        if not exist "build\FileOrganizer.exe" (
            echo ❌ Build failed. Please check for errors above.
            pause
            exit /b 1
        )
        echo ✅ Build completed successfully!
    ) else (
        echo.
        echo 💡 Please build the application and try again.
        pause
        exit /b 1
    )
)
echo ✅ FileOrganizer.exe found

:: Check port availability
echo 🔍 Checking if port 3000 is available...
netstat -an | find ":3000 " >nul
if %errorlevel% equ 0 (
    echo ⚠️  Port 3000 appears to be in use
    echo.
    echo 💡 This might cause issues. You can:
    echo    1. Close other applications using port 3000
    echo    2. Continue anyway ^(the server might still work^)
    echo.
    echo 🚀 Continue anyway? ^(y/n^)
    set /p CONTINUE_CHOICE=
    if /i not "%CONTINUE_CHOICE%"=="y" (
        echo 🚫 Startup cancelled.
        pause
        exit /b 1
    )
) else (
    echo ✅ Port 3000 is available
)

echo.
echo ╔══════════════════════════════════════════════════════════════════════════════╗
echo ║                           🚀 Starting Server 🚀                             ║
echo ╚══════════════════════════════════════════════════════════════════════════════╝
echo.
echo 📡 Server Status: Starting...
echo 🌐 URL: http://localhost:3000
echo ⌨️  Press Ctrl+C to stop the server
echo.
echo ━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━
echo.

:: Change to web directory and start server
cd web
node server.js

:: If we reach here, the server has stopped
echo.
echo 🛑 Server stopped.
echo 👋 Thank you for using FileOrganizer!
pause
