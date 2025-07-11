#ifndef DOCUMENTFILE_H
#define DOCUMENTFILE_H

#include "File.h"
#include <QStringList>

class DocumentFile : public File {
public:
    DocumentFile(const QString& path);
    
    QString getTargetDirectory() const override;
    QString getFileType() const override;
    bool canHandle() const override;
    
private:
    static QStringList getSupportedExtensions();
};

#endif // DOCUMENTFILE_H