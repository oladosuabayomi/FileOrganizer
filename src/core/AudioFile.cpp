#include "AudioFile.h"

AudioFile::AudioFile(const QString& path)
    : File(path) {}

QString AudioFile::getTargetDirectory() const {
    return "Music";
}

QString AudioFile::getFileType() const {
    return "Audio";
}

bool AudioFile::canHandle() const {
    return getSupportedExtensions().contains(getExtension());
}

QStringList AudioFile::getSupportedExtensions() {
    return QStringList() << "mp3" << "wav" << "flac" << "aac" << "ogg" 
                         << "wma" << "m4a" << "opus" << "aiff" << "au";
}