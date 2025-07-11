#ifndef IMAGEFILE_H
#define IMAGEFILE_H

#include "File.h"
#include <QStringList>

class ImageFile : public File {
public:
    ImageFile(const QString& path);
    
    QString getTargetDirectory() const override;
    QString getFileType() const override;
    bool canHandle() const override;
    
private:
    static QStringList getSupportedExtensions();
};

#endif // IMAGEFILE_H
};

#endif // IMAGEFILE_H