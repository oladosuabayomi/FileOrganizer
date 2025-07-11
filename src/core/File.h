#ifndef FILE_H
#define FILE_H

#include <QString>
#include <QFileInfo>

class File {
private:
    QString filePath;
    QString fileName;
    QString extension;
    qint64 fileSize;

public:
    File(const QString& path);
    virtual ~File() = default;
    
    // Getters
    QString getFilePath() const { return filePath; }
    QString getFileName() const { return fileName; }
    QString getExtension() const { return extension; }
    qint64 getFileSize() const { return fileSize; }
    
    // Pure virtual functions for polymorphism
    virtual QString getTargetDirectory() const = 0;
    virtual QString getFileType() const = 0;
    virtual bool canHandle() const = 0;

protected:
    void setFileInfo(const QString& path);
};

#endif // FILE_H