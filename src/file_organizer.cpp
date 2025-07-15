#include "file_organizer.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <ctime>

FileOrganizer::FileOrganizer() {
    initialize_categories();
    current_session_id_ = generate_session_id();
}

bool FileOrganizer::list_files(const std::string& directory_path) {
    if (!fs::exists(directory_path) || !fs::is_directory(directory_path)) {
        std::cerr << "Error: Directory does not exist: " << directory_path << std::endl;
        return false;
    }

    std::cout << "Files in " << directory_path << ":" << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    operation_stats_.clear();
    
    try {
        for (const auto& entry : fs::directory_iterator(directory_path)) {
            if (entry.is_regular_file() && is_valid_file(entry.path(), directory_path)) {
                std::string filename = entry.path().filename().string();
                std::string extension = entry.path().extension().string();
                std::transform(extension.begin(), extension.end(), extension.begin(), 
                    [](unsigned char c) { return std::tolower(c); });
                
                std::string category = get_file_category(extension);
                auto file_size = fs::file_size(entry.path());
                
                std::cout << "  " << std::setw(30) << std::left << filename 
                         << " -> " << std::setw(12) << category 
                         << " (" << format_file_size(file_size) << ")" << std::endl;
                
                operation_stats_[category]++;
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error accessing directory: " << e.what() << std::endl;
        return false;
    }

    std::cout << std::string(60, '-') << std::endl;
    std::cout << "Summary:" << std::endl;
    for (const auto& [category, count] : operation_stats_) {
        std::cout << "  " << category << ": " << count << " files" << std::endl;
    }

    return true;
}

bool FileOrganizer::organize_directory(const std::string& directory_path) {
    if (!fs::exists(directory_path) || !fs::is_directory(directory_path)) {
        std::cerr << "Error: Directory does not exist: " << directory_path << std::endl;
        return false;
    }

    std::cout << "Starting file organization in: " << directory_path << std::endl;
    std::cout << "Session ID: " << current_session_id_ << std::endl;

    if (!create_category_directories(directory_path)) {
        std::cerr << "Error: Failed to create category directories" << std::endl;
        return false;
    }

    current_operations_.clear();
    operation_stats_.clear();
    
    int total_files = 0;
    int processed_files = 0;

    // Count total files
    try {
        for (const auto& entry : fs::directory_iterator(directory_path)) {
            if (entry.is_regular_file() && is_valid_file(entry.path(), directory_path)) {
                total_files++;
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error counting files: " << e.what() << std::endl;
        return false;
    }

    std::cout << "Found " << total_files << " files to organize." << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    // Process files
    try {
        for (const auto& entry : fs::directory_iterator(directory_path)) {
            if (entry.is_regular_file() && is_valid_file(entry.path(), directory_path)) {
                std::string filename = entry.path().filename().string();
                std::string extension = entry.path().extension().string();
                std::transform(extension.begin(), extension.end(), extension.begin(), 
                    [](unsigned char c) { return std::tolower(c); });
                
                std::string category = get_file_category(extension);
                std::string target_dir = directory_path + "/" + category;
                std::string target_path = target_dir + "/" + filename;
                
                target_path = get_unique_file_path(target_path);
                
                try {
                    // Record operation
                    FileOperation operation;
                    operation.source_path = entry.path().string();
                    operation.destination_path = target_path;
                    operation.timestamp = current_session_id_;
                    operation.session_id = current_session_id_;
                    current_operations_.push_back(operation);
                    
                    fs::rename(entry.path(), target_path);
                    processed_files++;
                    operation_stats_[category]++;
                    
                    std::cout << "Moved: " << filename << " -> " << category << "/" << std::endl;
                    
                    // Show progress
                    int percentage = (processed_files * 100) / total_files;
                    std::cout << "Progress: " << processed_files << "/" << total_files 
                             << " (" << percentage << "%)" << std::endl;
                             
                } catch (const fs::filesystem_error& e) {
                    std::cerr << "Error moving " << filename << ": " << e.what() << std::endl;
                }
            }
        }
    } catch (const fs::filesystem_error& e) {
        std::cerr << "Error processing directory: " << e.what() << std::endl;
        return false;
    }

    if (!save_operation_log(directory_path)) {
        std::cerr << "Warning: Failed to save operation log" << std::endl;
    }

    std::cout << std::string(60, '-') << std::endl;
    std::cout << "Organization completed. Processed " << processed_files << " files." << std::endl;
    std::cout << "To undo this operation, use: --undo \"" << directory_path 
             << "\" --session " << current_session_id_ << std::endl;

    return true;
}

bool FileOrganizer::undo_organization(const std::string& directory_path, 
                                     const std::string& session_id) {
    std::vector<FileOperation> operations = load_operation_history(directory_path);
    std::vector<FileOperation> operations_to_undo;

    // Filter operations by session if specified
    for (const auto& operation : operations) {
        if (session_id.empty() || operation.session_id == session_id) {
            operations_to_undo.push_back(operation);
        }
    }

    if (operations_to_undo.empty()) {
        std::cout << "No operations found to undo." << std::endl;
        return true;
    }

    // Reverse order for undo (most recent first)
    std::reverse(operations_to_undo.begin(), operations_to_undo.end());

    std::cout << "Undoing " << operations_to_undo.size() << " file operations..." << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    int undo_count = 0;
    for (const auto& operation : operations_to_undo) {
        try {
            if (fs::exists(operation.destination_path)) {
                fs::rename(operation.destination_path, operation.source_path);
                undo_count++;
                std::cout << "Restored: " 
                         << fs::path(operation.source_path).filename().string() << std::endl;
            } else {
                std::cout << "Warning: File not found: " 
                         << fs::path(operation.destination_path).filename().string() << std::endl;
            }
        } catch (const fs::filesystem_error& e) {
            std::cerr << "Error restoring " 
                     << fs::path(operation.source_path).filename().string() 
                     << ": " << e.what() << std::endl;
        }
    }

    cleanup_empty_directories(directory_path);

    std::cout << std::string(60, '-') << std::endl;
    std::cout << "Undo completed. Restored " << undo_count << " files." << std::endl;

    return true;
}

bool FileOrganizer::show_history(const std::string& directory_path) {
    std::vector<FileOperation> operations = load_operation_history(directory_path);
    
    if (operations.empty()) {
        std::cout << "No organization history found for this directory." << std::endl;
        return true;
    }

    std::map<std::string, int> session_counts;
    for (const auto& operation : operations) {
        session_counts[operation.session_id]++;
    }

    std::cout << "Organization history for: " << directory_path << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    for (const auto& [session, count] : session_counts) {
        std::cout << "Session: " << session << " (" << count << " files moved)" << std::endl;
    }

    return true;
}

std::string FileOrganizer::get_current_session_id() const {
    return current_session_id_;
}

std::map<std::string, int> FileOrganizer::get_operation_stats() const {
    return operation_stats_;
}

void FileOrganizer::initialize_categories() {
    // Document files
    std::vector<std::string> document_extensions = {
        ".pdf", ".doc", ".docx", ".txt", ".rtf", ".odt",
        ".xls", ".xlsx", ".ppt", ".pptx", ".csv", ".md"
    };
    for (const auto& ext : document_extensions) {
        file_categories_[ext] = "Documents";
    }

    // Image files
    std::vector<std::string> image_extensions = {
        ".jpg", ".jpeg", ".png", ".gif", ".bmp", ".tiff", 
        ".svg", ".webp", ".ico"
    };
    for (const auto& ext : image_extensions) {
        file_categories_[ext] = "Images";
    }

    // Video files
    std::vector<std::string> video_extensions = {
        ".mp4", ".avi", ".mkv", ".mov", ".wmv", ".flv",
        ".webm", ".m4v", ".3gp"
    };
    for (const auto& ext : video_extensions) {
        file_categories_[ext] = "Videos";
    }

    // Audio files
    std::vector<std::string> audio_extensions = {
        ".mp3", ".wav", ".flac", ".aac", ".ogg", ".wma",
        ".m4a", ".opus"
    };
    for (const auto& ext : audio_extensions) {
        file_categories_[ext] = "Audio";
    }
}

std::string FileOrganizer::get_file_category(const std::string& extension) {
    auto it = file_categories_.find(extension);
    return (it != file_categories_.end()) ? it->second : "Others";
}

bool FileOrganizer::create_category_directories(const std::string& base_path) {
    std::vector<std::string> categories = {"Documents", "Images", "Videos", "Audio", "Others"};
    
    for (const std::string& category : categories) {
        std::string category_path = base_path + "/" + category;
        try {
            fs::create_directory(category_path);
        } catch (const fs::filesystem_error&) {
            // Directory might already exist, which is fine
        }
    }
    return true;
}

bool FileOrganizer::is_valid_file(const fs::path& file_path, const std::string& base_path) {
    (void)base_path; // Parameter reserved for future use
    std::string filename = file_path.filename().string();
    std::string parent_dir = file_path.parent_path().filename().string();
    
    // Skip hidden files, log files, and files already in category folders
    if (filename[0] == '.' || 
        filename == ".file_organizer_log.txt" ||
        parent_dir == "Documents" || parent_dir == "Images" || 
        parent_dir == "Videos" || parent_dir == "Audio" || 
        parent_dir == "Others") {
        return false;
    }
    
    return true;
}

std::string FileOrganizer::get_unique_file_path(const std::string& target_path) {
    if (!fs::exists(target_path)) {
        return target_path;
    }
    
    fs::path path(target_path);
    std::string stem = path.stem().string();
    std::string extension = path.extension().string();
    std::string directory = path.parent_path().string();
    
    int counter = 1;
    std::string new_path;
    
    do {
        new_path = directory + "/" + stem + "_" + std::to_string(counter) + extension;
        counter++;
    } while (fs::exists(new_path));
    
    return new_path;
}

std::string FileOrganizer::generate_session_id() {
    auto now = std::time(nullptr);
    auto tm = *std::localtime(&now);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y%m%d_%H%M%S");
    return oss.str();
}

bool FileOrganizer::save_operation_log(const std::string& directory_path) {
    std::string log_file = get_log_file_path(directory_path);
    std::ofstream file(log_file, std::ios::app);
    
    if (!file.is_open()) {
        return false;
    }
    
    file << "SESSION:" << current_session_id_ << std::endl;
    for (const auto& operation : current_operations_) {
        file << "OPERATION:" << operation.source_path << "|" << operation.destination_path << std::endl;
    }
    file << "END_SESSION:" << current_session_id_ << std::endl;
    
    return true;
}

std::vector<FileOperation> FileOrganizer::load_operation_history(const std::string& directory_path) {
    std::vector<FileOperation> operations;
    std::string log_file = get_log_file_path(directory_path);
    
    if (!fs::exists(log_file)) {
        return operations;
    }
    
    std::ifstream file(log_file);
    std::string line;
    std::string current_session;
    
    while (std::getline(file, line)) {
        if (line.find("SESSION:") == 0) {
            current_session = line.substr(8);
        } else if (line.find("OPERATION:") == 0) {
            std::string operation_info = line.substr(10);
            size_t pos = operation_info.find('|');
            if (pos != std::string::npos) {
                FileOperation operation;
                operation.source_path = operation_info.substr(0, pos);
                operation.destination_path = operation_info.substr(pos + 1);
                operation.session_id = current_session;
                operation.timestamp = current_session;
                operations.push_back(operation);
            }
        }
    }
    
    return operations;
}

void FileOrganizer::cleanup_empty_directories(const std::string& base_path) {
    std::vector<std::string> categories = {"Documents", "Images", "Videos", "Audio", "Others"};
    
    for (const std::string& category : categories) {
        std::string category_path = base_path + "/" + category;
        try {
            if (fs::exists(category_path) && fs::is_directory(category_path) && fs::is_empty(category_path)) {
                fs::remove(category_path);
                std::cout << "Removed empty directory: " << category << std::endl;
            }
        } catch (const fs::filesystem_error&) {
            // Ignore errors when removing directories
        }
    }
}

std::string FileOrganizer::format_file_size(std::uintmax_t size) {
    const std::uintmax_t KB = 1024;
    const std::uintmax_t MB = KB * 1024;
    const std::uintmax_t GB = MB * 1024;
    
    std::ostringstream oss;
    if (size >= GB) {
        oss << std::fixed << std::setprecision(2) << (double)size / GB << " GB";
    } else if (size >= MB) {
        oss << std::fixed << std::setprecision(2) << (double)size / MB << " MB";
    } else if (size >= KB) {
        oss << std::fixed << std::setprecision(2) << (double)size / KB << " KB";
    } else {
        oss << size << " bytes";
    }
    
    return oss.str();
}

std::string FileOrganizer::get_log_file_path(const std::string& directory_path) {
    return directory_path + "/.file_organizer_log.txt";
}
