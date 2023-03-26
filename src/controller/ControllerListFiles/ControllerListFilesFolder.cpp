#include "ControllerListFilesFolder.h"
#include "QtQml/qqml.h"
#include <qqml.h>
#include <QByteArray>
#include "Controller/Controller.h"

ControllerListFilesFolder::ControllerListFilesFolder(QObject *parent)
    : QAbstractListModel(parent)
    , _is_visible(true)
    , _selected(0)
    , _controllerListFiles(new ControllerListFiles(this, [this]() {
        return &_folder[_selected].getFiles();
    }))
{
    qmlRegisterType<ControllerListFilesFolder>(
        "writernote.WQMLControllerListFile", 1, 0, "WItemListFiles");

    Controller::registerType("_controllerListFiles",  this->_controllerListFiles);

    this->_folder.append(Folder("/home/giacomo/writernote", "Elettronica"));
    this->_folder.append(Folder("/home/giacomo/writernote", "Economia"));
    this->_folder.append(Folder("/home/giacomo/writernote", "Robotica"));
    this->_folder.append(Folder("/home/giacomo/writernote", "Bioinformatica"));


    this->_folder[0].addFile(File("Elettronica lez 1"));
    this->_folder[1].addFile(File("Economica lez 2"));

    this->_controllerListFiles->updateList();
}

int ControllerListFilesFolder::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return this->_folder.size();
}

QHash<int, QByteArray> ControllerListFilesFolder::roleNames() const
{
    static QHash<int, QByteArray> mapping {
        {Roles::FolderName, "folder_name"}
    };

    return mapping;
}

bool ControllerListFilesFolder::isVisible() const
{
    qDebug() << "ControllerListFilesFolder::isVisible call" << this->_is_visible;
    return this->_is_visible;
}

void ControllerListFilesFolder::setVisible(bool visible)
{
    const auto changed = visible != this->_is_visible;
    this->_is_visible = visible;
    if (changed) {
        emit this->isVisibleChanged();
    }
}

QString ControllerListFilesFolder::getDirSelected() const
{
    return this->_folder[_selected].getFolderName();
}

void ControllerListFilesFolder::duplicateData(int row)
{
    if (row < 0 or row >= this->_folder.size()) {
        qWarning() << "ControllerListFilesFolder::duplicateData index out of bound";
        return;
    }

    const Folder &data = _folder[row];
    const int rowOfInsert = row + 1;

    beginInsertRows(QModelIndex(), rowOfInsert, rowOfInsert);
    _folder.insert(rowOfInsert, data);
    endInsertRows();
}

void ControllerListFilesFolder::removeData(int row)
{
    if (row < 0 or row >= this->_folder.size()) {
        qWarning() << "ControllerListFilesFolder::duplicateData index out of bound";
        return;
    }

    beginRemoveRows(QModelIndex(), row, row);
    _folder.removeAt(row);
    endRemoveRows();
}

void ControllerListFilesFolder::click(int index)
{
    Q_ASSERT(index >= 0 and index < this->_folder.size());
    const auto last_index = _selected;
    this->_selected = index;
    this->_controllerListFiles->updateList();

    if (last_index != _selected) {
        emit this->onDirSelectedChanged();
    }
}

QVariant ControllerListFilesFolder::data(const QModelIndex& index, int role) const
{
    if (not index.isValid()) {
        qWarning() << "Index is not valid";
        return {};
    }

    qDebug() << "data" << role << index.row();

    if (index.row() < 0 || index.row() >= _folder.count())
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

