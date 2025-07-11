# FileOrganizer - Technical Documentation

## Table of Contents

1. [Problem Statement](#problem-statement)
2. [Project Overview](#project-overview)
3. [Benefits of the Solution](#benefits-of-the-solution)
4. [Object-Oriented Programming Principles](#object-oriented-programming-principles)
5. [Architecture and Design](#architecture-and-design)
6. [How to Use the Project](#how-to-use-the-project)
7. [Code Examples](#code-examples)
8. [Technical Implementation](#technical-implementation)

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

FileOrganizer is a C++ command-line application that automatically categorizes and organizes files in a directory based on their file extensions. The application uses Object-Oriented Programming principles to create a maintainable, extensible, and robust file management system.

### Key Features

- **Automatic file categorization** into predefined categories (Documents, Images, Music, Videos, Others)
- **Undo functionality** with session-based tracking
- **Interactive and command-line modes** for different user preferences
- **Safe file operations** with comprehensive error handling
- **Cross-platform compatibility** using C++17 filesystem API
- **Extensible design** allowing easy addition of new file types and categories

### Target Users

- **Home users** with cluttered download folders
- **Photographers** organizing large image collections
- **Content creators** managing mixed media files
- **Students** organizing academic documents
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

   - Handles directories with thousands of files
   - Efficient processing with progress tracking
   - Memory-efficient operation

3. **User Experience**
   - Consistent interface across different usage modes
   - Clear feedback and progress indicators
   - Comprehensive help and documentation

---

## Object-Oriented Programming Principles

FileOrganizer demonstrates all four core OOP principles through its architecture:

### 1. Abstraction

**Definition**: Hiding complex implementation details while exposing only essential features.

**Implementation in FileOrganizer**:

```cpp
// File.h - Abstract base class
class File {
public:
    virtual ~File() = default;
    virtual QString getCategory() const = 0;  // Pure virtual function
    virtual bool isValidType(const QString& extension) const = 0;

    // Common interface for all file types
    QString getFilePath() const { return filePath; }
    QString getFileName() const { return fileName; }
    qint64 getFileSize() const { return fileSize; }

protected:
    QString filePath;
    QString fileName;
    qint64 fileSize;
};
```

**Benefits**:

- Users interact with files through a simple, consistent interface
- Complex file type detection logic is hidden
- Easy to work with different file types uniformly

### 2. Encapsulation

**Definition**: Bundling data and methods together while controlling access to internal state.

**Implementation in FileOrganizer**:

```cpp
// ImageFile.cpp - Data and methods encapsulated
class ImageFile : public File {
private:
    // Private data members - controlled access
    static const QStringList validExtensions;
    QString resolution;
    QString colorDepth;

public:
    // Public interface controls access to data
    QString getCategory() const override { return "Images"; }

    bool isValidType(const QString& extension) const override {
        return validExtensions.contains(extension.toLower());
    }

    // Controlled access to internal data
    QString getResolution() const { return resolution; }
    void setResolution(const QString& res) { resolution = res; }

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

### 3. Inheritance

**Definition**: Creating new classes based on existing classes, inheriting properties and methods.

**Implementation in FileOrganizer**:

```cpp
// Base class
class File {
    // Common functionality for all files
};

// Derived classes inherit from File
class DocumentFile : public File {
public:
    QString getCategory() const override { return "Documents"; }
    bool isValidType(const QString& extension) const override {
        // Document-specific validation
    }
};

class AudioFile : public File {
public:
    QString getCategory() const override { return "Music"; }
    bool isValidType(const QString& extension) const override {
        // Audio-specific validation
    }
};

class VideoFile : public File {
public:
    QString getCategory() const override { return "Videos"; }
    bool isValidType(const QString& extension) const override {
        // Video-specific validation
    }
};

class ImageFile : public File {
public:
    QString getCategory() const override { return "Images"; }
    bool isValidType(const QString& extension) const override {
        // Image-specific validation
    }
};
```

**Benefits**:

- Code reuse: Common file operations defined once in base class
- Consistent interface: All file types share the same basic structure
- Easy extension: New file types can be added by inheriting from File

### 4. Polymorphism

**Definition**: Objects of different types can be treated uniformly through a common interface.

**Implementation in FileOrganizer**:

```cpp
// FileHandler.cpp - Polymorphism in action
void FileHandler::organizeFolder(const QString& folderPath) {
    QDir dir(folderPath);
    QFileInfoList fileList = dir.entryInfoList(QDir::Files);

    for (const QFileInfo& fileInfo : fileList) {
        // Create appropriate file object based on extension
        std::unique_ptr<File> file = createFileObject(fileInfo);

        if (file) {
            // Polymorphic call - different behavior for each file type
            QString category = file->getCategory();  // Calls appropriate override
            bool isValid = file->isValidType(fileInfo.suffix());  // Polymorphic

            if (isValid) {
                moveFileToCategory(file.get(), category);
            }
        }
    }
}

std::unique_ptr<File> FileHandler::createFileObject(const QFileInfo& fileInfo) {
    QString extension = fileInfo.suffix().toLower();

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
```

**Benefits**:

- Single code path handles all file types uniformly
- Easy to add new file types without modifying existing code
- Runtime behavior determined by actual object type

---

## Architecture and Design

### System Architecture

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

### Class Relationships

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

SimpleFileOrganizer (Main Application)
├── Contains FileHandler (Composition)
├── Manages user interface
└── Coordinates application flow
```

---

## How to Use the Project

### Prerequisites

- C++ compiler with C++17 support (g++, clang++, MSVC)
- Windows, Linux, or macOS operating system

### Installation

1. **Clone the Repository**

   ```bash
   git clone https://github.com/yourusername/FileOrganizer.git
   cd FileOrganizer
   ```

2. **Build the Application**

   **Windows:**

   ```bash
   build.bat
   ```

   **Linux/Mac:**

   ```bash
   chmod +x run.sh
   ./run.sh
   ```

### Usage Modes

#### 1. Interactive Mode (Recommended for Beginners)

```bash
./build/FileOrganizerWithUndo.exe --interactive
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
Enter folder path to organize: C:\Users\John\Downloads

Starting file organization in: C:\Users\John\Downloads
Session ID: 20250711_143022
Found 25 files to organize.
----------------------------------------
✓ Moved: report.pdf -> Documents/
Progress: 1/25 (4%)
✓ Moved: vacation.jpg -> Images/
Progress: 2/25 (8%)
...
----------------------------------------
File organization completed! Processed 25 files.
To undo this operation, use: --undo "C:\Users\John\Downloads" 20250711_143022
```

#### 2. Command-Line Mode (For Automation)

**List Files Before Organizing:**

```bash
./build/FileOrganizerWithUndo.exe --list "C:\Users\John\Downloads"
```

**Organize Files:**

```bash
./build/FileOrganizerWithUndo.exe --organize "C:\Users\John\Downloads"
```

**Undo Last Operation:**

```bash
./build/FileOrganizerWithUndo.exe --undo "C:\Users\John\Downloads"
```

**View Organization History:**

```bash
./build/FileOrganizerWithUndo.exe --history "C:\Users\John\Downloads"
```

**Undo Specific Session:**

```bash
./build/FileOrganizerWithUndo.exe --undo "C:\Users\John\Downloads" 20250711_143022
```

### Understanding the Output

#### File Listing

```
Files in C:\Users\John\Downloads:
----------------------------------------
  document.pdf -> Documents (1.2 MB)
  photo.jpg -> Images (3.4 MB)
  song.mp3 -> Music (4.1 MB)
  video.mp4 -> Videos (15.7 MB)
  archive.zip -> Others (2.3 MB)
```

#### Organization Process

```
Starting file organization in: C:\Users\John\Downloads
Session ID: 20250711_143022
Found 5 files to organize.
----------------------------------------
✓ Moved: document.pdf -> Documents/
Progress: 1/5 (20%)
✓ Moved: photo.jpg -> Images/
Progress: 2/5 (40%)
✓ Moved: song.mp3 -> Music/
Progress: 3/5 (60%)
✓ Moved: video.mp4 -> Videos/
Progress: 4/5 (80%)
✓ Moved: archive.zip -> Others/
Progress: 5/5 (100%)
----------------------------------------
File organization completed! Processed 5 files.
To undo this operation, use: --undo "C:\Users\John\Downloads" 20250711_143022
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
     # Organize multiple folders
     ./build/FileOrganizerWithUndo.exe --organize "/home/user/Downloads"
     ./build/FileOrganizerWithUndo.exe --organize "/home/user/Desktop"
     ```

---

## Code Examples

### Adding a New File Type

To demonstrate the extensibility of the OOP design, here's how to add a new file type:

```cpp
// Step 1: Create new file type class
// src/core/ArchiveFile.h
#ifndef ARCHIVEFILE_H
#define ARCHIVEFILE_H

#include "File.h"
#include <QStringList>

class ArchiveFile : public File {
public:
    ArchiveFile();

    QString getCategory() const override;
    bool isValidType(const QString& extension) const override;

    // Archive-specific methods
    QString getCompressionType() const;
    bool isPasswordProtected() const;

private:
    static const QStringList validExtensions;
    QString compressionType;
    bool passwordProtected;

    void detectArchiveProperties();
};

#endif // ARCHIVEFILE_H
```

```cpp
// src/core/ArchiveFile.cpp
#include "ArchiveFile.h"

const QStringList ArchiveFile::validExtensions = {
    ".zip", ".rar", ".7z", ".tar", ".gz", ".bz2", ".xz"
};

ArchiveFile::ArchiveFile() : passwordProtected(false) {
    // Initialize archive-specific properties
}

QString ArchiveFile::getCategory() const {
    return "Archives";
}

bool ArchiveFile::isValidType(const QString& extension) const {
    return validExtensions.contains(extension.toLower());
}

QString ArchiveFile::getCompressionType() const {
    return compressionType;
}

bool ArchiveFile::isPasswordProtected() const {
    return passwordProtected;
}

void ArchiveFile::detectArchiveProperties() {
    // Implementation for detecting archive properties
}
```

```cpp
// Step 2: Update FileHandler to use new type
// In FileHandler::createFileObject(), add:
else if (ArchiveFile().isValidType(extension)) {
    return std::make_unique<ArchiveFile>();
}
```

### Custom File Processing

```cpp
// Example of polymorphic processing
void FileHandler::processSpecialFiles(const QStringList& filePaths) {
    for (const QString& filePath : filePaths) {
        QFileInfo fileInfo(filePath);
        std::unique_ptr<File> file = createFileObject(fileInfo);

        if (file) {
            // Polymorphic behavior based on actual file type
            QString category = file->getCategory();

            // Type-specific processing
            if (auto* imageFile = dynamic_cast<ImageFile*>(file.get())) {
                // Special processing for images
                processImageMetadata(imageFile);
            }
            else if (auto* audioFile = dynamic_cast<AudioFile*>(file.get())) {
                // Special processing for audio
                processAudioTags(audioFile);
            }

            // Common processing for all types
            moveFileToCategory(file.get(), category);
        }
    }
}
```

---

## Technical Implementation

### File Detection Algorithm

```cpp
// Simplified version of the file detection logic
std::unique_ptr<File> FileHandler::createFileObject(const QFileInfo& fileInfo) {
    QString extension = fileInfo.suffix().toLower();

    // Use polymorphism to determine file type
    std::vector<std::unique_ptr<File>> fileTypes = {
        std::make_unique<ImageFile>(),
        std::make_unique<AudioFile>(),
        std::make_unique<VideoFile>(),
        std::make_unique<DocumentFile>()
    };

    for (auto& fileType : fileTypes) {
        if (fileType->isValidType(extension)) {
            // Return copy of the matching type
            return std::unique_ptr<File>(fileType.release());
        }
    }

    return nullptr; // Unknown file type -> "Others" category
}
```

### Session Management

```cpp
// Session tracking for undo functionality
class SessionManager {
private:
    struct FileOperation {
        QString originalPath;
        QString newPath;
        QString timestamp;
        QString sessionId;
    };

    std::vector<FileOperation> operations;
    QString logFilePath;

public:
    QString createSession() {
        QDateTime now = QDateTime::currentDateTime();
        return now.toString("yyyyMMdd_hhmmss");
    }

    void logOperation(const QString& sessionId,
                     const QString& originalPath,
                     const QString& newPath) {
        FileOperation op = {originalPath, newPath,
                           QDateTime::currentDateTime().toString(),
                           sessionId};
        operations.push_back(op);
        writeToLogFile(op);
    }

    bool undoSession(const QString& sessionId) {
        // Implementation for session-based undo
        return true;
    }
};
```

### Error Handling

```cpp
// Robust error handling throughout the application
bool FileHandler::moveFileToCategory(const QString& filePath,
                                   const QString& category) {
    try {
        QFileInfo fileInfo(filePath);
        QString targetDir = createCategoryDirectory(category);
        QString targetPath = targetDir + "/" + fileInfo.fileName();

        // Check for conflicts
        if (QFile::exists(targetPath)) {
            targetPath = resolveNameConflict(targetPath);
        }

        // Perform the move operation
        if (QFile::rename(filePath, targetPath)) {
            // Log successful operation
            sessionManager->logOperation(currentSessionId, filePath, targetPath);
            emit fileProcessed(fileInfo.fileName(), category);
            return true;
        } else {
            // Handle move failure
            emit errorOccurred("Failed to move file: " + filePath);
            return false;
        }

    } catch (const std::exception& e) {
        emit errorOccurred("Exception occurred: " + QString(e.what()));
        return false;
    }
}
```

This documentation demonstrates how FileOrganizer effectively implements all four OOP principles while solving a real-world problem through clean, maintainable code architecture.
