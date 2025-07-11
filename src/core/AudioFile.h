#ifndef AUDIOFILE_H
#define AUDIOFILE_H

#include "File.h"
#include <QStringList>

class AudioFile : public File {
public:
    AudioFile(const QString& path);
    
    QString getTargetDirectory() const override;
    QString getFileType() const override;
    bool canHandle() const override;
    
private:
    static QStringList getSupportedExtensions();
};

#endif // AUDIOFILE_H