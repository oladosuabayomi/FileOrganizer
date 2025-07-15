# File Organizer - Technical Documentation

**Version 1.0.0 - Production Release**

## Table of Contents

1. [Problem Statement](#problem-statement)
2. [Project Overview](#project-overview)
3. [Benefits of the Solution](#benefits-of-the-solution)
4. [Architecture and Design](#architecture-and-design)
5. [Build System](#build-system)
6. [API Documentation](#api-documentation)
7. [Usage Examples](#usage-examples)
8. [Technical Implementation](#technical-implementation)
9. [Extension and Customization](#extension-and-customization)

---

## Problem Statement

### The Challenge

Modern computer users accumulate thousands of files across their systems, often resulting in:

- **Cluttered directories** with mixed file types (documents, images, videos, music all in one folder)
- **Difficulty finding files** when needed due to poor organization
- **Wasted time** manually sorting files into appropriate categories
- **Storage inefficiency** due to scattered file locations
- **No easy way to reverse organization mistakes** once files are moved

### Real-World Impact

- Users spend an average of 2.5 hours per week searching for misplaced files
- Poor file organization reduces productivity and increases frustration
- Manual file sorting is time-consuming and error-prone
- Accidental file movements can be difficult to reverse without proper tracking

---

## Project Overview

### Solution Description

File Organizer is a modern C++17 command-line application that automatically categorizes and organizes files in a directory based on their file extensions. The application uses a clean, single-responsibility architecture to create a maintainable, extensible, and robust file management system.

### Key Features

- **Automatic file categorization** into predefined categories (Documents, Images, Audio, Videos, Others)
- **Complete undo functionality** with detailed session tracking
- **Interactive and command-line modes** for different user preferences
- **Safe file operations** with comprehensive error handling and logging
- **Cross-platform compatibility** using C++17 filesystem API
- **Zero external dependencies** - pure standard library implementation
- **Professional command-line interface** with standard Unix-style arguments
- **Session-based operation tracking** for granular undo control

### Target Users

- **Home users** with cluttered download folders
- **Photographers** organizing large image collections
- **Content creators** managing mixed media files
- **Students** organizing academic documents
- **System administrators** automating file organization tasks
- **Anyone** who struggles with file organization

---

## Benefits of the Solution

### Immediate Benefits

1. **Time Savings**

   - Automated organization vs. manual sorting saves hours
   - Instant categorization of hundreds of files
   - No need to remember where files are located

2. **Improved Productivity**

   - Files are easily discoverable in logical categories
   - Reduced cognitive load from disorganized directories
   - Focus on work rather than file management

3. **Safety and Reliability**

   - Complete undo functionality prevents data loss
   - Session tracking allows selective reversal of operations
   - Safe file moves with error handling

4. **Flexibility**
   - Interactive mode for guided operation
   - Command-line mode for automation and scripting
   - Configurable categorization rules

### Long-term Benefits

1. **Maintainable System**

   - Object-oriented design allows easy modifications
   - New file types can be added without restructuring
   - Clean separation of concerns

2. **Scalability**

   - Handles directories with thousands of files efficiently
   - Memory-efficient operation with smart resource management
   - Batch processing capabilities for large file sets

3. **User Experience**
   - Consistent interface across different usage modes
   - Clear feedback and progress indicators
   - Comprehensive help and documentation
   - Detailed operation logging for transparency

---

## Architecture and Design

### Production Architecture (v1.0.0)

The File Organizer follows a clean, modern C++17 architecture emphasizing simplicity and maintainability:

```
┌─────────────────────────────────────────────────────────┐
│                    User Interface                        │
│                                                         │
│  ┌─────────────────┐    ┌─────────────────────────────┐ │
│  │ Interactive CLI │    │   Command-Line Interface    │ │
│  │    (main.cpp)   │    │       (main.cpp)           │ │
│  └─────────────────┘    └─────────────────────────────┘ │
└─────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────┐
│                Core Business Logic                       │
│                                                         │
│  ┌──────────────────────────────────────────────────┐  │
│  │            FileOrganizer Class                   │  │
│  │         (file_organizer.h/.cpp)                 │  │
│  │                                                  │  │
│  │  • list_files()                                 │  │
│  │  • organize_directory()                         │  │
│  │  • undo_organization()                          │  │
│  │  • show_history()                               │  │
│  │  • Session management                           │  │
│  │  • Category mapping                             │  │
│  │  • Error handling & logging                     │  │
│  └──────────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────┐
│                C++17 Standard Library                   │
│                                                         │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐ │
│  │ std::        │  │ std::        │  │ std::        │ │
│  │ filesystem   │  │ fstream      │  │ string       │ │
│  └──────────────┘  └──────────────┘  └──────────────┘ │
│                                                         │
│  ┌──────────────┐  ┌──────────────┐  ┌──────────────┐ │
│  │ std::vector  │  │ std::map     │  │ std::chrono  │ │
│  └──────────────┘  └──────────────┘  └──────────────┘ │
└─────────────────────────────────────────────────────────┘
```

### Project Structure

```
file-organizer/
├── src/
│   ├── main.cpp              # Application entry point and CLI
│   ├── file_organizer.h      # FileOrganizer class declaration
│   └── file_organizer.cpp    # FileOrganizer class implementation
├── build/                    # Build output directory
├── CMakeLists.txt           # CMake build configuration
├── build.bat               # Windows build script
├── run.sh                  # Unix/Linux build script
├── README.md               # User documentation
├── DOCUMENTATION.md        # Technical documentation (this file)
├── LICENSE                 # MIT license
└── .gitignore             # Git ignore rules
```

### Core Design Principles

The current architecture follows these key principles:

1. **Single Responsibility**: Each component has one clear purpose
2. **Simplicity**: Minimal complexity while maintaining functionality
3. **Maintainability**: Easy to understand, modify, and extend
4. **Cross-platform**: Uses standard C++17 features only
5. **Zero Dependencies**: No external libraries required

### Object-Oriented Programming Principles

While the current production version uses a simplified single-class architecture for maintainability, FileOrganizer demonstrates how Object-Oriented Programming principles can be applied to file management systems. Here are conceptual examples showing how the four core OOP principles could be implemented:

#### 1. Abstraction

**Definition**: Hiding complex implementation details while exposing only essential features.

**Conceptual Implementation for File Types**:

```cpp
// Abstract base class for file operations
class File {
public:
    virtual ~File() = default;
    virtual std::string getCategory() const = 0;  // Pure virtual function
    virtual bool isValidType(const std::string& extension) const = 0;

    // Common interface for all file types
    std::string getFilePath() const { return filePath; }
    std::string getFileName() const { return fileName; }
    size_t getFileSize() const { return fileSize; }

protected:
    std::string filePath;
    std::string fileName;
    size_t fileSize;
};
```

**Benefits**:

- Users interact with files through a simple, consistent interface
- Complex file type detection logic is hidden
- Easy to work with different file types uniformly

#### 2. Encapsulation

**Definition**: Bundling data and methods together while controlling access to internal state.

**Conceptual Implementation**:

```cpp
// ImageFile.cpp - Data and methods encapsulated
class ImageFile : public File {
private:
    // Private data members - controlled access
    static const std::vector<std::string> validExtensions;
    std::string resolution;
    std::string colorDepth;

public:
    // Public interface controls access to data
    std::string getCategory() const override { return "Images"; }

    bool isValidType(const std::string& extension) const override {
        return std::find(validExtensions.begin(), validExtensions.end(),
                        extension) != validExtensions.end();
    }

    // Controlled access to internal data
    std::string getResolution() const { return resolution; }
    void setResolution(const std::string& res) { resolution = res; }

private:
    // Private helper methods
    void detectImageProperties();
    bool validateImageFile();
};
```

**Benefits**:

- Internal file properties are protected from direct manipulation
- Data validation is enforced through controlled methods
- Class maintains its own invariants

#### 3. Inheritance

**Definition**: Creating new classes based on existing classes, inheriting properties and methods.

**Conceptual Implementation**:

```cpp
// Base class
class File {
    // Common functionality for all files
};

// Derived classes inherit from File
class DocumentFile : public File {
public:
    std::string getCategory() const override { return "Documents"; }
    bool isValidType(const std::string& extension) const override {
        static const std::vector<std::string> docExtensions =
            {"pdf", "doc", "docx", "txt", "rtf", "odt"};
        return std::find(docExtensions.begin(), docExtensions.end(),
                        extension) != docExtensions.end();
    }
};

class AudioFile : public File {
public:
    std::string getCategory() const override { return "Audio"; }
    bool isValidType(const std::string& extension) const override {
        static const std::vector<std::string> audioExtensions =
            {"mp3", "wav", "flac", "aac", "ogg", "m4a"};
        return std::find(audioExtensions.begin(), audioExtensions.end(),
                        extension) != audioExtensions.end();
    }
};

class VideoFile : public File {
public:
    std::string getCategory() const override { return "Videos"; }
    bool isValidType(const std::string& extension) const override {
        static const std::vector<std::string> videoExtensions =
            {"mp4", "avi", "mkv", "mov", "wmv", "flv"};
        return std::find(videoExtensions.begin(), videoExtensions.end(),
                        extension) != videoExtensions.end();
    }
};

class ImageFile : public File {
public:
    std::string getCategory() const override { return "Images"; }
    bool isValidType(const std::string& extension) const override {
        static const std::vector<std::string> imageExtensions =
            {"jpg", "jpeg", "png", "gif", "bmp", "tiff", "svg"};
        return std::find(imageExtensions.begin(), imageExtensions.end(),
                        extension) != imageExtensions.end();
    }
};
```

**Benefits**:

- Code reuse: Common file operations defined once in base class
- Consistent interface: All file types share the same basic structure
- Easy extension: New file types can be added by inheriting from File

#### 4. Polymorphism

**Definition**: Objects of different types can be treated uniformly through a common interface.

**Conceptual Implementation**:

```cpp
// FileHandler.cpp - Polymorphism in action
class FileHandler {
public:
    void organizeFolder(const std::string& folderPath) {
        std::filesystem::directory_iterator dirIter(folderPath);

        for (const auto& entry : dirIter) {
            if (entry.is_regular_file()) {
                // Create appropriate file object based on extension
                std::unique_ptr<File> file = createFileObject(entry);

                if (file) {
                    // Polymorphic call - different behavior for each file type
                    std::string category = file->getCategory();  // Calls appropriate override
                    std::string ext = entry.path().extension().string();
                    bool isValid = file->isValidType(ext);  // Polymorphic

                    if (isValid) {
                        moveFileToCategory(file.get(), category);
                    }
                }
            }
        }
    }

private:
    std::unique_ptr<File> createFileObject(const std::filesystem::directory_entry& entry) {
        std::string extension = entry.path().extension().string();
        std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

        // Factory pattern using polymorphism
        if (ImageFile().isValidType(extension)) {
            return std::make_unique<ImageFile>();
        }
        else if (AudioFile().isValidType(extension)) {
            return std::make_unique<AudioFile>();
        }
        else if (VideoFile().isValidType(extension)) {
            return std::make_unique<VideoFile>();
        }
        else if (DocumentFile().isValidType(extension)) {
            return std::make_unique<DocumentFile>();
        }

        return nullptr;  // Unknown file type
    }
};
```

**Benefits**:

- Single code path handles all file types uniformly
- Easy to add new file types without modifying existing code
- Runtime behavior determined by actual object type

### Alternative OOP Architecture

If implementing a full OOP design, the system architecture could look like:

```
┌─────────────────────────────────────────────────────────┐
│                    User Interface                        │
│                                                         │
│  ┌─────────────────┐    ┌─────────────────────────────┐ │
│  │ Interactive CLI │    │   Command-Line Interface    │ │
│  └─────────────────┘    └─────────────────────────────┘ │
└─────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────┐
│                 Core Application Logic                  │
│                                                         │
│  ┌──────────────────────────────────────────────────┐  │
│  │              FileHandler                          │  │
│  │  • Organization Logic                            │  │
│  │  • Undo Management                               │  │
│  │  • Session Tracking                              │  │
│  └──────────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────┐
│                  File Type System                       │
│                                                         │
│     ┌─────────┐  ┌─────────┐  ┌─────────┐  ┌─────────┐ │
│     │  File   │  │Document │  │ Image   │  │ Audio   │ │
│     │ (Base)  │  │  File   │  │  File   │  │  File   │ │
│     └─────────┘  └─────────┘  └─────────┘  └─────────┘ │
│                                                         │
│                    ┌─────────┐                         │
│                    │ Video   │                         │
│                    │  File   │                         │
│                    └─────────┘                         │
└─────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────┐
│                   Utility Layer                         │
│                                                         │
│  ┌──────────────────────────────────────────────────┐  │
│  │                FileUtils                         │  │
│  │  • File System Operations                       │  │
│  │  • Path Validation                              │  │
│  │  • Size Formatting                              │  │
│  └──────────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────────┘
```

### Class Relationships (OOP Design)

```cpp
// Class hierarchy showing OOP relationships
File (Abstract Base Class)
├── DocumentFile (Concrete Implementation)
├── ImageFile (Concrete Implementation)
├── AudioFile (Concrete Implementation)
└── VideoFile (Concrete Implementation)

FileHandler (Composition)
├── Uses File objects polymorphically
├── Manages file operations
└── Tracks undo sessions

FileOrganizer (Main Application)
├── Contains FileHandler (Composition)
├── Manages user interface
└── Coordinates application flow
```

**Note**: The current production version prioritizes simplicity and maintainability with a single `FileOrganizer` class that handles all functionality directly. The OOP examples above demonstrate how the system could be designed using classical object-oriented patterns for educational purposes or future extensibility requirements.

---

## Build System

### Prerequisites

- C++ compiler with C++17 support (g++, clang++, MSVC 2017+)
- Windows, Linux, or macOS operating system
- CMake 3.10+ (optional, for CMake builds)

### Installation and Building

1. **Clone the Repository**

   ```bash
   git clone https://github.com/your-username/FileOrganizer.git
   cd FileOrganizer
   ```

2. **Build Options**

   **Option A: Using Build Scripts (Recommended)**

   **Windows:**

   ```bash
   build.bat
   ```

   **Linux/Mac:**

   ```bash
   chmod +x run.sh
   ./run.sh
   ```

   **Option B: Using CMake**

   ```bash
   mkdir build
   cd build
   cmake ..
   make  # Linux/Mac
   # OR
   cmake --build . --config Release  # Cross-platform
   ```

   **Option C: Direct Compilation**

   ```bash
   # Create build directory
   mkdir build

   # Compile with static linking (recommended)
   g++ -std=c++17 -static -O2 -o build/file-organizer src/main.cpp src/file_organizer.cpp

   # Or without static linking
   g++ -std=c++17 -O2 -o build/file-organizer src/main.cpp src/file_organizer.cpp
   ```

### Build Notes

- **Static Linking**: The `-static` flag is recommended on Windows to avoid runtime library dependencies
- **Optimization**: Use `-O2` or `-O3` for release builds
- **Debug Builds**: Add `-g -DDEBUG` for debugging builds
- **Cross-Platform**: The code uses only standard C++17 features for maximum compatibility

---

## API Documentation

### FileOrganizer Class

The core `FileOrganizer` class provides all file organization functionality:

```cpp
class FileOrganizer {
public:
    // Main operations
    void list_files(const std::string& directory_path);
    bool organize_directory(const std::string& directory_path);
    bool undo_organization(const std::string& directory_path, const std::string& session_id = "");
    void show_history(const std::string& directory_path);

    // Utility methods
    bool is_valid_directory(const std::string& path);
    std::string get_last_session_id(const std::string& directory_path);

private:
    // File categorization
    std::string get_file_category(const std::string& extension);
    std::map<std::string, std::vector<std::string>> get_extension_categories();

    // Session management
    std::string generate_session_id();
    bool log_file_move(const std::string& session_id, const std::string& from, const std::string& to);
    bool restore_from_log(const std::string& directory_path, const std::string& session_id);
};
```

### Method Details

#### `list_files(const std::string& directory_path)`

- **Purpose**: Lists all files in the directory with their current and target categories
- **Parameters**: `directory_path` - Path to the directory to analyze
- **Output**: Displays files categorized by type with size information

#### `organize_directory(const std::string& directory_path)`

- **Purpose**: Organizes all files in the directory into category folders
- **Parameters**: `directory_path` - Path to the directory to organize
- **Returns**: `true` if successful, `false` if errors occurred
- **Side Effects**: Creates category folders and moves files, generates session log

#### `undo_organization(const std::string& directory_path, const std::string& session_id)`

- **Purpose**: Undoes a previous organization operation
- **Parameters**:
  - `directory_path` - Path to the directory to restore
  - `session_id` - Specific session to undo (optional, defaults to last session)
- **Returns**: `true` if successful, `false` if errors occurred
- **Side Effects**: Moves files back to original locations, removes empty category folders

#### `show_history(const std::string& directory_path)`

- **Purpose**: Displays the history of organization sessions for a directory
- **Parameters**: `directory_path` - Path to the directory
- **Output**: Lists all available sessions with timestamps and file counts

---

## Usage Examples

**Note**: The following examples show Windows paths (with `.exe` extension). For Linux/macOS, remove the `.exe` extension from all executable names.

### Usage Modes

#### 1. Interactive Mode (Recommended for Beginners)

```bash
# CMake build (Windows)
./build/bin/Release/file-organizer.exe --interactive

# Direct compilation (Windows)
./build/file-organizer.exe --interactive

# Linux/macOS - remove .exe extension
./build/bin/file-organizer --interactive
```

**Interactive Session Example:**

```
=== File Organizer CLI - Interactive Mode ===

Commands:
  1. List files in directory
  2. Organize directory
  3. Undo last organization
  4. Show organization history
  5. Exit

Enter your choice (1-5): 2
Enter directory path to organize: /home/user/Downloads

Starting file organization in: /home/user/Downloads
Session ID: 20250115_143022
Found 25 files to organize.
----------------------------------------
✓ Moved: report.pdf -> Documents/
Progress: 1/25 (4%)
✓ Moved: vacation.jpg -> Images/
Progress: 2/25 (8%)
...
----------------------------------------
File organization completed! Processed 25 files.
To undo this operation, use: --undo "/home/user/Downloads" 20250115_143022
```

#### 2. Command-Line Mode (For Automation)

**List Files Before Organizing:**

```bash
# CMake build (Windows)
./build/bin/Release/file-organizer.exe --list "/home/user/Downloads"

# Direct compilation (Windows)
./build/file-organizer.exe --list "/home/user/Downloads"
```

**Organize Files:**

```bash
./build/bin/Release/file-organizer.exe --organize "/home/user/Downloads"
```

**Undo Last Operation:**

```bash
./build/bin/Release/file-organizer.exe --undo "/home/user/Downloads"
```

**View Organization History:**

```bash
./build/bin/Release/file-organizer.exe --history "/home/user/Downloads"
```

**Undo Specific Session:**

```bash
./build/bin/Release/file-organizer.exe --undo "/home/user/Downloads" 20250115_143022
```

### Understanding the Output

#### File Listing

```
Files in /home/user/Downloads:
----------------------------------------
  document.pdf -> Documents (1.2 MB)
  photo.jpg -> Images (3.4 MB)
  song.mp3 -> Audio (4.1 MB)
  video.mp4 -> Videos (15.7 MB)
  archive.zip -> Others (2.3 MB)
```

#### Organization Process

```
Starting file organization in: /home/user/Downloads
Session ID: 20250115_143022
Found 5 files to organize.
----------------------------------------
✓ Moved: document.pdf -> Documents/
Progress: 1/5 (20%)
✓ Moved: photo.jpg -> Images/
Progress: 2/5 (40%)
✓ Moved: song.mp3 -> Audio/
Progress: 3/5 (60%)
✓ Moved: video.mp4 -> Videos/
Progress: 4/5 (80%)
✓ Moved: archive.zip -> Others/
Progress: 5/5 (100%)
----------------------------------------
File organization completed! Processed 5 files.
To undo this operation, use: --undo "/home/user/Downloads" 20250115_143022
```

#### Undo Process

```
Undoing 5 file moves...
----------------------------------------
✓ Restored: archive.zip
✓ Restored: video.mp4
✓ Restored: song.mp3
✓ Restored: photo.jpg
✓ Restored: document.pdf
Removed empty folder: Others
Removed empty folder: Videos
Removed empty folder: Audio
Removed empty folder: Images
Removed empty folder: Documents
----------------------------------------
Undo completed! Restored 5 files.
```

### File Categories

The application automatically categorizes files into these folders based on file extensions:

| Category      | Extensions                                                    |
| ------------- | ------------------------------------------------------------- |
| **Documents** | .pdf, .doc, .docx, .txt, .rtf, .odt, .xls, .xlsx, .ppt, .pptx |
| **Images**    | .jpg, .jpeg, .png, .gif, .bmp, .tiff, .svg, .webp             |
| **Audio**     | .mp3, .wav, .flac, .aac, .ogg, .m4a, .wma                     |
| **Videos**    | .mp4, .avi, .mkv, .mov, .wmv, .flv, .webm, .m4v               |
| **Others**    | All other file types                                          |

### Best Practices

1. **Always Test First**

   - Use `--list` to preview what will be organized
   - Test on a small folder before processing large directories

2. **Keep Track of Sessions**

   - Note the session ID after each organization
   - Use `--history` to review past operations

3. **Regular Backups**

   - While the undo feature is reliable, maintain regular backups
   - Test undo functionality on non-critical data first

4. **Batch Processing**
   - For automation, integrate into scripts:
     ```bash
     #!/bin/bash
     # Organize multiple folders (Windows paths shown)
     ./build/bin/Release/file-organizer.exe --organize "/home/user/Downloads"
     ./build/bin/Release/file-organizer.exe --organize "/home/user/Desktop"
     ./build/bin/Release/file-organizer.exe --organize "/home/user/Documents/Unsorted"
     ```

---

## Technical Implementation

### Core Algorithm

The file organization algorithm follows these steps:

1. **Directory Validation**: Verify the target directory exists and is accessible
2. **File Discovery**: Scan the directory for all regular files (non-directories)
3. **Extension Analysis**: Extract and normalize file extensions
4. **Category Mapping**: Map extensions to predefined categories
5. **Folder Creation**: Create category folders if they don't exist
6. **File Movement**: Move files to appropriate category folders
7. **Session Logging**: Record all operations for undo functionality
8. **Progress Reporting**: Provide real-time feedback to the user

### File Detection Algorithm

```cpp
std::string FileOrganizer::get_file_category(const std::string& extension) {
    // Convert to lowercase for case-insensitive comparison
    std::string ext = extension;
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);

    // Remove leading dot if present
    if (!ext.empty() && ext[0] == '.') {
        ext = ext.substr(1);
    }

    // Category mapping
    static const std::map<std::string, std::vector<std::string>> categories = {
        {"Documents", {"pdf", "doc", "docx", "txt", "rtf", "odt", "xls", "xlsx", "ppt", "pptx"}},
        {"Images", {"jpg", "jpeg", "png", "gif", "bmp", "tiff", "svg", "webp"}},
        {"Audio", {"mp3", "wav", "flac", "aac", "ogg", "m4a", "wma"}},
        {"Videos", {"mp4", "avi", "mkv", "mov", "wmv", "flv", "webm", "m4v"}}
    };

    // Search for extension in categories
    for (const auto& [category, extensions] : categories) {
        if (std::find(extensions.begin(), extensions.end(), ext) != extensions.end()) {
            return category;
        }
    }

    return "Others";  // Default category for unknown extensions
}
```

### Session Management

The application uses a robust session management system to track file operations:

```cpp
std::string FileOrganizer::generate_session_id() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);

    std::stringstream ss;
    ss << std::put_time(std::localtime(&time_t), "%Y%m%d_%H%M%S");
    return ss.str();
}

bool FileOrganizer::log_file_move(const std::string& session_id,
                                  const std::string& from,
                                  const std::string& to) {
    // Create log file path
    std::string log_path = std::filesystem::path(from).parent_path() / ".file_organizer_log.txt";

    std::ofstream log_file(log_path, std::ios::app);
    if (!log_file.is_open()) {
        return false;
    }

    // Log entry format: timestamp|session_id|operation|from_path|to_path
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);

    log_file << std::put_time(std::localtime(&time_t), "%Y-%m-%d %H:%M:%S")
             << "|" << session_id
             << "|MOVE|" << from
             << "|" << to << std::endl;

    return true;
}
```

### Error Handling

The application implements comprehensive error handling:

```cpp
bool FileOrganizer::organize_directory(const std::string& directory_path) {
    try {
        // Validate directory
        if (!is_valid_directory(directory_path)) {
            std::cerr << "Error: Invalid directory path: " << directory_path << std::endl;
            return false;
        }

        // Generate session ID
        std::string session_id = generate_session_id();

        // Process files with error handling
        std::error_code ec;
        for (const auto& entry : std::filesystem::directory_iterator(directory_path, ec)) {
            if (ec) {
                std::cerr << "Warning: Cannot access some files in directory" << std::endl;
                continue;
            }

            if (entry.is_regular_file()) {
                // Process individual file with error handling
                if (!process_file(entry.path(), session_id)) {
                    std::cerr << "Warning: Failed to process file: "
                              << entry.path().filename() << std::endl;
                }
            }
        }

        return true;

    } catch (const std::exception& e) {
        std::cerr << "Error during organization: " << e.what() << std::endl;
        return false;
    }
}
```

---

## Extension and Customization

### Adding New File Categories

To add support for new file types, modify the category mapping in `file_organizer.cpp`:

```cpp
// In get_extension_categories() method
std::map<std::string, std::vector<std::string>> FileOrganizer::get_extension_categories() {
    return {
        {"Documents", {"pdf", "doc", "docx", "txt", "rtf", "odt", "xls", "xlsx", "ppt", "pptx"}},
        {"Images", {"jpg", "jpeg", "png", "gif", "bmp", "tiff", "svg", "webp"}},
        {"Audio", {"mp3", "wav", "flac", "aac", "ogg", "m4a", "wma"}},
        {"Videos", {"mp4", "avi", "mkv", "mov", "wmv", "flv", "webm", "m4v"}},
        {"Archives", {"zip", "rar", "7z", "tar", "gz", "bz2"}},  // New category
        {"Code", {"cpp", "h", "py", "js", "html", "css", "java"}}  // New category
    };
}
```

### Custom Organization Rules

For more complex organization logic, extend the `get_file_category` method:

```cpp
std::string FileOrganizer::get_file_category(const std::string& extension) {
    std::string category = get_basic_category(extension);

    // Custom rules can be added here
    if (category == "Others") {
        // Special handling for unknown extensions
        if (is_executable_extension(extension)) {
            return "Executables";
        }
        if (is_config_file(extension)) {
            return "Configuration";
        }
    }

    return category;
}
```

### Integration with Build Systems

The File Organizer can be integrated into build systems for automated cleanup:

```cmake
# CMakeLists.txt example
add_custom_target(organize_downloads
    COMMAND ${CMAKE_BINARY_DIR}/file-organizer --organize "${HOME}/Downloads"
    COMMENT "Organizing downloads folder"
)
```
