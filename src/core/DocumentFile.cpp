#include "DocumentFile.h"

DocumentFile::DocumentFile(const QString& path)
    : File(path) {}

QString DocumentFile::getTargetDirectory() const {
    return "Documents";
}

QString DocumentFile::getFileType() const {
    return "Document";
}

bool DocumentFile::canHandle() const {
    return getSupportedExtensions().contains(getExtension());
}

QStringList DocumentFile::getSupportedExtensions() {
    return QStringList() << "pdf" << "doc" << "docx" << "txt" << "rtf" 
                         << "odt" << "xls" << "xlsx" << "ppt" << "pptx" 
                         << "csv" << "md" << "html" << "xml";
}