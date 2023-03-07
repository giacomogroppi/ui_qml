#include "ControllerListFiles.h"

ControllerListFiles::ControllerListFiles(QObject *parent)
{
    Q_ASSERT(0);
}

ControllerListFiles::ControllerListFiles(QObject *parent,
                                         std::function<QList<File> *()> getFiles)
    :   QAbstractListModel(parent)
    ,   _getFile(getFiles)
{
}

int ControllerListFiles::rowCount(const QModelIndex &parent) const
{
    qDebug() << "ControllerListFiles::rowCount() call";
    if (parent.isValid())
        return 0;

    return this->_getFile()->size();
}

QHash<int, QByteArray> ControllerListFiles::roleNames() const
{
    static QHash<int, QByteArray> mapping {
        {Roles::Path, "name_file"},
        {Roles::LastModification, "last_mod"}
    };

    return mapping;
}

void ControllerListFiles::duplicateData(int row)
{
    QList<File> &files = *this->_getFile();
    if (row < 0 or row >= files.size()) {
        qWarning() << "ControllerListFilesFolder::duplicateData index out of bound";
        return;
    }

    const File &data = files[row];
    const int rowOfInsert = row + 1;

    beginInsertRows(QModelIndex(), rowOfInsert, rowOfInsert);
    files.insert(rowOfInsert, data);
    endInsertRows();
}

void ControllerListFiles::removeData(int row)
{
    QList<File> &files = *this->_getFile();
    if (row < 0 or row >= files.size()) {
        qWarning() << "ControllerListFilesFolder::duplicateData index out of bound";
        return;
    }

    beginRemoveRows(QModelIndex(), row, row);
    files.removeAt(row);
    endRemoveRows();
}

void ControllerListFiles::updateList()
{
    beginResetModel();
    endResetModel();
    //beginRemoveRows(QModelIndex(), row, row);
    //endRemoveRows();
}

QVariant ControllerListFiles::data(const QModelIndex& index, int role) const
{
    QList<File> &files = *this->_getFile();
    if (not index.isValid()) {
        qWarning() << "Index is not valid";
        return {};
    }

    qDebug() << "ControllerListFiles::data" << role << index.row();

    if (index.row() < 0 || index.row() >= files.count())
        return {};

    const auto &data = files.at(index.row());

    switch (role) {
        case Roles::Path: return {
            data.getName()
        };
        case Roles::LastModification: return {
            data.getLastMod()
        };
        default: break;
    }

    qWarning() << "ControllerListFiles::data unkown role" << role;
    return {};
}
