#!/bin/bash

echo "Starting FileOrganizer Web Interface..."
echo

# Check if Node.js is installed
if ! command -v node &> /dev/null; then
    echo "❌ Node.js is not installed or not in PATH"
    echo
    echo "💡 Please install Node.js:"
    echo "   - Ubuntu/Debian: sudo apt install nodejs npm"
    echo "   - macOS: brew install node"
    echo "   - Or download from: https://nodejs.org/"
    echo
    exit 1
fi

# Check if the C++ executable exists
if [ ! -f "../build/FileOrganizer" ]; then
    echo "❌ FileOrganizer executable not found!"
    echo
    echo "💡 Please build the project first:"
    echo "   1. Run: ./run.sh from the main directory"
    echo "   2. Then run this script again"
    echo
    exit 1
fi

# Display startup message
echo "🚀 Starting FileOrganizer Web Interface..."
echo
echo "📌 Controls:"
echo "   - Press Ctrl+C to stop the server"
echo "   - The browser should open automatically"
echo "   - If not, visit: http://localhost:3000"
echo
echo "━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━"
echo

# Start the Node.js server
node server.js
