# File Organizer

A professional C++ command-line application for automatic file organization by type. Organizes cluttered directories into categorized subdirectories with full undo capabilities.

## Overview

File Organizer scans a directory and automatically sorts files into predefined categories based on file extensions. The application provides safe file operations with complete undo functionality and session tracking.

## Features

- Automatic file categorization by extension
- Safe file operations with error handling
- Complete undo functionality with session tracking
- Cross-platform compatibility (Windows, Linux, macOS)
- Interactive and command-line modes
- Progress tracking and detailed logging

## Supported File Types

| Category  | Extensions                                                                                       |
| --------- | ------------------------------------------------------------------------------------------------ |
| Documents | `.pdf`, `.doc`, `.docx`, `.txt`, `.rtf`, `.odt`, `.xls`, `.xlsx`, `.ppt`, `.pptx`, `.csv`, `.md` |
| Images    | `.jpg`, `.jpeg`, `.png`, `.gif`, `.bmp`, `.tiff`, `.svg`, `.webp`, `.ico`                        |
| Videos    | `.mp4`, `.avi`, `.mkv`, `.mov`, `.wmv`, `.flv`, `.webm`, `.m4v`, `.3gp`                          |
| Audio     | `.mp3`, `.wav`, `.flac`, `.aac`, `.ogg`, `.wma`, `.m4a`, `.opus`                                 |
| Others    | All other file types                                                                             |

## Build and Installation

### Prerequisites

- C++ compiler with C++17 support (g++, clang++, MSVC)
- Windows, Linux, or macOS

### Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/oladosuabayomi/FileOrganizer.git
   cd FileOrganizer
   ```

2. Build the project:

   **Windows (Command Prompt):**

   ```cmd
   build.bat
   ```

   **Linux/macOS/Windows (Git Bash):**

   ```bash
   chmod +x run.sh
   ./run.sh
   ```

3. The executable will be created in the `build/` directory:
   - **Windows**: `build/FileOrganizer.exe`
   - **Linux/macOS**: `build/FileOrganizer`

## Usage

### Basic Commands

```bash
# Show help
./build/FileOrganizer --help               # Linux/macOS
./build/FileOrganizer.exe --help           # Windows

# Interactive mode (recommended for beginners)
./build/FileOrganizer --interactive

# List files and their categories (preview mode)
./build/FileOrganizer --list "/path/to/folder"

# Organize files
./build/FileOrganizer --organize "/path/to/folder"

# Undo last organization
./build/FileOrganizer --undo "/path/to/folder"

# Undo specific session
./build/FileOrganizer --undo "/path/to/folder" 20250711_143022

# Show organization history
./build/FileOrganizer --history "/path/to/folder"
```

### Examples

```bash
# Organize Downloads folder
./build/FileOrganizer --organize ~/Downloads

# Preview organization without moving files
./build/FileOrganizer --list ~/Downloads

# Interactive mode for guided operation
./build/FileOrganizer --interactive

# Undo the last organization in Downloads
./build/FileOrganizer --undo ~/Downloads
```

## Project Structure

```
FileOrganizer/
├── src/
│   └── fileorganizer.cpp    # Main application source
├── build/                   # Build output directory
│   └── FileOrganizer(.exe)  # Compiled executable
├── build.bat               # Windows build script
├── run.sh                  # Linux/macOS build script
├── README.md               # User documentation
├── DOCUMENTATION.md        # Technical documentation
├── LICENSE                 # MIT License
└── .gitignore             # Git ignore rules
```

## Development

### Building from Source

Use the provided build scripts for your platform:

- **Windows**: `build.bat`
- **Linux/macOS/Git Bash**: `./run.sh`

### Manual Compilation

For advanced users who prefer manual compilation:

```bash
# Create build directory
mkdir -p build

# Windows
g++ -std=c++17 -static-libgcc -static-libstdc++ -o build/FileOrganizer.exe src/fileorganizer.cpp

# Linux/macOS
g++ -std=c++17 -static-libgcc -static-libstdc++ -O2 -Wall -Wextra -o build/FileOrganizer src/fileorganizer.cpp
```

## License

This project is licensed under the MIT License. See LICENSE file for details.

## Contributing

1. Fork the repository
2. Create a feature branch
3. Commit your changes
4. Push to the branch
5. Create a Pull Request

## Support

For issues and questions, please create an issue on the GitHub repository.

<!-- reference the DOCUMENTATION.md file -->

## Documentation

For detailed documentation, please refer to the [DOCUMENTATION.md](DOCUMENTATION.md) file.
This file contains comprehensive guides, examples, and API references to help you understand and use the File Organizer effectively.
