#include "WQMLControllerListFolder.h"
#include "QtQml/qqml.h"
#include <qqml.h>
#include <QByteArray>
#include "controller/Controller.h"

static const WListFast<WFile> listEmpty;

WQMLControllerListFolder::WQMLControllerListFolder(QObject *parent, WQMLControllerListFiles *files)
    : QAbstractListModel(parent)
    , _is_visible(true)
    , _selected(0)
    , _controllerListFiles(files)
{

    /*
    this->_folder.append(Directory("/home/giacomo/writernote", "Elettronica"));
    this->_folder.append(Folder("/home/giacomo/writernote", "Economia"));
    this->_folder.append(Folder("/home/giacomo/writernote", "Robotica"));
    this->_folder.append(Folder("/home/giacomo/writernote", "Bioinformatica"));

    this->_folder[0].addFile(WFile(qstr("Elettronica lez 1")));
    this->_folder[1].addFile(WFile(qstr("Economica lez 2")));
    */

    this->_controllerListFiles->updateList();
}

auto WQMLControllerListFolder::rowCount(const QModelIndex &parent) const -> int
{
    if (parent.isValid())
        return 0;

    return this->_folder.size();
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

auto WQMLControllerListFolder::getDirSelected() const -> QString
{
    return this->_folder[_selected].getFolderName();
}

auto WQMLControllerListFolder::getFiles() const -> const WListFast<WFile> &
{
    if (_folder.isEmpty())
        return listEmpty;

    return _folder.at(_selected).getFiles();
}

auto WQMLControllerListFolder::removeFile(QString name) -> int
{
    int i;
    const auto &listFiles = this->_folder[_selected].getFiles();

    for (i = 0; i < listFiles.size(); i++) {
        if (_folder.at(i).getFolderName() == name)
            break;
    }

    W_ASSERT(listFiles.size() != i);

    _folder.remove(i);
    this->removeData(i);
    this->_controllerListFiles->updateList();
}

void WQMLControllerListFolder::addFolder(Directory &&directory)
{
    beginInsertRows(QModelIndex(), _folder.size(), _folder.size());
    _folder.append(std::move(directory));
    endInsertRows();
}

void WQMLControllerListFolder::duplicateData(int row)
{
    if (row < 0 or row >= this->_folder.size()) {
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
    if (row < 0 or row >= this->_folder.size()) {
        qWarning() << "ControllerListFilesFolder::duplicateData index out of bound";
        return;
    }

    beginRemoveRows(QModelIndex(), row, row);
    _folder.remove(row);
    endRemoveRows();
}

void WQMLControllerListFolder::click(int index)
{
    Q_ASSERT(index >= 0 and index < this->_folder.size());
    const auto last_index = _selected;
    this->_selected = index;
    this->_controllerListFiles->updateList();

    if (last_index != _selected) {
        emit this->onDirSelectedChanged();
    }
}

auto WQMLControllerListFolder::data(const QModelIndex& index, int role) const -> QVariant
{
    if (not index.isValid()) {
        qWarning() << "Index is not valid";
        return {};
    }

    qDebug() << "data" << role << index.row();

    if (index.row() < 0 || index.row() >= _folder.size())
        return {};

    const auto &data = _folder.at(index.row());

    switch (role) {
        case Roles::FolderName: return {
            data.getFolderName()
        };
        default: break;
    }

    qWarning() << "ControllerListFilesFolder::data unkown role" << role;
    return {};
}

