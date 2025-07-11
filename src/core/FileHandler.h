#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <QString>
#include <QDir>
#include <QStringList>
#include <QObject>
#include <memory>

class File;

class FileHandler : public QObject {
    Q_OBJECT
    
public:
    explicit FileHandler(QObject *parent = nullptr);
    
    // Main functionality
    bool organizeFolder(const QString& folderPath);
    void scanFolder(const QString& folderPath);
    
    // File operations
    bool moveFileToCategory(const QString& filePath, const QString& targetDir);
    bool createCategoryFolders(const QString& basePath);
    
    // File classification
    std::unique_ptr<File> createFileHandler(const QString& filePath);
    QString getFileCategoryFolder(const QString& extension);
    
    // Getters
    QStringList getProcessedFiles() const { return processedFiles; }
    QStringList getErrors() const { return errors; }
    int getTotalFiles() const { return totalFiles; }
    int getProcessedCount() const { return processedCount; }

signals:
    void fileProcessed(const QString& fileName, const QString& category);
    void progressUpdated(int current, int total);
    void operationCompleted(bool success, const QString& message);
    void errorOccurred(const QString& error);

private:
    QStringList processedFiles;
    QStringList errors;
    int totalFiles;
    int processedCount;
    
    // Helper methods
    bool isValidFile(const QString& filePath);
    QString sanitizeFileName(const QString& fileName);
};

#endif // FILEHANDLER_H