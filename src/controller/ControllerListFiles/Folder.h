#pragma once

#include <QtGlobal>
#include <QByteArray>
#include "file/File.h"
#include <QList>

class Folder
{
private:
    QList<File> _files;

    QByteArray _path;
    QByteArray _nameFolder;
public:
    Folder(const QByteArray &path, const QByteArray &folderName);
    ~Folder() = default;

    const QByteArray &getFolderPath() const;
    const QByteArray &getFolderName() const;

    const QList<File> &getFiles() const;
    QList<File> &getFiles();

    void addFile(const File &file);
    void removeFile(const File &file);

    bool contains(const File &file) const;

    //Q_DISABLE_COPY(Folder);
};
