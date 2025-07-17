#!/bin/bash

echo "Building FileOrganizer Production Version..."
echo

# Create build directory if it doesn't exist
mkdir -p build

# Compile the production version
echo "Compiling FileOrganizer..."

# Detect platform and set appropriate executable name
if [[ "$OSTYPE" == "msys" || "$OSTYPE" == "win32" || "$OSTYPE" == "cygwin" ]]; then
    EXECUTABLE="build/FileOrganizer.exe"
else
    EXECUTABLE="build/FileOrganizer"
fi

g++ -std=c++17 -static-libgcc -static-libstdc++ -O2 -Wall -Wextra -o "$EXECUTABLE" src/fileorganizer.cpp

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo
    echo "✓ Build successful!"
    echo "✓ Executable: $EXECUTABLE"
    echo
    echo "Usage:"
    echo "  ./$EXECUTABLE --help"
    echo "  ./$EXECUTABLE --interactive"
else
    echo
    echo "✗ Build failed!"
    echo "Make sure you have g++ with C++17 support installed."
fi

echo
