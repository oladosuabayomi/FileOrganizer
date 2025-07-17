#!/bin/bash

echo "Building FileOrganizer Production Version..."
echo

# Create build directory if it doesn't exist
mkdir -p build

# Compile the production version
echo "Compiling FileOrganizer..."
g++ -std=c++17 -static-libgcc -static-libstdc++ -O2 -Wall -Wextra -o build/FileOrganizer src/fileorganizer.cpp

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo
    echo "✓ Build successful!"
    echo "✓ Executable: build/FileOrganizer"
    echo
    echo "Usage:"
    echo "  ./build/FileOrganizer --help"
    echo "  ./build/FileOrganizer --interactive"
else
    echo
    echo "✗ Build failed!"
    echo "Make sure you have g++ with C++17 support installed."
fi

echo
