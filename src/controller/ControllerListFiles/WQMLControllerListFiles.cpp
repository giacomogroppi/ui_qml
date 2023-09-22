#include "ControllerListFiles.h"
#include "controller/Controller.h"

WQMLControllerListFiles::WQMLControllerListFiles(QObject *parent,
                                                 Fn<const WListFast<WFile>&()> getCurrentFiles,
                                                 Fn<int(QString name)> removeFileFromDirectory )
    : QAbstractListModel(parent)
    , _getCurrentFiles(std::move(getCurrentFiles))
    , _removeFileFromDirectory(std::move(removeFileFromDirectory))
{
}

auto WQMLControllerListFiles::rowCount(const QModelIndex &parent) const -> int
{
    qDebug() << "ControllerListFiles::rowCount() call";
    if (parent.isValid())
        return 0;

    return this->_getCurrentFiles().size();
}

auto WQMLControllerListFiles::roleNames() const -> QHash<int, QByteArray>
{
    static QHash<int, QByteArray> mapping {
        {Roles::Path, "name_file"},
        {Roles::LastModification, "last_mod"}
    };

    return mapping;
}

void WQMLControllerListFiles::duplicateData(int row)
{
    const auto &files = this->_getCurrentFiles();

    if (row < 0 or row >= files.size()) {
        qWarning() << "ControllerListFilesFolder::duplicateData index out of bound";
        return;
    }

    W_ASSERT(0);

    /*
    const WFile &data = files[row];
    const int rowOfInsert = row + 1;

    beginInsertRows(QModelIndex(), rowOfInsert, rowOfInsert);
    files.insert(rowOfInsert, data);
    endInsertRows();
     */
}

void WQMLControllerListFiles::removeData(int row)
{
    const auto &files = this->_getCurrentFiles();

    if (row < 0 or row >= files.size()) {
        qWarning() << "ControllerListFilesFolder::duplicateData index out of bound";
        return;
    }

    beginRemoveRows(QModelIndex(), row, row);
    this->_removeFileFromDirectory(files.at(row).getName());
    endRemoveRows();
}

void WQMLControllerListFiles::updateList()
{
    beginResetModel();
    endResetModel();
    //beginRemoveRows(QModelIndex(), row, row);
    //endRemoveRows();
}

auto WQMLControllerListFiles::data(const QModelIndex& index, int role) const -> QVariant
{
    const auto &files = this->_getCurrentFiles();

    if (not index.isValid()) {
        qWarning() << "Index is not valid";
        return {};
    }

    qDebug() << "ControllerListFiles::data" << role << index.row();

    if (index.row() < 0 || index.row() >= files.size())
        return {};

    const auto &data = files.at(index.row());

    switch (role) {
        case Roles::Path: return {
                QString(data.getName().constData())
        };
        case Roles::LastModification: return {
            data.getLastMod().toString().toUtf8().constData()
        };
        default: break;
    }

    qWarning() << "ControllerListFiles::data unkown role" << role;
    return {};
}

void WQMLControllerListFiles::clickFile(int index)
{
    Q_ASSERT(index >= 0 and index < this->_getCurrentFiles().size());
    Controller::instance()->showMain();
}
