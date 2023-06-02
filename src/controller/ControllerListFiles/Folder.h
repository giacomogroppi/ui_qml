#pragma once

#include <QtGlobal>
#include <QByteArray>
#include "file/File.h"
#include <QList>

class Folder
{
private:
    QList<WFile> _files;

    QByteArray _path;
    QByteArray _nameFolder;
public:
    Folder(const QByteArray &path, const QByteArray &folderName);
    ~Folder() = default;

    const QByteArray &getFolderPath() const;
    const QByteArray &getFolderName() const;

    const QList<WFile> &getFiles() const;
    QList<WFile> &getFiles();

    void addFile(const WFile &file);
    void removeFile(const WFile &file);

    bool contains(const WFile &file) const;

    //Q_DISABLE_COPY(Folder);
};
