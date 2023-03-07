#include "Folder.h"

Folder::Folder(const QByteArray &path, const QByteArray &folderName)
    : _path(path)
    , _nameFolder(folderName)
{
}

const QByteArray &Folder::getFolderName() const
{
    return this->_nameFolder;
}

const QList<File> &Folder::getFiles() const
{
    return this->_files;
}

QList<File> &Folder::getFiles()
{
    return this->_files;
}

void Folder::addFile(const File &file)
{
    Q_ASSERT(!this->contains(file));
    this->_files.append(file);
}

void Folder::removeFile(const File &file)
{
    Q_ASSERT(this->contains(file));
    int i;

    for (i = 0; i < this->_files.size(); i++) {
        if (_files.at(i) == file) {
            this->_files.removeAt(i);
            break;
        }
    }
}

bool Folder::contains(const File &file) const
{
    for (const auto &f : this->_files) {
        if(file == f)
            return true;
    }

    return false;
}
