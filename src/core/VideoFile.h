#ifndef VIDEOFILE_H
#define VIDEOFILE_H

#include "File.h"
#include <QStringList>

class VideoFile : public File {
public:
    VideoFile(const QString& path);
    
    QString getTargetDirectory() const override;
    QString getFileType() const override;
    bool canHandle() const override;
    
private:
    static QStringList getSupportedExtensions();
};

#endif // VIDEOFILE_H