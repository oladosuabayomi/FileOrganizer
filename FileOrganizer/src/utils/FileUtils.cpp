#include "FileUtils.h"
#include <QDirIterator>
#include <QRegularExpression>

bool FileUtils::isImageFile(const QString& extension) {
    QStringList imageExtensions = {"jpg", "jpeg", "png", "gif", "bmp", "tiff", "tif", "svg", "webp", "ico"};
    return imageExtensions.contains(extension.toLower());
}

bool FileUtils::isAudioFile(const QString& extension) {
    QStringList audioExtensions = {"mp3", "wav", "flac", "aac", "ogg", "wma", "m4a", "opus", "aiff", "au"};
    return audioExtensions.contains(extension.toLower());
}

bool FileUtils::isVideoFile(const QString& extension) {
    QStringList videoExtensions = {"mp4", "avi", "mkv", "mov", "wmv", "flv", "webm", "m4v", "3gp", "mpg", "mpeg"};
    return videoExtensions.contains(extension.toLower());
}

bool FileUtils::isDocumentFile(const QString& extension) {
    QStringList docExtensions = {"pdf", "doc", "docx", "txt", "rtf", "odt", "xls", "xlsx", "ppt", "pptx", "csv", "md", "html", "xml"};
    return docExtensions.contains(extension.toLower());
}

QString FileUtils::getFileCategory(const QString& filePath) {
    QFileInfo fileInfo(filePath);
    QString extension = fileInfo.suffix().toLower();
    
    if (isImageFile(extension)) return "Images";
    if (isAudioFile(extension)) return "Music";
    if (isVideoFile(extension)) return "Videos";
    if (isDocumentFile(extension)) return "Documents";
    
    return "Others";
}

qint64 FileUtils::getDirectorySize(const QString& dirPath) {
    qint64 size = 0;
    QDirIterator iterator(dirPath, QDir::Files, QDirIterator::Subdirectories);
    
    while (iterator.hasNext()) {
        iterator.next();
        size += QFileInfo(iterator.filePath()).size();
    }
    
    return size;
}

QStringList FileUtils::getFilesInDirectory(const QString& dirPath, bool recursive) {
    QStringList files;
    QDirIterator::IteratorFlag flag = recursive ? QDirIterator::Subdirectories : QDirIterator::NoIteratorFlags;
    QDirIterator iterator(dirPath, QDir::Files, flag);
    
    while (iterator.hasNext()) {
        files.append(iterator.next());
    }
    
    return files;
}

bool FileUtils::createDirectoryIfNotExists(const QString& dirPath) {
    QDir dir;
    return dir.mkpath(dirPath);
}

QString FileUtils::formatFileSize(qint64 size) {
    const qint64 KB = 1024;
    const qint64 MB = KB * 1024;
    const qint64 GB = MB * 1024;
    
    if (size >= GB) {
        return QString::number(size / GB, 'f', 2) + " GB";
    } else if (size >= MB) {
        return QString::number(size / MB, 'f', 2) + " MB";
    } else if (size >= KB) {
        return QString::number(size / KB, 'f', 2) + " KB";
    } else {
        return QString::number(size) + " bytes";
    }
}

bool FileUtils::isValidFileName(const QString& fileName) {
    // Check for invalid characters in file names
    QRegularExpression invalidChars("[<>:\"/\\\\|?*]");
    return !fileName.contains(invalidChars) && !fileName.isEmpty();
}