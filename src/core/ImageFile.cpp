#include "ImageFile.h"

ImageFile::ImageFile(const QString& path)
    : File(path) {}

QString ImageFile::getTargetDirectory() const {
    return "Images";
}

QString ImageFile::getFileType() const {
    return "Image";
}

bool ImageFile::canHandle() const {
    return getSupportedExtensions().contains(getExtension());
}

QStringList ImageFile::getSupportedExtensions() {
    return QStringList() << "jpg" << "jpeg" << "png" << "gif" << "bmp" 
                         << "tiff" << "tif" << "svg" << "webp" << "ico";
}