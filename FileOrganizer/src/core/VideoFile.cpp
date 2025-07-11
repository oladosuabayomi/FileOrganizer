#include "VideoFile.h"

VideoFile::VideoFile(const QString& path)
    : File(path) {}

QString VideoFile::getTargetDirectory() const {
    return "Videos";
}

QString VideoFile::getFileType() const {
    return "Video";
}

bool VideoFile::canHandle() const {
    return getSupportedExtensions().contains(getExtension());
}

QStringList VideoFile::getSupportedExtensions() {
    return QStringList() << "mp4" << "avi" << "mkv" << "mov" << "wmv" 
                         << "flv" << "webm" << "m4v" << "3gp" << "mpg" << "mpeg";
}