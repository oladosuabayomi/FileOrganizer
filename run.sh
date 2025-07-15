#!/bin/bash

echo "File Organizer Build System"
echo "=========================="
echo

# Check for CMake
if command -v cmake &> /dev/null; then
    echo "Using CMake build system..."
    mkdir -p build
    cd build
    
    echo "Configuring..."
    if cmake .. -DCMAKE_BUILD_TYPE=Release; then
        echo "Building..."
        if cmake --build . --config Release; then
            echo
            echo "Build successful!"
            # Check if Windows (MSYS/MinGW) or Unix
            if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "cygwin" ]]; then
                echo "Executable: build/bin/Release/file-organizer.exe"
                echo
                echo "To run: ./build/bin/Release/file-organizer.exe --help"
            else
                echo "Executable: build/bin/file-organizer"
                echo
                echo "To run: ./build/bin/file-organizer --help"
            fi
            exit 0
        else
            echo "CMake build failed. Trying direct compilation..."
            cd ..
        fi
    else
        echo "CMake configuration failed. Trying direct compilation..."
        cd ..
    fi
fi

# Direct compilation fallback
echo "Direct compilation..."
mkdir -p build

echo "Checking compiler..."
if ! command -v g++ &> /dev/null; then
    echo "Error: g++ compiler not found"
    echo "Please install build tools:"
    echo "  Ubuntu/Debian: sudo apt install build-essential"
    echo "  CentOS/RHEL: sudo yum install gcc-c++"
    echo "  macOS: xcode-select --install"
    exit 1
fi

echo "Compiling..."
# Choose appropriate filename and flags based on OS
if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "cygwin" ]]; then
    EXE_NAME="build/file-organizer.exe"
    EXTRA_FLAGS="-static"
else
    EXE_NAME="build/file-organizer"
    EXTRA_FLAGS=""
fi

if g++ -std=c++17 -Wall -O2 $EXTRA_FLAGS -o $EXE_NAME src/main.cpp src/file_organizer.cpp; then
    echo
    echo "Build successful!"
    echo "Executable: $EXE_NAME"
    echo
    echo "To run: ./$EXE_NAME --help"
else
    echo "Build failed!"
    echo "Please check:"
    echo "1. C++17 compatible compiler is installed"
    echo "2. All source files are present"
    echo "3. No compilation errors in the code"
    exit 1
fi
