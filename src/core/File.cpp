#include "File.h"
#include <QFileInfo>

// Constructor to initialize the file object
File::File(const QString& path) 
    : filePath(path) {
    setFileInfo(path);
}

// Method to extract file information
void File::setFileInfo(const QString& path) {
    QFileInfo fileInfo(path);
    fileName = fileInfo.fileName();
    extension = fileInfo.suffix().toLower();
    fileSize = fileInfo.size();
}