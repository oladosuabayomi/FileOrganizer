#!/bin/bash

echo "Building FileOrganizer Production Version..."
echo

# Create build directory if it doesn't exist
mkdir -p build

# Compile the production version
echo "Compiling FileOrganizerWithUndo..."
g++ -std=c++17 -static -O2 -Wall -Wextra -o build/FileOrganizerWithUndo src/main_simple_cli_with_undo.cpp

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo
    echo "✓ Build successful!"
    echo "✓ Executable: build/FileOrganizerWithUndo"
    echo
    echo "Usage:"
    echo "  ./build/FileOrganizerWithUndo --help"
    echo "  ./build/FileOrganizerWithUndo --interactive"
else
    echo
    echo "✗ Build failed!"
    echo "Make sure you have g++ with C++17 support installed."
fi

echo
