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


**Definition**: Bundling data and methods together while controlling access to internal state.

**Conceptual Implementation**:

**Location**: `src/fileorganizer.cpp`, lines 42-67

```cpp
class SimpleFileOrganizer {
private:
    // Private data members - controlled access

private:
    // Private helper methods - implementation details hidden
    std::string getCategory(const std::string& extension);
    void createCategoryFolders(const std::string& basePath);
    bool isValidFile(const fs::path& filePath, const std::string& basePath);
    std::string getUniqueFilePath(const std::string& originalPath);
    std::string getCurrentTimestamp();
    void saveUndoLog(const std::string& folderPath, const std::vector<FileMove>& moves, const std::string& sessionId);
    void removeEmptyCategories(const std::string& basePath);
    void removeSessionFromLog(const std::string& folderPath, const std::string& sessionId);
    std::string formatFileSize(std::uintmax_t size);
};
```

**Benefits**:

- File category mappings are protected from external modification
- Internal helper methods are hidden from public interface
- Class maintains control over its internal state


**Definition**: Hiding complex implementation details while exposing only essential features.

**Conceptual Implementation**:

**Location**: `src/fileorganizer.cpp`, lines 268-271

```cpp
```

**Benefits**:

- Users interact with simple methods like `organizeFolder()` without knowing the complex file system operations
- Complex file categorization logic is hidden behind a simple `getCategory()` method
- Error handling and edge cases are abstracted away from the public interface

### 3. Data Structures and Organization

**Definition**: Using appropriate data structures to organize and manage information effectively.

**Implementation in FileOrganizer**:

**Location**: `src/fileorganizer.cpp`, lines 36-40

```cpp
// Structure to track file movements for undo functionality
struct FileMove {
    std::string originalPath;
    std::string newPath;
    std::string timestamp;
};
```

**Location**: `src/fileorganizer.cpp`, lines 102-108

```cpp
        int totalFiles = 0;
        int processedFiles = 0;
        std::vector<FileMove> moves;

        // Count total files first
        for (const auto& entry : fs::directory_iterator(folderPath)) {
            if (entry.is_regular_file() && isValidFile(entry.path(), folderPath)) {
```

**Benefits**:

- Clear data structure (`FileMove`) represents file operations
- Vector container efficiently manages multiple file operations
- Structured approach to tracking undo information

### 4. Method Organization and Responsibility

**Definition**: Each method has a single, well-defined responsibility.

**Implementation in FileOrganizer**:

**Location**: `src/fileorganizer.cpp`, lines 69-95

```cpp
    void listFiles(const std::string& folderPath) {
        if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
            std::cout << "Error: Folder does not exist: " << folderPath << std::endl;
            return;
        }

        std::cout << "Files in " << folderPath << ":" << std::endl;
        std::cout << "----------------------------------------" << std::endl;

        for (const auto& entry : fs::directory_iterator(folderPath)) {
            if (entry.is_regular_file()) {
                std::string filename = entry.path().filename().string();
                std::string extension = entry.path().extension().string();
                std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

                std::string category = getCategory(extension);
                auto fileSize = fs::file_size(entry.path());

                std::cout << "  " << filename << " -> " << category << " (" << formatFileSize(fileSize) << ")" << std::endl;
            }
        }
    }
```

**Location**: `src/fileorganizer.cpp`, lines 285-304

```cpp
    bool isValidFile(const fs::path& filePath, const std::string& basePath) {
        std::string filename = filePath.filename().string();
        std::string parentDir = filePath.parent_path().filename().string();

        // Skip hidden files, log files, and files already in category folders
        if (filename[0] == '.' ||
            filename == ".fileorganizer_log.txt" ||
            parentDir == "Images" || parentDir == "Videos" ||
            parentDir == "Music" || parentDir == "Documents" ||
            parentDir == "Others") {
            return false;
        }

        return true;
    }
```

**Benefits**:

- `listFiles()` method has single responsibility: display file categorization preview
- `isValidFile()` method has single responsibility: determine if a file should be processed
- Each method is focused and easy to understand/maintain

### 5. Error Handling and Robustness

**Definition**: Implementing comprehensive error handling to make the system robust.

**Implementation in FileOrganizer**:

**Location**: `src/fileorganizer.cpp`, lines 132-145

```cpp
                try {
                    // Record the move for undo functionality
                    FileMove move;
                    move.originalPath = entry.path().string();
                    move.newPath = targetPath;
                    move.timestamp = sessionId;
                    moves.push_back(move);

                    fs::rename(entry.path(), targetPath);
                    processedFiles++;
                    std::cout << "✓ Moved: " << filename << " -> " << category << "/" << std::endl;

                    // Show progress
                    int percentage = (processedFiles * 100) / totalFiles;
                    std::cout << "Progress: " << processedFiles << "/" << totalFiles << " (" << percentage << "%)" << std::endl;
                } catch (const fs::filesystem_error& e) {
                    std::cout << "❌ Error moving " << filename << ": " << e.what() << std::endl;
                }
```

