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

## Requirements

- C++17 compatible compiler (GCC 7.0+, Clang 5.0+, MSVC 2017+)
- CMake 3.12 or higher
- Operating System: Windows 10+, Ubuntu 18.04+, macOS 10.14+

## Installation

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

   ```bash
   # For Windows
   ./build.bat
   
   # For Linux/Mac
   chmod +x run.sh
   ./run.sh
   ```

3. Manual compilation (recommended - static linking to avoid linker issues):
   ```bash
   mkdir build
   cd build
   g++ -std=c++17 -static -o FileOrganizer.exe ../src/fileorganizer.cpp
   ```

**Note**: If you encounter linker errors, use the static linking option (`-static` flag) which resolves dynamic library dependencies.

### Usage

```bash
# Show help
./build/FileOrganizer.exe --help
```

```bash
# Interactive mode (recommended for beginners)
./build/FileOrganizer.exe --interactive
```

```bash
# List files and their categories (preview mode)
./build/FileOrganizer.exe --list "C:\path\to\folder"
```

```bash
# Organize files
./build/FileOrganizer.exe --organize "C:\path\to\folder"
```

```bash
# Undo last organization
./build/FileOrganizer.exe --undo "C:\path\to\folder"
```

```bash
# Undo specific session
./build/FileOrganizer.exe --undo "C:\path\to\folder" 20250711_143022
```

```bash
# Show organization history
./build/FileOrganizer.exe --history "C:\path\to\folder"
```

### Platform-Specific Instructions

**Windows:**

```cmd
build.bat
```

**Linux/macOS:**

```bash
chmod +x run.sh
./run.sh
```

## Usage

### Executable Locations

After building, the executable will be located at:

- **CMake build**: `./build/bin/Release/file-organizer.exe` (Windows) or `./build/bin/file-organizer` (Linux/macOS)
- **Direct compilation**: `./build/file-organizer.exe` (Windows) or `./build/file-organizer` (Linux/macOS)

**Note**: The `run.sh` script automatically detects your platform and shows the correct path after building.

**Tip**: For easier usage, you can create an alias:

```bash
# For Windows (Git Bash/MSYS)
alias file-organizer='./build/bin/Release/file-organizer.exe'

# For Linux/macOS
alias file-organizer='./build/bin/file-organizer'

# Then use simply:
file-organizer --help
```

### Command Line Interface

```bash
# Display help (Windows paths shown, adjust .exe for Linux/macOS)
./build/bin/Release/file-organizer.exe --help   # CMake build
# OR
./build/file-organizer.exe --help               # Direct compilation

# List files (preview mode)
./build/bin/Release/file-organizer.exe --list /path/to/directory

# Organize files
./build/bin/Release/file-organizer.exe --organize /path/to/directory

# Interactive mode
./build/bin/Release/file-organizer.exe --interactive

# Undo operations
./build/bin/Release/file-organizer.exe --undo /path/to/directory
./build/bin/Release/file-organizer.exe --undo /path/to/directory --session SESSION_ID

# View history
./build/bin/Release/file-organizer.exe --history /path/to/directory
```

### Examples

```bash
# Organize Downloads folder (Windows Git Bash/MSYS)
./build/bin/Release/file-organizer.exe --organize ~/Downloads

# Preview organization without moving files
./build/bin/Release/file-organizer.exe --list ~/Downloads

# Interactive mode for guided operation
./build/bin/Release/file-organizer.exe --interactive
```

## Project Structure

```
file-organizer/
├── src/
```

## Development

### Building from Source

```bash
mkdir build
cd build
cmake ..
make
```

### Running Tests

```bash
# Run with test directory (Windows Git Bash/MSYS)
./build/bin/Release/file-organizer.exe --list test_data/
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
