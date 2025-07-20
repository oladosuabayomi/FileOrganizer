# File Organizer - Technical Documentation

Version 1.0.0 - Production Release

## Table of Contents

1. [Problem Statement](#problem-statement)
2. [Project Overview](#project-overview)
3. [Benefits of the Solution](#benefits-of-the-solution)
4. [Web Interface](#web-interface)
5. [Architecture and Design](#architecture-and-design)
6. [Build System](#build-system)
7. [API Documentation](#api-documentation)
8. [Usage Examples](#usage-examples)
9. [Technical Implementation](#technical-implementation)
10. [Extension and Customization](#extension-and-customization)
11. [Command-Line Reference](#command-line-reference)
12. [Command-Line Troubleshooting](#command-line-troubleshooting)

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

- **Modern web interface** with responsive design and real-time progress tracking
- **Automatic file categorization** into predefined categories (Documents, Images, Music, Videos, Others)
- **Complete undo functionality** with detailed session tracking and selective restoration
- **Multiple interface options**: Web UI, interactive CLI, and command-line modes
- **Safe file operations** with comprehensive error handling and logging
- **Cross-platform compatibility** using C++17 filesystem API and Node.js
- **Zero external dependencies** for C++ core, web interface uses built-in Node.js modules
- **Professional command-line interface** with standard Unix-style arguments
- **Session-based operation tracking** for granular undo control
- **Optimized performance** with caching and efficient file operations

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

## Web Interface

### Overview

File Organizer includes a modern, responsive web interface that provides an intuitive alternative to the command-line interface. Built with standard web technologies (HTML5, CSS3, JavaScript, and Node.js), the web interface offers all the functionality of the command-line tool with enhanced user experience.

### Features

#### 🌟 User Interface Features

- **Modern Responsive Design**: Works seamlessly on desktop, tablet, and mobile devices
- **Real-time Progress Tracking**: Visual progress bars and live status updates during operations
- **File Preview**: See exactly what files will be organized before making changes
- **Interactive File Lists**: Click-to-select files and folders with visual feedback
- **Drag-and-Drop Support**: Intuitive file and folder selection (where supported by browser)
- **Dark/Light Theme**: Automatic theme detection with manual override options

#### 📁 File Management Features

- **Quick Folder Access**: One-click access to common directories:
  - Downloads folder
  - Desktop
  - Documents
  - Pictures
  - Custom folder selection
- **File Type Filtering**: Filter and preview files by category before organization
- **Batch Operations**: Select multiple files/folders for simultaneous processing
- **Safe Mode Preview**: Test organization logic without moving files

#### 🔄 History and Undo Features

- **Complete Organization History**: View all past organization sessions with timestamps
- **Session Details**: See exactly what files were moved in each session
- **Selective Undo**: Choose specific sessions to undo from an interactive list
- **Multi-session Undo**: Undo multiple sessions at once
- **Undo Confirmation**: Clear confirmation dialogs to prevent accidental reversals

#### ⚡ Performance Features

- **Asynchronous Operations**: Non-blocking file operations with progress feedback
- **Incremental Loading**: Handle large directories without freezing the interface
- **Background Processing**: Long-running operations continue in background
- **Status Persistence**: Operations continue even if browser window is refreshed

### Architecture

#### Frontend Stack

```text
┌─────────────────────────────────────────┐
│              Web Browser                │
├─────────────────────────────────────────┤
│  HTML5 + CSS3 + Vanilla JavaScript     │
├─────────────────────────────────────────┤
│           AJAX/Fetch API                │
├─────────────────────────────────────────┤
│         REST API Endpoints              │
└─────────────────────────────────────────┘
```

#### Backend Stack

```text
┌─────────────────────────────────────────┐
│           Node.js Server                │
├─────────────────────────────────────────┤
│        Express.js Framework            │
├─────────────────────────────────────────┤
│       C++ Binary Integration           │
├─────────────────────────────────────────┤
│      Filesystem Operations API         │
└─────────────────────────────────────────┘
```

### Getting Started

#### Prerequisites

- **Node.js**: Version 12.0 or higher (built-in modules only, no external dependencies)
- **Modern Web Browser**: Chrome 70+, Firefox 65+, Safari 12+, Edge 79+
- **File Organizer C++ Binary**: Must be built and available in `build/` directory

#### Installation and Setup

**Quick Start (Windows):**

```cmd
launch-web.bat
```

**Manual Start (All Platforms):**

```bash
# Navigate to web directory
cd web

# Start the server (Windows)
start.bat

# Start the server (Linux/macOS)
./start.sh
```

**Custom Configuration:**

```bash
# Start on custom port
node server.js --port 8080

# Enable debug mode
node server.js --debug

# Specify custom C++ binary path
node server.js --binary "../custom/path/FileOrganizer.exe"
```

#### Access the Interface

Once the server is running:

1. Open your web browser
2. Navigate to `http://localhost:3000` (or your custom port)
3. The interface will automatically load and detect your system

### API Endpoints

The web interface communicates with the backend through RESTful API endpoints:

#### File Operations

```javascript
// Get file list for a directory
GET /api/files?path=/path/to/directory

// Preview organization (without moving files)
POST /api/preview
Content-Type: application/json
{
  "path": "/path/to/directory"
}

// Execute organization
POST /api/organize
Content-Type: application/json
{
  "path": "/path/to/directory"
}
```

#### History Operations

```javascript
// Get organization history
GET /api/history?path=/path/to/directory

// Undo specific session
POST /api/undo
Content-Type: application/json
{
  "path": "/path/to/directory",
  "sessionId": "20250717_143022"
}

// Undo last organization
POST /api/undo-last
Content-Type: application/json
{
  "path": "/path/to/directory"
}
```

#### System Operations

```javascript
// Get system information
GET / api / system - info;

// Check server health
GET / api / health;

// Get supported file types
GET / api / file - types;
```

### File Structure

```text
web/
├── index.html              # Main interface HTML
├── styles.css              # Modern CSS with animations
├── app.js                  # Frontend JavaScript logic
├── server.js               # Node.js backend server
├── start.bat               # Windows startup script
├── start.sh                # Linux/macOS startup script
└── README.md               # Web interface documentation
```

### Configuration Options

#### Server Configuration

The web server supports several configuration options through environment variables or command-line arguments:

```javascript
// Default configuration
const config = {
  port: process.env.PORT || 3000,
  host: process.env.HOST || "localhost",
  binaryPath: process.env.BINARY_PATH || "../build/FileOrganizer",
  maxFileSize: process.env.MAX_FILE_SIZE || "100MB",
  timeout: process.env.TIMEOUT || 30000,
  debugMode: process.env.DEBUG === "true",
};
```

#### Client Configuration

```javascript
// Frontend configuration (in app.js)
const CLIENT_CONFIG = {
  apiBaseUrl: window.location.origin + "/api",
  pollInterval: 1000, // Status polling interval (ms)
  maxRetries: 3, // Max API retry attempts
  timeout: 30000, // Request timeout (ms)
  animationDuration: 300, // UI animation duration (ms)
};
```

### Security Considerations

#### Path Validation

- All file paths are validated and sanitized
- Directory traversal attacks are prevented
- Only accessible directories can be organized

#### File Operation Security

- Read-only preview mode available
- Confirmation required for destructive operations
- Comprehensive logging of all file movements
- Automatic backup creation before organization

#### Network Security

- Server binds to localhost only by default
- No authentication required for local access
- HTTPS support available for production deployments
- CORS headers configured for same-origin policy

### Troubleshooting

#### Common Issues

**Server Won't Start:**

1. Check if Node.js is installed: `node --version`
2. Verify port 3000 is available: `netstat -an | findstr :3000`
3. Ensure C++ binary exists: `ls build/FileOrganizer*`

**Interface Not Loading:**

1. Check browser console for JavaScript errors
2. Verify server is running: `curl http://localhost:3000/api/health`
3. Clear browser cache and reload

**File Operations Failing:**

1. Check file permissions in target directories
2. Verify sufficient disk space
3. Ensure C++ binary has execution permissions

#### Debug Mode

Enable debug mode for detailed logging:

```bash
# Enable debug logging
node server.js --debug

# View debug logs in browser console
# Press F12 → Console tab
```

#### Performance Optimization

For large directories (1000+ files):

1. Use preview mode first to verify organization
2. Enable incremental loading in browser settings
3. Consider organizing in smaller batches
4. Monitor system resources during operations

---

## Architecture and Design

**Definition**: Bundling data and methods together while controlling access to internal state.

**Conceptual Implementation**:

**Location**: `src/fileorganizer.cpp`, lines 42-67

```cpp
class SimpleFileOrganizer {
private:
    // Extension to category mapping for efficient file categorization
    std::map<std::string, std::string> extensionCategories = {
        // Images
        {".jpg", "Images"}, {".jpeg", "Images"}, {".png", "Images"},
        {".gif", "Images"}, {".bmp", "Images"}, {".tiff", "Images"},
        {".svg", "Images"}, {".webp", "Images"}, {".ico", "Images"},

        // Audio (categorized as "Music")
        {".mp3", "Music"}, {".wav", "Music"}, {".flac", "Music"},
        {".aac", "Music"}, {".ogg", "Music"}, {".wma", "Music"},
        {".m4a", "Music"}, {".opus", "Music"},

        // Video
        {".mp4", "Videos"}, {".avi", "Videos"}, {".mkv", "Videos"},
        {".mov", "Videos"}, {".wmv", "Videos"}, {".flv", "Videos"},
        {".webm", "Videos"}, {".m4v", "Videos"}, {".3gp", "Videos"},

        // Documents
        {".pdf", "Documents"}, {".doc", "Documents"}, {".docx", "Documents"},
        {".txt", "Documents"}, {".rtf", "Documents"}, {".odt", "Documents"},
        {".xls", "Documents"}, {".xlsx", "Documents"}, {".ppt", "Documents"},
        {".pptx", "Documents"}, {".csv", "Documents"}, {".md", "Documents"}
    };

public:
    // Public interface methods
    void listFiles(const std::string& folderPath);
    void organizeFolder(const std::string& folderPath);
    void undoOrganization(const std::string& folderPath, const std::string& sessionId = "");
    void showUndoHistory(const std::string& folderPath);

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

```text
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

````cpp
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

   ```cmd
   ./build.bat
   ```

   **Linux/Mac:**

   ```bash
   chmod +x run.sh
   ./run.sh
   ```

   **Option B: Direct Compilation**

   **Windows (MinGW/MSYS2):**

   ```cmd
   mkdir build
   g++ -std=c++17 -static-libgcc -static-libstdc++ -o build/FileOrganizer.exe src/fileorganizer.cpp
   ```

   **Linux/Mac:**

   ```bash
   mkdir build
   g++ -std=c++17 -static-libgcc -static-libstdc++ -O2 -Wall -Wextra -o build/FileOrganizer src/fileorganizer.cpp
   ```

### Build Notes

- **Static Linking**: The `-static` flag is recommended on Windows to avoid runtime library dependencies
- **Optimization**: Use `-O2` or `-O3` for release builds
- **Debug Builds**: Add `-g -DDEBUG` for debugging builds
- **Cross-Platform**: The code uses only standard C++17 features for maximum compatibility

---

## API Documentation

### SimpleFileOrganizer Class

The core `SimpleFileOrganizer` class provides all file organization functionality:

```cpp
class SimpleFileOrganizer {
public:
    // Main operations
    void listFiles(const std::string& folderPath);
    void organizeFolder(const std::string& folderPath);
    void undoOrganization(const std::string& folderPath, const std::string& sessionId = "");
    void showUndoHistory(const std::string& folderPath);

private:
    // File categorization map
    std::map<std::string, std::string> extensionCategories;

    // Helper methods
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

### Method Details

#### `listFiles(const std::string& folderPath)`

- **Purpose**: Lists all files in the directory with their current and target categories
- **Parameters**: `folderPath` - Path to the directory to analyze
- **Output**: Displays files categorized by type with size information

#### `organizeFolder(const std::string& folderPath)`

- **Purpose**: Organizes all files in the directory into category folders
- **Parameters**: `folderPath` - Path to the directory to organize
- **Side Effects**: Creates category folders and moves files, generates session log

#### `undoOrganization(const std::string& folderPath, const std::string& sessionId)`

- **Purpose**: Undoes a previous organization operation
- **Parameters**:
  - `folderPath` - Path to the directory to restore
  - `sessionId` - Specific session to undo (optional, defaults to last session)
- **Side Effects**: Moves files back to original locations, removes empty category folders

#### `showUndoHistory(const std::string& folderPath)`

- **Purpose**: Displays the history of organization sessions for a directory
- **Parameters**: `folderPath` - Path to the directory
- **Output**: Lists all available sessions with timestamps and file counts

---

## Usage Examples

**Note**: The following examples show Windows commands with `.exe` extension. For Linux/macOS, remove the `.exe` extension and use forward slashes for paths.

### Usage Modes

#### 1. Interactive Mode (Recommended for Beginners)

```cmd
build\FileOrganizer.exe --interactive
```

**Interactive Session Example:**

```
=== FileOrganizer CLI - Interactive Mode ===

Commands:
  1. Organize folder
  2. List files in folder
  3. Undo last organization
  4. Show organization history
  5. Exit

Enter your choice (1-5): 1
Enter folder path to organize: C:\Users\hp\Downloads

Starting file organization in: C:\Users\hp\Downloads
Session ID: 20250117_143022
Scanning files... Found 25 files to organize.
Processing files:
Progress: 10/25 (40%)
Progress: 20/25 (80%)
Progress: 25/25 (100%)
File organization completed! Processed 25 files.
To undo: --undo "C:\Users\hp\Downloads" 20250117_143022
```

#### 2. Command-Line Mode (For Automation)

**List Files Before Organizing:**

```cmd
build\FileOrganizer.exe --list "C:\Users\hp\Downloads"
```

**Organize Files:**

```cmd
build\FileOrganizer.exe --organize "C:\Users\hp\Downloads"
```

**Undo Last Operation:**

```cmd
build\FileOrganizer.exe --undo "C:\Users\hp\Downloads"
```

**View Organization History:**

```cmd
build\FileOrganizer.exe --history "C:\Users\hp\Downloads"
```

**Undo Specific Session:**

```cmd
build\FileOrganizer.exe --undo "C:\Users\hp\Downloads" 20250117_143022
```

### Understanding the Output

#### File Listing

```
Files in C:\Users\hp\Downloads:
----------------------------------------
  document.pdf -> Documents (1.2 MB)
  photo.jpg -> Images (3.4 MB)
  song.mp3 -> Music (4.1 MB)
  video.mp4 -> Videos (15.7 MB)
  archive.zip -> Others (2.3 MB)
```

#### Organization Process

```
Starting file organization in: C:\Users\hp\Downloads
Session ID: 20250117_143022
Scanning files... Found 5 files to organize.
Processing files:
Progress: 3/5 (60%)
Progress: 5/5 (100%)
File organization completed! Processed 5 files.
To undo: --undo "C:\Users\hp\Downloads" 20250117_143022
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
Removed empty folder: Music
Removed empty folder: Images
Removed empty folder: Documents
----------------------------------------
Undo completed! Restored 5 files.
```

### File Categories

The application automatically categorizes files into these folders based on file extensions:

| Category      | Extensions                                                               |
| ------------- | ------------------------------------------------------------------------ |
| **Documents** | .pdf, .doc, .docx, .txt, .rtf, .odt, .xls, .xlsx, .ppt, .pptx, .csv, .md |
| **Images**    | .jpg, .jpeg, .png, .gif, .bmp, .tiff, .svg, .webp, .ico                  |
| **Music**     | .mp3, .wav, .flac, .aac, .ogg, .m4a, .wma, .opus                         |
| **Videos**    | .mp4, .avi, .mkv, .mov, .wmv, .flv, .webm, .m4v, .3gp                    |
| **Others**    | All other file types                                                     |

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

     ```cmd
     @echo off
     echo Organizing Downloads folder...
     build\FileOrganizer.exe --organize "C:\Users\%USERNAME%\Downloads"
     echo Done!
     ```

### 3. Web Interface Mode (Recommended for Most Users)

The web interface provides the most user-friendly experience with visual feedback and point-and-click operation.

#### Starting the Web Interface

**Quick Start (Windows):**

```cmd
launch-web.bat
```

**Manual Start:**

```cmd
cd web
start.bat
```

#### Web Interface Workflow

##### Step 1: Access the Interface

1. Open your web browser
2. Navigate to `http://localhost:3000`
3. The interface loads with a clean, modern design

##### Step 2: Select Directory

- **Quick Folders**: Click on predefined buttons for common directories:
  - Downloads
  - Desktop
  - Documents
  - Pictures
- **Custom Path**: Type or paste any directory path
- **Browse**: Use the folder selection dialog (where supported)

##### Step 3: Preview Organization

- Click "Preview Organization" to see what changes will be made
- Review the file categorization in an interactive list
- Files are grouped by destination category
- Each file shows size and current location

##### Step 4: Execute Organization

- Click "Organize Files" after reviewing the preview
- Watch real-time progress with animated progress bars
- See detailed status messages as files are processed
- Get immediate confirmation when organization completes

##### Step 5: Manage History

- Click "Undo Last" to access the undo interface
- Select from a list of recent organization sessions
- Each session shows timestamp and number of files moved
- Choose specific sessions to undo with confirmation dialogs

#### Example Web Workflow

**Organizing Downloads Folder:**

1. **Initial State**: Downloads folder contains mixed files
2. **Access Interface**: Open `http://localhost:3000`
3. **Select Downloads**: Click the "Downloads" quick folder button
4. **Preview**: Click "Preview Organization"
   - Interface shows: "25 files will be organized"
   - Categories preview:
     - Documents: 8 files (PDF, DOCX, TXT)
     - Images: 12 files (JPG, PNG, GIF)
     - Videos: 3 files (MP4, AVI)
     - Music: 2 files (MP3, FLAC)
5. **Execute**: Click "Organize Files"
   - Progress bar shows real-time completion
   - Status updates: "Processing file 15 of 25..."
   - Completion: "Organization complete! 25 files organized."
6. **Verify**: Browse the Downloads folder to see organized subdirectories

**Undoing Organization:**

1. **Access Undo**: Click "Undo Last" button
2. **Select Session**: Choose from list:
   - `20250717_143022` - 25 files moved
   - `20250716_092015` - 12 files moved
   - `20250715_160430` - 8 files moved
3. **Confirm Undo**: Select desired session and click "Undo Selected"
4. **Progress**: Watch progress bar as files are restored
5. **Complete**: "Undo complete! 25 files restored."

#### Web Interface Features in Action

**Real-time Progress Tracking:**

```text
╭─────────────────────────────────────────╮
│ Organizing Files...                     │
│ ████████████████████░░░  83% (20/24)   │
│ Processing: vacation_photo.jpg          │
│ Status: Moving to Images folder         │
╰─────────────────────────────────────────╯
```

**Interactive File Preview:**

```text
Documents (8 files)
├── 📄 report.pdf (2.1 MB)
├── 📄 invoice.docx (145 KB)
└── 📄 notes.txt (12 KB)

Images (12 files)
├── 🖼️ vacation_001.jpg (3.2 MB)
├── 🖼️ vacation_002.jpg (2.8 MB)
└── 🖼️ screenshot.png (892 KB)
```

**Organization History:**

```text
Recent Organization Sessions:
┌─────────────────────────────────────────┐
│ ⭐ 20250717_143022 (2 hours ago)       │
│    25 files moved • Downloads          │
├─────────────────────────────────────────┤
│   20250716_092015 (Yesterday)          │
│    12 files moved • Desktop            │
├─────────────────────────────────────────┤
│   20250715_160430 (2 days ago)         │
│    8 files moved • Downloads           │
└─────────────────────────────────────────┘
```

#### Advanced Web Features

**Bulk Operations:**

- Select multiple directories for batch organization
- Queue multiple operations with progress tracking
- Cancel long-running operations if needed

**Smart Categorization:**

- Visual preview of file movements before execution
- Custom category rules (when available)
- Conflict resolution for duplicate filenames

**Responsive Design:**

- Works on desktop, tablet, and mobile devices
- Touch-friendly interface for mobile users
- Adaptive layout based on screen size

**Accessibility Features:**

- Keyboard navigation support
- Screen reader compatibility
- High contrast mode support
- Clear focus indicators

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

**Location**: `src/fileorganizer.cpp`, lines 302-318

```cpp
std::string getCategory(const std::string& extension) {
    // Use static cache for repeated extension lookups
    static std::unordered_map<std::string, std::string> categoryCache;

    // Check cache first for better performance
    auto cacheIt = categoryCache.find(extension);
    if (cacheIt != categoryCache.end()) {
        return cacheIt->second;
    }

    // Not in cache, look up in main map
    auto it = extensionCategories.find(extension);
    std::string category = (it != extensionCategories.end()) ? it->second : "Others";

    // Add to cache for future lookups
    categoryCache[extension] = category;

    return category;
}
```

**Location**: `src/fileorganizer.cpp`, lines 118-180

```cpp
// File processing loop showing how categorization is used
void organizeFolder(const std::string& folderPath) {
    // ... validation and setup code ...

    for (const auto& entry : filesToProcess) {
        std::string filename = entry.path().filename().string();
        std::string extension = entry.path().extension().string();
        std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);

        std::string category = getCategory(extension);
        std::string targetDir = folderPath + "/" + category;
        std::string targetPath = targetDir + "/" + filename;

        // Handle file name conflicts
        targetPath = getUniqueFilePath(targetPath);

        try {
            // Record the move for undo functionality
            FileMove move;
            move.originalPath = entry.path().string();
            move.newPath = targetPath;
            move.timestamp = sessionId;
            moves.push_back(move);

            fs::rename(entry.path(), targetPath);
            processedFiles++;

            // Show progress at intervals
            int percentage = (processedFiles * 100) / totalFiles;
            if (percentage != lastProgress && (percentage % 10 == 0 || processedFiles % 100 == 0)) {
                std::cout << "Progress: " << processedFiles << "/" << totalFiles
                         << " (" << percentage << "%)" << std::endl;
                lastProgress = percentage;
            }

        } catch (const fs::filesystem_error& e) {
            std::cout << "Error moving " << filename << ": " << e.what() << std::endl;
        }
    }

    // Save move log for undo functionality
    saveUndoLog(folderPath, moves, sessionId);
}
```

### Session Management

**Location**: `src/fileorganizer.cpp`, lines 380-410

```cpp
void saveUndoLog(const std::string& folderPath, const std::vector<FileMove>& moves, const std::string& sessionId) {
    if (moves.empty()) {
        return; // No moves to log
    }

    std::string logFile = folderPath + "/.fileorganizer_log.txt";

    // Pre-allocate a string buffer for better performance with many files
    std::stringstream buffer;
    buffer << "SESSION:" << sessionId << std::endl;

    for (const auto& move : moves) {
        buffer << move.originalPath << "|" << move.newPath << "|" << move.timestamp << std::endl;
    }
    buffer << "END_SESSION:" << sessionId << std::endl;

    // Single write operation for better performance
    std::ofstream logStream(logFile, std::ios::app);
    if (logStream.is_open()) {
        logStream << buffer.str();
        logStream.close();
    }
}

std::string getCurrentTimestamp() {
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y%m%d_%H%M%S");
    return oss.str();
}
```

### Error Handling

**Location**: `src/fileorganizer.cpp`, lines 150-180

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

    // Show progress at intervals for better performance
    int percentage = (processedFiles * 100) / totalFiles;
    if (percentage != lastProgress && (percentage % 10 == 0 || processedFiles % 100 == 0)) {
        std::cout << "Progress: " << processedFiles << "/" << totalFiles
                 << " (" << percentage << "%)" << std::endl;
        lastProgress = percentage;
    }

} catch (const fs::filesystem_error& e) {
    std::cout << "Error moving " << filename << ": " << e.what() << std::endl;
}
```

**Location**: `src/fileorganizer.cpp`, lines 270-290

```cpp
// Undo operation with comprehensive error handling
for (const auto& move : movesToUndo) {
    try {
        if (fs::exists(move.newPath)) {
            fs::rename(move.newPath, move.originalPath);
            undoCount++;
            std::cout << "✓ Restored: " << fs::path(move.originalPath).filename().string() << std::endl;
        } else {
            std::cout << "⚠ File not found: " << fs::path(move.newPath).filename().string() << std::endl;
        }
    } catch (const fs::filesystem_error& e) {
        std::cout << "❌ Error restoring " << fs::path(move.originalPath).filename().string()
                 << ": " << e.what() << std::endl;
    }
}
```

---

## Extension and Customization

### Adding New File Categories

To add support for new file types, modify the category mapping in `fileorganizer.cpp`:

```cpp
// In the extensionCategories map within SimpleFileOrganizer class
std::map<std::string, std::string> extensionCategories = {
    // Images
    {".jpg", "Images"}, {".jpeg", "Images"}, {".png", "Images"},
    {".gif", "Images"}, {".bmp", "Images"}, {".tiff", "Images"},
    {".svg", "Images"}, {".webp", "Images"}, {".ico", "Images"},

    // Audio (categorized as "Music")
    {".mp3", "Music"}, {".wav", "Music"}, {".flac", "Music"},
    {".aac", "Music"}, {".ogg", "Music"}, {".wma", "Music"},
    {".m4a", "Music"}, {".opus", "Music"},

    // Video
    {".mp4", "Videos"}, {".avi", "Videos"}, {".mkv", "Videos"},
    {".mov", "Videos"}, {".wmv", "Videos"}, {".flv", "Videos"},
    {".webm", "Videos"}, {".m4v", "Videos"}, {".3gp", "Videos"},

    // Documents
    {".pdf", "Documents"}, {".doc", "Documents"}, {".docx", "Documents"},
    {".txt", "Documents"}, {".rtf", "Documents"}, {".odt", "Documents"},
    {".xls", "Documents"}, {".xlsx", "Documents"}, {".ppt", "Documents"},
    {".pptx", "Documents"}, {".csv", "Documents"}, {".md", "Documents"},

    // New categories can be added here
    {".zip", "Archives"}, {".rar", "Archives"}, {".7z", "Archives"},
    {".cpp", "Code"}, {".h", "Code"}, {".py", "Code"}, {".js", "Code"}
};
```

### Custom Organization Rules

For more complex organization logic, extend the `getCategory` method:

```cpp
std::string getCategory(const std::string& extension) {
    // Use static cache for repeated extension lookups
    static std::unordered_map<std::string, std::string> categoryCache;

    // Check cache first for better performance
    auto cacheIt = categoryCache.find(extension);
    if (cacheIt != categoryCache.end()) {
        return cacheIt->second;
    }

    // Not in cache, look up in main map
    auto it = extensionCategories.find(extension);
    std::string category = (it != extensionCategories.end()) ? it->second : "Others";

    // Custom rules can be added here
    if (category == "Others") {
        // Special handling for unknown extensions
        if (extension == ".exe" || extension == ".msi" || extension == ".app") {
            category = "Executables";
        } else if (extension == ".ini" || extension == ".cfg" || extension == ".conf") {
            category = "Configuration";
        }
    }

    // Add to cache for future lookups
    categoryCache[extension] = category;

    return category;
}
```

### Integration with Build Systems

The File Organizer can be integrated into build systems for automated cleanup:

**Windows Batch Script:**

```cmd
@echo off
echo Organizing project files...
build\FileOrganizer.exe --organize ".\downloads"
echo File organization complete!
```

**Linux/Mac Shell Script:**

```bash
#!/bin/bash
echo "Organizing project files..."
./build/FileOrganizer --organize "./downloads"
echo "File organization complete!"
```

**Task Automation:**

```cmd
REM Add to Windows Task Scheduler or cron job
build\FileOrganizer.exe --organize "C:\Users\%USERNAME%\Downloads"
```

---

## Command-Line Reference

### Available Commands

```text
FileOrganizer.exe [COMMAND] [OPTIONS]

Commands:
  --help                    Show help information
  --interactive             Start interactive mode
  --organize <path>         Organize files in specified directory
  --list <path>            List files and their target categories
  --undo <path> [session]  Undo organization (optionally specify session ID)
  --history <path>         Show organization history for directory

Examples:
  FileOrganizer.exe --help
  FileOrganizer.exe --interactive
  FileOrganizer.exe --organize "C:\Users\hp\Downloads"
  FileOrganizer.exe --list "C:\Users\hp\Downloads"
  FileOrganizer.exe --undo "C:\Users\hp\Downloads"
  FileOrganizer.exe --undo "C:\Users\hp\Downloads" 20250117_143022
  FileOrganizer.exe --history "C:\Users\hp\Downloads"
```

---

## Command-Line Troubleshooting

### Build and Installation Issues

1. **"g++ not found" during build**

   - Install MinGW-w64 or MSYS2 on Windows
   - Install build-essential on Linux: `sudo apt-get install build-essential`
   - Install Xcode command line tools on macOS: `xcode-select --install`

2. **"Permission denied" errors**

   - Run as administrator on Windows
   - Use `sudo` on Linux/macOS if needed
   - Check file permissions in target directory

3. **Files not being organized**

   - Ensure files are not hidden (starting with '.')
   - Check that files are not already in category folders
   - Verify directory path is correct

4. **Undo not working**
   - Check if `.fileorganizer_log.txt` exists in the directory
   - Verify session ID is correct
   - Ensure files haven't been manually moved after organization

### Performance Tips

- For large directories (1000+ files), organization may take a few minutes
- Progress is shown at 10% intervals during processing
- Use `--list` first to preview organization before running `--organize`
- Log files are automatically created and managed - no user intervention needed
````