**Location**: `src/fileorganizer.cpp`, lines 238-246

```cpp
            try {
                if (fs::exists(move.newPath)) {
                    fs::rename(move.newPath, move.originalPath);
                    undoCount++;
                    std::cout << "✓ Restored: " << fs::path(move.originalPath).filename().string() << std::endl;
                } else {
                    std::cout << "⚠ File not found: " << fs::path(move.newPath).filename().string() << std::endl;
                }
            } catch (const fs::filesystem_error& e) {
                std::cout << "❌ Error restoring " << fs::path(move.originalPath).filename().string() << ": " << e.what() << std::endl;
            }
```

**Benefits**:

- Comprehensive try-catch blocks handle file system errors gracefully
- User-friendly error messages with clear indicators (✓, ❌, ⚠)
- Operations continue even if individual files fail

This simplified but effective OOP approach demonstrates that good design doesn't always require complex inheritance hierarchies. The single-class design with proper encapsulation, abstraction, and method organization provides a maintainable and extensible solution.

### Alternative OOP Architecture

If implementing a full OOP design, the system architecture could look like:

```
┌─────────────────────────────────────────────────────────┐
│                    User Interface                        │
│                                                         │
│  ┌─────────────────┐    ┌─────────────────────────────┐ │
│  │ Interactive CLI │    │   Command-Line Interface    │ │
│  │  (main function)│    │     (main function)         │ │
│  └─────────────────┘    └─────────────────────────────┘ │
└─────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────┐
│                 Core Application Logic                  │
│                                                         │
│  ┌──────────────────────────────────────────────────┐  │
│  │           SimpleFileOrganizer Class              │  │
│  │  • File Organization Logic                       │  │
│  │  • Undo Management                               │  │
│  │  • Session Tracking                              │  │
│  │  • Category Management                           │  │
│  └──────────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────┐
│                  Data Structures                        │
│                                                         │
│     ┌─────────────────┐    ┌─────────────────────────┐  │
│     │    FileMove     │    │  extensionCategories   │  │
│     │   Structure     │    │        Map              │  │
│     │ (Undo tracking) │    │   (File categorization) │  │
│     └─────────────────┘    └─────────────────────────┘  │
└─────────────────────────────────────────────────────────┘
                              │
                              ▼
┌─────────────────────────────────────────────────────────┐
│                 File System Layer                       │
│                                                         │
│  ┌──────────────────────────────────────────────────┐  │
│  │         C++17 Filesystem API                    │  │
│  │  • Directory Operations                         │  │
│  │  • File Movement                                │  │
│  │  • Path Validation                              │  │
│  └──────────────────────────────────────────────────┘  │
└─────────────────────────────────────────────────────────┘
```

### Class Relationships (OOP Design)

```cpp
// Actual project structure (single-file architecture)
main() function
├── Creates SimpleFileOrganizer instance
├── Parses command-line arguments
├── Calls appropriate methods based on user input
└── Handles interactive mode

SimpleFileOrganizer class
├── Contains extensionCategories map (private member)
├── Manages FileMove vector for undo operations
├── Provides public interface methods:
│   ├── listFiles()
│   ├── organizeFolder()
│   ├── undoOrganization()
│   └── showUndoHistory()
└── Contains private helper methods:
    ├── getCategory()
    ├── createCategoryFolders()
    ├── isValidFile()
    ├── getUniqueFilePath()
    ├── getCurrentTimestamp()
    ├── saveUndoLog()
    ├── removeEmptyCategories()
    ├── removeSessionFromLog()
    └── formatFileSize()


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
   ./build.bat
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
```

**Organize Files:**

```bash
```

**Undo Last Operation:**

```bash
```

**View Organization History:**

```bash
```

**Undo Specific Session:**

```bash
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

The current implementation uses a simple but effective map-based approach for file categorization:

**Location**: `src/fileorganizer.cpp`, lines 268-271

```cpp
}
```

**Location**: `src/fileorganizer.cpp`, lines 118-127

```cpp
// File processing loop showing how categorization is used
for (const auto& entry : fs::directory_iterator(folderPath)) {
    if (entry.is_regular_file() && isValidFile(entry.path(), folderPath)) {
        std::string filename = entry.path().filename().string();
        std::string extension = entry.path().extension().string();
        std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

        std::string category = getCategory(extension);
        std::string targetDir = folderPath + "/" + category;
        std::string targetPath = targetDir + "/" + filename;
```

### Session Management


}


    // Log entry format: timestamp|session_id|operation|from_path|to_path
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);


### Error Handling

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
````

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
