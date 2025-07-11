#ifndef FILEUTILS_H
#define FILEUTILS_H

#include <QString>
#include <QStringList>
#include <QFileInfo>
#include <QDir>

class FileUtils {
public:
    // Static utility methods
    static bool isImageFile(const QString& extension);
    static bool isAudioFile(const QString& extension);
    static bool isVideoFile(const QString& extension);
    static bool isDocumentFile(const QString& extension);
    
    static QString getFileCategory(const QString& filePath);
    static qint64 getDirectorySize(const QString& dirPath);
    static QStringList getFilesInDirectory(const QString& dirPath, bool recursive = false);
    
    static bool createDirectoryIfNotExists(const QString& dirPath);
    static QString formatFileSize(qint64 size);
    static bool isValidFileName(const QString& fileName);
    
private:
    FileUtils() = default; // Prevent instantiation
};

#endif // FILEUTILS_H
    // Scans the given directory and returns a vector of file paths
    static std::vector<std::filesystem::path> scanDirectory(const std::string& directoryPath);

    // Moves a file from source to destination
    static bool moveFile(const std::filesystem::path& source, const std::filesystem::path& destination);

    // Gets the file extension category
    static std::string getExtensionCategory(const std::string& extension);
};

#endif // FILEUTILS_H