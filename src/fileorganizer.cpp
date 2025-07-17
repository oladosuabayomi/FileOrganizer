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
        
        int totalFiles = 0;
        int processedFiles = 0;
        std::vector<FileMove> moves;
        
        // Count total files first
        for (const auto& entry : fs::directory_iterator(folderPath)) {
            if (entry.is_regular_file() && isValidFile(entry.path(), folderPath)) {
                totalFiles++;
            }
        }
        
        std::cout << "Found " << totalFiles << " files to organize." << std::endl;
        std::cout << "----------------------------------------" << std::endl;
        
        // Process files
        for (const auto& entry : fs::directory_iterator(folderPath)) {
            if (entry.is_regular_file() && isValidFile(entry.path(), folderPath)) {
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
                    std::cout << "✓ Moved: " << filename << " -> " << category << "/" << std::endl;
                    
                    // Show progress
                    int percentage = (processedFiles * 100) / totalFiles;
                    std::cout << "Progress: " << processedFiles << "/" << totalFiles << " (" << percentage << "%)" << std::endl;
                } catch (const fs::filesystem_error& e) {
                    std::cout << "❌ Error moving " << filename << ": " << e.what() << std::endl;
                }
            }
        }
        
        // Save move log for undo functionality
        saveUndoLog(folderPath, moves, sessionId);
        
        std::cout << "----------------------------------------" << std::endl;
        std::cout << "File organization completed! Processed " << processedFiles << " files." << std::endl;
        std::cout << "To undo this operation, use: --undo \"" << folderPath << "\" " << sessionId << std::endl;
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
        auto it = extensionCategories.find(extension);
        return (it != extensionCategories.end()) ? it->second : "Others";
    }
    
    void createCategoryFolders(const std::string& basePath) {
        std::vector<std::string> folders = {"Images", "Videos", "Music", "Documents", "Others"};
        
        for (const std::string& folder : folders) {
            std::string folderPath = basePath + "/" + folder;
            try {
                fs::create_directory(folderPath);
            } catch (const fs::filesystem_error& e) {
                // Folder might already exist, that's okay
            }
        }
    }
    
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
    
    std::string getUniqueFilePath(const std::string& originalPath) {
        if (!fs::exists(originalPath)) {
            return originalPath;
        }
        
        fs::path path(originalPath);
        std::string stem = path.stem().string();
        std::string extension = path.extension().string();
        std::string directory = path.parent_path().string();
        
        int counter = 1;
        std::string newPath;
        
        do {
            newPath = directory + "/" + stem + "_" + std::to_string(counter) + extension;
            counter++;
        } while (fs::exists(newPath));
        
        return newPath;
    }
    
    std::string getCurrentTimestamp() {
        auto now = std::time(nullptr);
        auto tm = *std::localtime(&now);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y%m%d_%H%M%S");
        return oss.str();
    }
    
    void saveUndoLog(const std::string& folderPath, const std::vector<FileMove>& moves, const std::string& sessionId) {
        std::string logFile = folderPath + "/.fileorganizer_log.txt";
        std::ofstream file(logFile, std::ios::app);
        
        file << "SESSION:" << sessionId << std::endl;
        for (const auto& move : moves) {
            file << "MOVE:" << move.originalPath << "|" << move.newPath << std::endl;
        }
        file << "END_SESSION:" << sessionId << std::endl;
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
    std::cout << "FileOrganizer CLI - Simple File Organizer with Undo" << std::endl;
    std::cout << "====================================================" << std::endl;
    std::cout << "Usage:" << std::endl;
    std::cout << "  FileOrganizerSimple.exe [option] [folder_path] [session_id]" << std::endl;
    std::cout << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "  --organize <folder>         Organize files in the specified folder" << std::endl;
    std::cout << "  --list <folder>             List files and their categories" << std::endl;
    std::cout << "  --undo <folder> [session]   Undo organization (optionally specify session)" << std::endl;
    std::cout << "  --history <folder>          Show organization history" << std::endl;
    std::cout << "  --interactive               Run in interactive mode" << std::endl;
    std::cout << "  --help                      Show this help message" << std::endl;
    std::cout << std::endl;
    std::cout << "Examples:" << std::endl;
    std::cout << "  FileOrganizerSimple.exe --organize \"C:\\Users\\hp\\Downloads\"" << std::endl;
    std::cout << "  FileOrganizerSimple.exe --list \"C:\\Users\\hp\\Downloads\"" << std::endl;
    std::cout << "  FileOrganizerSimple.exe --undo \"C:\\Users\\hp\\Downloads\"" << std::endl;
    std::cout << "  FileOrganizerSimple.exe --undo \"C:\\Users\\hp\\Downloads\" 20250711_143022" << std::endl;
    std::cout << "  FileOrganizerSimple.exe --history \"C:\\Users\\hp\\Downloads\"" << std::endl;
    std::cout << "  FileOrganizerSimple.exe --interactive" << std::endl;
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
