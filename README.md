# FileOrganizer

FileOrganizer is a C++ desktop application designed to help users automatically organize their cluttered folders by sorting files into well-defined subfolders based on their file types. This application scans a specified directory and categorizes files into folders such as Documents, Music, Videos, Images, and Others.

## Problem Statement

Users often face challenges with disorganized folders containing mixed file types. FileOrganizer addresses this issue by providing a simple solution to automatically sort files into appropriate categories, making it easier for users to find and manage their files.

## Features

### Core Features

- **File Type Detection**: Automatically detects file types based on extensions
- **Smart Categorization**: Sorts files into logical categories (Documents, Music, Videos, Images, Others)
- **Object-Oriented Design**: Clean, maintainable C++ code using OOP principles
- **Cross-Platform**: Built with modern C++17 filesystem API

### File Categories Supported

- **Documents**: .pdf, .doc, .docx, .txt, .rtf, .odt, .xls, .xlsx, .ppt, .pptx, .csv, .md
- **Music**: .mp3, .wav, .flac, .aac, .ogg, .wma, .m4a, .opus
- **Videos**: .mp4, .avi, .mkv, .mov, .wmv, .flv, .webm, .m4v, .3gp
- **Images**: .jpg, .jpeg, .png, .gif, .bmp, .tiff, .svg, .webp, .ico
- **Others**: All other file types

### Available Versions

**FileOrganizerWithUndo.exe**: Production-ready CLI application with full functionality including undo operations and session history

## Getting Started

### Prerequisites

- C++ compiler with C++17 support (g++, clang++, MSVC)
- Windows, Linux, or macOS

### Installation

1. Clone the repository:

   ```bash
   git clone https://github.com/yourusername/FileOrganizer.git
   cd FileOrganizer
   ```

2. Build the project:

   ```bash
   # For Windows
   build.bat

   # For Linux/Mac
   chmod +x run.sh
   ./run.sh

   # Manual compilation
   g++ -std=c++17 -O2 -o build/FileOrganizerWithUndo.exe src/main_simple_cli_with_undo.cpp
   ```

### Usage

```bash
# Show help
./build/FileOrganizerWithUndo.exe --help

# Interactive mode
./build/FileOrganizerWithUndo.exe --interactive

# List files and their categories
./build/FileOrganizerWithUndo.exe --list "C:\path\to\folder"

# Organize files
./build/FileOrganizerWithUndo.exe --organize "C:\path\to\folder"

# Undo last organization
./build/FileOrganizerWithUndo.exe --undo "C:\path\to\folder"

# Show organization history
./build/FileOrganizerWithUndo.exe --history "C:\path\to\folder"
```

## Project Structure

```
FileOrganizer/
├── src/
│   ├── main_simple_cli_with_undo.cpp     # Production CLI with undo
│   ├── core/
│   │   ├── File.h/.cpp                   # Base file class
│   │   ├── FileHandler.h/.cpp            # Main file handling logic (Qt-based)
│   │   ├── ImageFile.h/.cpp              # Image file specialization
│   │   ├── AudioFile.h/.cpp              # Audio file specialization
│   │   ├── VideoFile.h/.cpp              # Video file specialization
│   │   └── DocumentFile.h/.cpp           # Document file specialization
│   └── utils/
│       ├── FileUtils.h/.cpp              # Utility functions
├── build/
│   └── FileOrganizerWithUndo.exe         # Production executable
├── build.bat                             # Windows build script
├── run.sh                                # Linux/Mac build script
├── DOCUMENTATION.md                      # Technical documentation
├── .gitignore                            # Git ignore file
└── README.md                             # This file
```

## Advanced Features

### Undo Functionality

The advanced CLI version includes comprehensive undo functionality:

- **Session-based undo**: Each organization operation is tracked
- **Selective undo**: Undo specific sessions by ID
- **History viewing**: See all past organization operations
- **Persistent logging**: Operations are saved to `.fileorganizer_log.txt`

### Safety Features

- **File integrity**: Moves files safely without data loss
- **Error handling**: Robust error handling for edge cases
- **Progress tracking**: Real-time progress updates during organization
- **Dry-run mode**: Preview mode for listing files before organizing

## Contributing

Contributions are welcome! Please feel free to submit a pull request or open an issue for any suggestions or improvements.

### Development Guidelines

- Follow C++17 standards
- Use Object-Oriented Programming principles
- Include proper error handling
- Write clear, self-documenting code
- Test both CLI versions before submitting

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Changelog

### v1.0.0 (Production Release)

- ✅ Production CLI version with undo functionality
- ✅ Object-oriented file handling system
- ✅ Cross-platform C++17 implementation
- ✅ Comprehensive file type support (Documents, Images, Music, Videos, Others)
- ✅ Session-based operation tracking and history
- ✅ Interactive and command-line modes
- ✅ Safe file operations with complete undo capability
- ✅ Clean, optimized codebase ready for production deployment

## Documentation

For detailed technical documentation, including OOP principles implementation, architecture details, and code examples, see [DOCUMENTATION.md](DOCUMENTATION.md).
