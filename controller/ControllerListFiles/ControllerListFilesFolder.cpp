#include "ControllerListFilesFolder.h"
#include "QtQml/qqml.h"
#include <qqml.h>
#include <QByteArray>

ControllerListFilesFolder::ControllerListFilesFolder(QObject *parent)
    : QAbstractListModel(parent)
    , _is_visible(true)
{
    qmlRegisterType<ControllerListFilesFolder>("writernote.WQMLControllerListFile",
                                               1, 0,
                                               "WItemListFiles");
}

int ControllerListFilesFolder::rowCount(const QModelIndex &parent) const
{
    if (parent.isValid())
        return 0;

    return this->_files.size();
}

QHash<int, QByteArray> ControllerListFilesFolder::roleNames() const
{
    static QHash<int, QByteArray> mapping {
        {Roles::Path, "path"},
        {Roles::LastModification, "last_mod"}
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

void ControllerListFilesFolder::duplicateData(int row)
{
    if (row < 0 or row >= this->_files.size()) {
        qWarning() << "ControllerListFilesFolder::duplicateData index out of bound";
        return;
    }

    const Files &data = _files[row];
    const int rowOfInsert = row + 1;

    beginInsertRows(QModelIndex(), rowOfInsert, rowOfInsert);
    _files.insert(rowOfInsert, data);
    endInsertRows();
}

void ControllerListFilesFolder::removeData(int row)
{
    if (row < 0 or row >= this->_files.size()) {
        qWarning() << "ControllerListFilesFolder::duplicateData index out of bound";
        return;
    }

    beginRemoveRows(QModelIndex(), row, row);
    _files.removeAt(row);
    endRemoveRows();
}

QVariant ControllerListFilesFolder::data(const QModelIndex& index, int role) const
{
    if ( !index.isValid() )
        return {};

    qDebug() << "data" << role << index.row();

    if (index.row() < 0 || index.row() >= _files.count())
        return {};

    const auto &data = _files.at(index.row());

    switch (role) {
        case Roles::Path: return { data.getName() };
        case Roles::LastModification: return {data.getLastMod() };
        default: break;
    }

    qWarning() << "ControllerListFilesFolder::data unkown role" << role;
    return {};
}

