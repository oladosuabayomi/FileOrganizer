#include "FileHandler.h"
#include "File.h"
#include "ImageFile.h"
#include "AudioFile.h"
#include "VideoFile.h"
#include "DocumentFile.h"
#include <QFileInfo>
#include <QDirIterator>
#include <QStandardPaths>
#include <QRegularExpression>

FileHandler::FileHandler(QObject *parent)
    : QObject(parent), totalFiles(0), processedCount(0)
{
}

bool FileHandler::organizeFolder(const QString& folderPath) {
    if (!QDir(folderPath).exists()) {
        emit errorOccurred("Folder does not exist: " + folderPath);
        return false;
    }
    
    processedFiles.clear();
    errors.clear();
    totalFiles = 0;
    processedCount = 0;
    
    // Create category folders
    if (!createCategoryFolders(folderPath)) {
        emit errorOccurred("Failed to create category folders");
        return false;
    }
    
    // Scan and organize files
    scanFolder(folderPath);
    
    emit operationCompleted(true, QString("Successfully processed %1 files").arg(processedCount));
    return true;
}

void FileHandler::scanFolder(const QString& folderPath) {
    // First pass: count total files
    QDirIterator countIterator(folderPath, QDir::Files, QDirIterator::NoIteratorFlags);
    while (countIterator.hasNext()) {
        countIterator.next();
        if (isValidFile(countIterator.filePath())) {
            totalFiles++;
        }
    }
    
    // Second pass: process files
    QDirIterator iterator(folderPath, QDir::Files, QDirIterator::NoIteratorFlags);
    while (iterator.hasNext()) {
        QString filePath = iterator.next();
        
        if (!isValidFile(filePath)) {
            continue;
        }
        
        auto fileHandler = createFileHandler(filePath);
        if (fileHandler && fileHandler->canHandle()) {
            QString targetDir = folderPath + "/" + fileHandler->getTargetDirectory();
            
            if (moveFileToCategory(filePath, targetDir)) {
                processedFiles.append(filePath);
                emit fileProcessed(fileHandler->getFileName(), fileHandler->getFileType());
            } else {
                errors.append("Failed to move: " + filePath);
                emit errorOccurred("Failed to move: " + filePath);
            }
        } else {
            // Move to "Others" folder for unknown file types
            QString targetDir = folderPath + "/Others";
            QDir().mkpath(targetDir);
            
            if (moveFileToCategory(filePath, targetDir)) {
                processedFiles.append(filePath);
                emit fileProcessed(QFileInfo(filePath).fileName(), "Other");
            }
        }
        
        processedCount++;
        emit progressUpdated(processedCount, totalFiles);
    }
}

bool FileHandler::moveFileToCategory(const QString& filePath, const QString& targetDir) {
    QFileInfo fileInfo(filePath);
    QString fileName = sanitizeFileName(fileInfo.fileName());
    QString targetPath = targetDir + "/" + fileName;
    
    // Handle file name conflicts
    int counter = 1;
    QString baseName = fileInfo.baseName();
    QString suffix = fileInfo.suffix();
    
    while (QFile::exists(targetPath)) {
        QString newName = QString("%1_%2.%3").arg(baseName).arg(counter).arg(suffix);
        targetPath = targetDir + "/" + newName;
        counter++;
    }
    
    return QFile::rename(filePath, targetPath);
}

bool FileHandler::createCategoryFolders(const QString& basePath) {
    QStringList folders = {"Images", "Videos", "Music", "Documents", "Others"};
    
    for (const QString& folder : folders) {
        QString folderPath = basePath + "/" + folder;
        if (!QDir().mkpath(folderPath)) {
            return false;
        }
    }
    return true;
}

std::unique_ptr<File> FileHandler::createFileHandler(const QString& filePath) {
    // Try each file type
    auto imageFile = std::make_unique<ImageFile>(filePath);
    if (imageFile->canHandle()) return std::move(imageFile);
    
    auto audioFile = std::make_unique<AudioFile>(filePath);
    if (audioFile->canHandle()) return std::move(audioFile);
    
    auto videoFile = std::make_unique<VideoFile>(filePath);
    if (videoFile->canHandle()) return std::move(videoFile);
    
    auto documentFile = std::make_unique<DocumentFile>(filePath);
    if (documentFile->canHandle()) return std::move(documentFile);
    
    return nullptr; // Unknown file type
}

QString FileHandler::getFileCategoryFolder(const QString& extension) {
    ImageFile tempImage("");
    if (tempImage.canHandle()) return "Images";
    
    AudioFile tempAudio("");
    if (tempAudio.canHandle()) return "Music";
    
    VideoFile tempVideo("");
    if (tempVideo.canHandle()) return "Videos";
    
    DocumentFile tempDoc("");
    if (tempDoc.canHandle()) return "Documents";
    
    return "Others";
}

bool FileHandler::isValidFile(const QString& filePath) {
    QFileInfo fileInfo(filePath);
    
    // Skip directories, hidden files, and system files
    if (fileInfo.isDir() || fileInfo.fileName().startsWith('.')) {
        return false;
    }
    
    // Skip files that are already in category folders
    QString parentDir = fileInfo.dir().dirName();
    if (parentDir == "Images" || parentDir == "Videos" || 
        parentDir == "Music" || parentDir == "Documents" || 
        parentDir == "Others") {
        return false;
    }
    
    return true;
}

QString FileHandler::sanitizeFileName(const QString& fileName) {
    QString sanitized = fileName;
    // Remove or replace invalid characters
    sanitized.replace(QRegularExpression("[<>:\"/\\|?*]"), "_");
    return sanitized;
}
        return "Documents";
    } else if (extension == ".mp3" || extension == ".wav") {
        return "Music";
    } else if (extension == ".mp4" || extension == ".avi") {
        return "Videos";
    } else if (extension == ".jpg" || extension == ".png" || extension == ".gif") {
        return "Images";
    } else {
        return "Others";
    }
}