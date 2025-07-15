#ifndef FILE_ORGANIZER_H
#define FILE_ORGANIZER_H

#include <string>
#include <vector>
#include <map>
#include <filesystem>

namespace fs = std::filesystem;

/**
 * @brief Structure to represent a file operation for undo functionality
 */
struct FileOperation {
    std::string source_path;
    std::string destination_path;
    std::string timestamp;
    std::string session_id;
};

/**
 * @brief Main file organizer class
 * 
 * Provides functionality to organize files by type with undo capabilities
 */
class FileOrganizer {
public:
    /**
     * @brief Construct a new File Organizer object
     */
    FileOrganizer();

    /**
     * @brief Destroy the File Organizer object
     */
    ~FileOrganizer() = default;

    /**
     * @brief List files in directory without organizing them
     * @param directory_path Path to directory to analyze
     * @return true if successful, false otherwise
     */
    bool list_files(const std::string& directory_path);

    /**
     * @brief Organize files in the specified directory
     * @param directory_path Path to directory to organize
     * @return true if successful, false otherwise
     */
    bool organize_directory(const std::string& directory_path);

    /**
     * @brief Undo the last organization operation
     * @param directory_path Directory where organization was performed
     * @param session_id Optional specific session to undo
     * @return true if successful, false otherwise
     */
    bool undo_organization(const std::string& directory_path, 
                          const std::string& session_id = "");

    /**
     * @brief Display organization history for a directory
     * @param directory_path Directory to check history for
     * @return true if successful, false otherwise
     */
    bool show_history(const std::string& directory_path);

    /**
     * @brief Get the current session ID
     * @return Current session identifier
     */
    std::string get_current_session_id() const;

    /**
     * @brief Get statistics from last operation
     * @return Map containing operation statistics
     */
    std::map<std::string, int> get_operation_stats() const;

private:
    std::map<std::string, std::string> file_categories_;
    std::vector<FileOperation> current_operations_;
    std::string current_session_id_;
    std::map<std::string, int> operation_stats_;

    /**
     * @brief Initialize file extension to category mappings
     */
    void initialize_categories();

    /**
     * @brief Get category for file extension
     * @param extension File extension (including dot)
     * @return Category name
     */
    std::string get_file_category(const std::string& extension);

    /**
     * @brief Create category directories if they don't exist
     * @param base_path Base directory path
     * @return true if successful, false otherwise
     */
    bool create_category_directories(const std::string& base_path);

    /**
     * @brief Check if file should be processed
     * @param file_path Path to file
     * @param base_path Base directory path
     * @return true if file should be processed, false otherwise
     */
    bool is_valid_file(const fs::path& file_path, const std::string& base_path);

    /**
     * @brief Generate unique file path to avoid conflicts
     * @param target_path Desired target path
     * @return Unique file path
     */
    std::string get_unique_file_path(const std::string& target_path);

    /**
     * @brief Generate timestamp-based session ID
     * @return Session identifier string
     */
    std::string generate_session_id();

    /**
     * @brief Save operation log for undo functionality
     * @param directory_path Directory where operations were performed
     * @return true if successful, false otherwise
     */
    bool save_operation_log(const std::string& directory_path);

    /**
     * @brief Load operation history from log file
     * @param directory_path Directory to load history for
     * @return Vector of file operations
     */
    std::vector<FileOperation> load_operation_history(const std::string& directory_path);

    /**
     * @brief Remove empty category directories
     * @param base_path Base directory path
     */
    void cleanup_empty_directories(const std::string& base_path);

    /**
     * @brief Format file size for display
     * @param size File size in bytes
     * @return Formatted size string
     */
    std::string format_file_size(std::uintmax_t size);

    /**
     * @brief Get operation log file path
     * @param directory_path Base directory
     * @return Path to log file
     */
    std::string get_log_file_path(const std::string& directory_path);
};

#endif // FILE_ORGANIZER_H
