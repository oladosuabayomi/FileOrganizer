/*
 * FileOrganizer - Simple File Organization Tool with Undo Functionality
 * 
 * MIT License
 * Copyright (c) 2025 FileOrganizer Project
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <map>
#include <algorithm>
#include <fstream>
#include <ctime>
#include <unordered_map>
#include <iomanip>
#include <sstream>

namespace fs = std::filesystem;

// Structure to track file movements for undo functionality
struct FileMove {
    std::string originalPath;
    std::string newPath;
    std::string timestamp;
};

class SimpleFileOrganizer {
private:
    std::map<std::string, std::string> extensionCategories = {
        // Images
        {".jpg", "Images"}, {".jpeg", "Images"}, {".png", "Images"}, 
        {".gif", "Images"}, {".bmp", "Images"}, {".tiff", "Images"},
        {".svg", "Images"}, {".webp", "Images"}, {".ico", "Images"},
        
        // Audio
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
    void listFiles(const std::string& folderPath) {
        if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
            std::cout << "Error: Folder does not exist: " << folderPath << std::endl;
            return;
        }

        std::cout << "Files in " << folderPath << ":" << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        
        // Use a vector to collect entries before processing (faster iteration)
        std::vector<fs::directory_entry> entries;
        for (const auto& entry : fs::directory_iterator(folderPath)) {
            if (entry.is_regular_file()) {
                entries.push_back(entry);
            }
        }
        
        // Cache extension mappings for this run
        std::unordered_map<std::string, std::string> extensionCache;
        
        // Process files efficiently with minimal I/O operations
        for (const auto& entry : entries) {
            std::string filename = entry.path().filename().string();
            std::string extension = entry.path().extension().string();
            std::transform(extension.begin(), extension.end(), extension.begin(), ::tolower);
            
            // Use cached category if available
            std::string category;
            auto cacheIt = extensionCache.find(extension);
            if (cacheIt != extensionCache.end()) {
                category = cacheIt->second;
            } else {
                category = getCategory(extension);
                extensionCache[extension] = category;  // Cache for future use
            }
            
            auto fileSize = entry.file_size(); // More efficient than fs::file_size
            
            std::cout << "  " << filename << " -> " << category << " (" << formatFileSize(fileSize) << ")" << std::endl;
        }
    }

    void organizeFolder(const std::string& folderPath) {
        if (!fs::exists(folderPath) || !fs::is_directory(folderPath)) {
            std::cout << "Error: Folder does not exist: " << folderPath << std::endl;
            return;
        }

        std::cout << "Starting file organization in: " << folderPath << std::endl;
        
        // Create session ID for this organization session
        std::string sessionId = getCurrentTimestamp();
        std::cout << "Session ID: " << sessionId << std::endl;
        
        // Create category folders
        createCategoryFolders(folderPath);
        
        std::vector<FileMove> moves;
        std::vector<fs::directory_entry> filesToProcess;
        
        // Single pass: collect all valid files
        std::cout << "Scanning files..." << std::flush;
        for (const auto& entry : fs::directory_iterator(folderPath)) {
            if (entry.is_regular_file() && isValidFile(entry.path(), folderPath)) {
                filesToProcess.push_back(entry);
            }
        }
        
        int totalFiles = filesToProcess.size();
        if (totalFiles == 0) {
            std::cout << "\nNo files to organize." << std::endl;
            return;
        }
        
        std::cout << " Found " << totalFiles << " files to organize." << std::endl;
        std::cout << "Processing files:" << std::endl;
        
        int processedFiles = 0;
        int lastProgress = -1;
        
        // Process files efficiently
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
                
                // Show progress only at 10% intervals or every 100 files
                int percentage = (processedFiles * 100) / totalFiles;
                if (percentage != lastProgress && (percentage % 10 == 0 || processedFiles % 100 == 0 || processedFiles == totalFiles)) {
                    std::cout << "Progress: " << processedFiles << "/" << totalFiles << " (" << percentage << "%)" << std::endl;
                    lastProgress = percentage;
                }
                
            } catch (const fs::filesystem_error& e) {
                std::cout << "Error moving " << filename << ": " << e.what() << std::endl;
            }
        }
        
        // Save move log for undo functionality (single write operation)
        saveUndoLog(folderPath, moves, sessionId);
        
        std::cout << "File organization completed! Processed " << processedFiles << " files." << std::endl;
        std::cout << "To undo: --undo \"" << folderPath << "\" " << sessionId << std::endl;
    }
    
    void showUndoHistory(const std::string& folderPath) {
        std::string logFile = folderPath + "/.fileorganizer_log.txt";
        
        if (!fs::exists(logFile)) {
            std::cout << "No organization history found for this folder." << std::endl;
            return;
        }
        
        std::ifstream file(logFile);
        std::string line;
        std::map<std::string, int> sessions;
        
        std::cout << "Organization history for: " << folderPath << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        
        while (std::getline(file, line)) {
            if (line.find("SESSION:") == 0) {
                std::string sessionId = line.substr(8);
                sessions[sessionId]++;
            }
        }
        
        for (const auto& session : sessions) {
            std::cout << "Session: " << session.first << " (" << session.second << " files moved)" << std::endl;
        }
        
        if (sessions.empty()) {
            std::cout << "No sessions found." << std::endl;
        }
    }
    
    void undoOrganization(const std::string& folderPath, const std::string& sessionId = "") {
        std::string logFile = folderPath + "/.fileorganizer_log.txt";
        
        if (!fs::exists(logFile)) {
            std::cout << "No undo log found for this folder." << std::endl;
            return;
        }
        
        std::vector<FileMove> movesToUndo;
        std::ifstream file(logFile);
        std::string line;
        std::string currentSession;
        
        // Read the log file
        while (std::getline(file, line)) {
            if (line.find("SESSION:") == 0) {
                currentSession = line.substr(8);
            } else if (line.find("MOVE:") == 0 && (sessionId.empty() || currentSession == sessionId)) {
                // Parse move line: MOVE:originalPath|newPath
                std::string moveInfo = line.substr(5);
                size_t pos = moveInfo.find('|');
                if (pos != std::string::npos) {
                    FileMove move;
                    move.originalPath = moveInfo.substr(0, pos);
                    move.newPath = moveInfo.substr(pos + 1);
                    move.timestamp = currentSession;
                    movesToUndo.push_back(move);
                }
            }
        }
        file.close();
        
        if (movesToUndo.empty()) {
            if (sessionId.empty()) {
                std::cout << "No moves found to undo." << std::endl;
            } else {
                std::cout << "No moves found for session: " << sessionId << std::endl;
            }
            return;
        }
        
        // Sort moves in reverse order (undo most recent first)
        std::reverse(movesToUndo.begin(), movesToUndo.end());
        
        std::cout << "Undoing " << movesToUndo.size() << " file moves..." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        
        int undoCount = 0;
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
                std::cout << "❌ Error restoring " << fs::path(move.originalPath).filename().string() << ": " << e.what() << std::endl;
            }
        }
        
        // Clean up empty category folders
        removeEmptyCategories(folderPath);
        
        // Remove the undone moves from the log
        if (!sessionId.empty()) {
            removeSessionFromLog(folderPath, sessionId);
        }
        
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "Undo completed! Restored " << undoCount << " files." << std::endl;
    }

private:
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
    
    void createCategoryFolders(const std::string& basePath) {
        // Store created paths for faster lookup later
        static std::vector<std::string> categoryFolders = {"Images", "Videos", "Music", "Documents", "Others"};
        
        // Create all category folders at once, avoiding string concatenation in loops
        fs::path basePathObj(basePath);
        for (const auto& folder : categoryFolders) {
            fs::path folderPath = basePathObj / folder;
            try {
                if (!fs::exists(folderPath)) {
                    fs::create_directory(folderPath);
                }
            } catch (const fs::filesystem_error&) {
                // Folder might already exist, that's okay
            }
        }
    }
    
    bool isValidFile(const fs::path& filePath, const std::string& basePath) {
        (void)basePath; // Mark as intentionally unused
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
    
    std::string getUniqueFilePath(const std::string& originalPath) {
        if (!fs::exists(originalPath)) {
            return originalPath; // Fast path for most files
        }
        
        // Use filesystem library for path manipulation (more efficient)
        fs::path path(originalPath);
        fs::path directory = path.parent_path();
        std::string stem = path.stem().string();
        std::string extension = path.extension().string();
        
        // Start with a reasonable counter to avoid too many checks for large duplicates
        int counter = 1;
        fs::path newPath;
        
        // Try to find a unique name with minimal filesystem checks
        do {
            // Use path concatenation instead of string concatenation
            newPath = directory / (stem + "_" + std::to_string(counter++) + extension);
        } while (fs::exists(newPath) && counter < 10000); // Avoid infinite loops
        
        return newPath.string();
    }
    
    std::string getCurrentTimestamp() {
        auto now = std::time(nullptr);
        auto tm = *std::localtime(&now);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y%m%d_%H%M%S");
        return oss.str();
    }
    
    void saveUndoLog(const std::string& folderPath, const std::vector<FileMove>& moves, const std::string& sessionId) {
        if (moves.empty()) {
            return; // No moves to log
        }
        
        std::string logFile = folderPath + "/.fileorganizer_log.txt";
        
        // Pre-allocate a string buffer for better performance with many files
        std::stringstream buffer;
        buffer << "SESSION:" << sessionId << std::endl;
        
        for (const auto& move : moves) {
            buffer << "MOVE:" << move.originalPath << "|" << move.newPath << std::endl;
        }
        buffer << "END_SESSION:" << sessionId << std::endl;
        
        // Single file write operation
        std::ofstream file(logFile, std::ios::app);
        file << buffer.str();
        file.close();
    }
    
    void removeEmptyCategories(const std::string& basePath) {
        std::vector<std::string> folders = {"Images", "Videos", "Music", "Documents", "Others"};
        
        for (const std::string& folder : folders) {
            std::string folderPath = basePath + "/" + folder;
            try {
                if (fs::exists(folderPath) && fs::is_directory(folderPath) && fs::is_empty(folderPath)) {
                    fs::remove(folderPath);
                    std::cout << "Removed empty folder: " << folder << std::endl;
                }
            } catch (const fs::filesystem_error& e) {
                // Ignore errors when removing directories
            }
        }
    }
    
    void removeSessionFromLog(const std::string& folderPath, const std::string& sessionId) {
        std::string logFile = folderPath + "/.fileorganizer_log.txt";
        std::string tempFile = logFile + ".tmp";
        
        std::ifstream input(logFile);
        std::ofstream output(tempFile);
        std::string line;
        bool skipSession = false;
        
        while (std::getline(input, line)) {
            if (line == "SESSION:" + sessionId) {
                skipSession = true;
                continue;
            } else if (line == "END_SESSION:" + sessionId) {
                skipSession = false;
                continue;
            }
            
            if (!skipSession) {
                output << line << std::endl;
            }
        }
        
        input.close();
        output.close();
        
        fs::remove(logFile);
        fs::rename(tempFile, logFile);
    }
    
    std::string formatFileSize(std::uintmax_t size) {
        const std::uintmax_t KB = 1024;
        const std::uintmax_t MB = KB * 1024;
        const std::uintmax_t GB = MB * 1024;
        
        if (size >= GB) {
            return std::to_string(size / GB) + " GB";
        } else if (size >= MB) {
            return std::to_string(size / MB) + " MB";
        } else if (size >= KB) {
            return std::to_string(size / KB) + " KB";
        } else {
            return std::to_string(size) + " bytes";
        }
    }
};

void showHelp() {
    std::cout << "FileOrganizer v1.0 - Professional File Organization Tool" << std::endl;
    std::cout << "========================================================" << std::endl;
    std::cout << std::endl;
    std::cout << "DESCRIPTION:" << std::endl;
    std::cout << "  Automatically organizes files into categorized subdirectories based on file extensions." << std::endl;
    std::cout << "  Features complete undo functionality with session tracking for safe file operations." << std::endl;
    std::cout << std::endl;
    std::cout << "USAGE:" << std::endl;
    std::cout << "  FileOrganizer [OPTION] <folder_path> [session_id]" << std::endl;
    std::cout << std::endl;
    std::cout << "OPTIONS:" << std::endl;
    std::cout << "  --organize <folder>         Organize files in the specified folder" << std::endl;
    std::cout << "                              Creates subdirectories: Documents/, Images/, Videos/, Audio/, Others/" << std::endl;
    std::cout << std::endl;
    std::cout << "  --list <folder>             Preview organization without moving files" << std::endl;
    std::cout << "                              Shows which files will go into which categories" << std::endl;
    std::cout << std::endl;
    std::cout << "  --undo <folder> [session]   Restore files to their original locations" << std::endl;
    std::cout << "                              If session ID provided, undo specific session only" << std::endl;
    std::cout << "                              If no session ID, undo the most recent organization" << std::endl;
    std::cout << std::endl;
    std::cout << "  --history <folder>          Show all organization sessions for the folder" << std::endl;
    std::cout << "                              Displays session IDs, timestamps, and file counts" << std::endl;
    std::cout << std::endl;
    std::cout << "  --interactive               Launch guided interactive mode" << std::endl;
    std::cout << "                              Recommended for first-time users" << std::endl;
    std::cout << std::endl;
    std::cout << "  --help                      Show this comprehensive help message" << std::endl;
    std::cout << std::endl;
    std::cout << "SUPPORTED FILE TYPES:" << std::endl;
    std::cout << "  Documents: .pdf .doc .docx .txt .rtf .odt .xls .xlsx .ppt .pptx .csv .md" << std::endl;
    std::cout << "  Images:    .jpg .jpeg .png .gif .bmp .tiff .svg .webp .ico" << std::endl;
    std::cout << "  Videos:    .mp4 .avi .mkv .mov .wmv .flv .webm .m4v .3gp" << std::endl;
    std::cout << "  Audio:     .mp3 .wav .flac .aac .ogg .wma .m4a .opus" << std::endl;
    std::cout << "  Others:    All other file types (preserves original extensions)" << std::endl;
    std::cout << std::endl;
    std::cout << "EXAMPLES:" << std::endl;
    std::cout << "  # Preview what will be organized (safe, no files moved)" << std::endl;
    std::cout << "  FileOrganizer --list \"C:\\Users\\hp\\Downloads\"" << std::endl;
    std::cout << std::endl;
    std::cout << "  # Organize files (creates folders and moves files)" << std::endl;
    std::cout << "  FileOrganizer --organize \"C:\\Users\\hp\\Downloads\"" << std::endl;
    std::cout << std::endl;
    std::cout << "  # Interactive mode for guided operation" << std::endl;
    std::cout << "  FileOrganizer --interactive" << std::endl;
    std::cout << std::endl;
    std::cout << "  # Undo the most recent organization" << std::endl;
    std::cout << "  FileOrganizer --undo \"C:\\Users\\hp\\Downloads\"" << std::endl;
    std::cout << std::endl;
    std::cout << "  # Undo a specific session (use --history to find session IDs)" << std::endl;
    std::cout << "  FileOrganizer --undo \"C:\\Users\\hp\\Downloads\" 20250717_143022" << std::endl;
    std::cout << std::endl;
    std::cout << "  # View organization history" << std::endl;
    std::cout << "  FileOrganizer --history \"C:\\Users\\hp\\Downloads\"" << std::endl;
    std::cout << std::endl;
    std::cout << "SAFETY FEATURES:" << std::endl;
    std::cout << "  * All file operations are logged with timestamps" << std::endl;
    std::cout << "  * Complete undo functionality - no permanent data loss" << std::endl;
    std::cout << "  * Preview mode to see changes before applying them" << std::endl;
    std::cout << "  * Session tracking allows selective undo operations" << std::endl;
    std::cout << "  * Existing organized folders are preserved and updated" << std::endl;
    std::cout << std::endl;
    std::cout << "WORKFLOW:" << std::endl;
    std::cout << "  1. Use --list to preview organization" << std::endl;
    std::cout << "  2. Use --organize to apply changes" << std::endl;
    std::cout << "  3. Use --history to view past operations" << std::endl;
    std::cout << "  4. Use --undo if you need to revert changes" << std::endl;
    std::cout << std::endl;
    std::cout << "For more information, visit: https://github.com/oladosuabayomi/FileOrganizer" << std::endl;
}

void interactiveMode() {
    SimpleFileOrganizer organizer;
    std::string choice, folderPath, sessionId;
    
    std::cout << "=== FileOrganizer CLI - Interactive Mode ===" << std::endl;
    std::cout << std::endl;
    
    while (true) {
        std::cout << "Commands:" << std::endl;
        std::cout << "  1. Organize folder" << std::endl;
        std::cout << "  2. List files in folder" << std::endl;
        std::cout << "  3. Undo last organization" << std::endl;
        std::cout << "  4. Show organization history" << std::endl;
        std::cout << "  5. Exit" << std::endl;
        std::cout << std::endl;
        std::cout << "Enter your choice (1-5): ";
        std::getline(std::cin, choice);
        
        if (choice == "1") {
            std::cout << "Enter folder path to organize: ";
            std::getline(std::cin, folderPath);
            
            if (!folderPath.empty()) {
                std::cout << std::endl;
                organizer.organizeFolder(folderPath);
                std::cout << std::endl;
            }
        }
        else if (choice == "2") {
            std::cout << "Enter folder path to list: ";
            std::getline(std::cin, folderPath);
            
            if (!folderPath.empty()) {
                std::cout << std::endl;
                organizer.listFiles(folderPath);
                std::cout << std::endl;
            }
        }
        else if (choice == "3") {
            std::cout << "Enter folder path to undo: ";
            std::getline(std::cin, folderPath);
            
            if (!folderPath.empty()) {
                std::cout << "Enter session ID (or press Enter for latest): ";
                std::getline(std::cin, sessionId);
                std::cout << std::endl;
                organizer.undoOrganization(folderPath, sessionId);
                std::cout << std::endl;
            }
        }
        else if (choice == "4") {
            std::cout << "Enter folder path to check history: ";
            std::getline(std::cin, folderPath);
            
            if (!folderPath.empty()) {
                std::cout << std::endl;
                organizer.showUndoHistory(folderPath);
                std::cout << std::endl;
            }
        }
        else if (choice == "5" || choice == "exit" || choice == "quit") {
            std::cout << "Goodbye!" << std::endl;
            break;
        }
        else {
            std::cout << "Invalid choice. Please try again." << std::endl << std::endl;
        }
    }
}

int main(int argc, char* argv[]) {
    SimpleFileOrganizer organizer;
    
    if (argc == 1) {
        showHelp();
        return 0;
    }
    
    std::string command = argv[1];
    
    if (command == "--help") {
        showHelp();
    }
    else if (command == "--interactive") {
        interactiveMode();
    }
    else if (command == "--organize" && argc >= 3) {
        std::string folderPath = argv[2];
        organizer.organizeFolder(folderPath);
    }
    else if (command == "--list" && argc >= 3) {
        std::string folderPath = argv[2];
        organizer.listFiles(folderPath);
    }
    else if (command == "--undo" && argc >= 3) {
        std::string folderPath = argv[2];
        std::string sessionId = (argc >= 4) ? argv[3] : "";
        organizer.undoOrganization(folderPath, sessionId);
    }
    else if (command == "--history" && argc >= 3) {
        std::string folderPath = argv[2];
        organizer.showUndoHistory(folderPath);
    }
    else {
        std::cout << "Invalid arguments. Use --help for usage information." << std::endl;
        return 1;
    }
    
    return 0;
}
