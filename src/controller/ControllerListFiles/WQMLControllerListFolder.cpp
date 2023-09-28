#include "WQMLControllerListFolder.h"
#include "QtQml/qqml.h"
#include <qqml.h>
#include <QByteArray>
#include "controller/Controller.h"

static const WListFast<WFile> listEmpty;

WQMLControllerListFolder::WQMLControllerListFolder(QObject *parent, const SharedPtr<FileManager>& fileManager)
    : QAbstractListModel(parent)
    , _fileManager(fileManager)
    , _is_visible(true)
{
    auto update = [this] { updateList(); };
    w_connect_lambda(_fileManager.get(), onDirectoryListChanged, update);
    w_connect_lambda(_fileManager.get(), onCurrentDirectoryChanged, update);
}

auto WQMLControllerListFolder::getPath(const WString &path) -> Path
{
    return (path.addSlashIfNecessary().toStdString());
}

auto WQMLControllerListFolder::rowCount(const QModelIndex &parent) const -> int
{
    if (parent.isValid())
        return 0;

    return this->_fileManager->getDirectory().size();
}

auto WQMLControllerListFolder::roleNames() const -> QHash<int, QByteArray>
{
    static QHash<int, QByteArray> mapping {
        {Roles::FolderName, "folder_name"}
    };

    return mapping;
}

auto WQMLControllerListFolder::isVisible() const -> bool
{
    qDebug() << "ControllerListFilesFolder::isVisible call" << this->_is_visible;
    return this->_is_visible;
}

void WQMLControllerListFolder::setVisible(bool visible)
{
    const auto changed = visible != this->_is_visible;
    this->_is_visible = visible;
    if (changed) {
        emit this->isVisibleChanged();
    }
}

auto WQMLControllerListFolder::updateList() -> void
{
    beginResetModel();
    endResetModel();
}

void WQMLControllerListFolder::duplicateData(int row)
{
    if (row < 0 or row >= this->_fileManager->getDirectory().size()) {
        qWarning() << "ControllerListFilesFolder::duplicateData index out of bound";
        return;
    }

    W_ASSERT("Not possibile");

    /*
    const auto &data = _folder[row];
    const int rowOfInsert = row + 1;

    beginInsertRows(QModelIndex(), rowOfInsert, rowOfInsert);
    _folder.insert(rowOfInsert, data);
    endInsertRows();
    */
}

void WQMLControllerListFolder::removeData(int row)
{
    if (row < 0 or row >= this->_fileManager->getDirectory().size()) {
        qWarning() << "ControllerListFilesFolder::duplicateData index out of bound";
        return;
    }

    beginRemoveRows(QModelIndex(), row, row);
    _fileManager->removeDirectory(row);
    emit onDirSelectedChanged();
    endRemoveRows();
}

void WQMLControllerListFolder::click(int index)
{
    Q_ASSERT(index >= 0 and index < this->_fileManager->getDirectory().size());

    if (_fileManager->selectedDirectory(index)) {
        emit this->onDirSelectedChanged();
    }
}

auto WQMLControllerListFolder::data(const QModelIndex& index, int role) const -> QVariant
{
    if (not index.isValid()) {
        qWarning() << "Index is not valid";
        return {};
    }

    const auto &directory = _fileManager->getDirectory();

    qDebug() << "data" << role << index.row();

    if (index.row() < 0 || index.row() >= directory.size())
        return {};

    const auto &data = directory.at(index.row());

    switch (role) {
        case Roles::FolderName: return {
            data.getFolderName()
        };
        default: break;
    }

    qWarning() << "ControllerListFilesFolder::data unkown role" << role;
    return {};
}

auto WQMLControllerListFolder::getDirSelected() const -> QString
{
    return _fileManager->getCurrentDirectory().getFolderName();
}

