#include "ControllerListFiles.h"
#include "controller/Controller.h"
#include "Scheduler/Scheduler.h"

WQMLControllerListFiles::WQMLControllerListFiles(QObject *parent,
                                                 const SharedPtr<FileManager>& fileManager)
    : QAbstractListModel(parent)
    , _fileManager(fileManager)
{
    const auto update = std::bind(&WQMLControllerListFiles::updateList, this);
    w_connect_lambda(fileManager.get(), onListFilesChanged, update);
    w_connect_lambda(fileManager.get(), onCurrentDirectoryChanged, update);

    Scheduler::addTaskMainThread(Scheduler::Ptr<WTaskFunction>::make(
            nullptr, WTask::DeleteLater, update)
    );
}

auto WQMLControllerListFiles::rowCount(const QModelIndex &parent) const -> int
{
    WDebug(debug, "call with size: " << _fileManager->getCurrentFiles().size());
    if (parent.isValid())
        return 0;

    return this->_fileManager->getCurrentFiles().size();
}

auto WQMLControllerListFiles::roleNames() const -> QHash<int, QByteArray>
{
    static QHash<int, QByteArray> mapping {
        {Roles::Path, "name_file"},
        {Roles::LastModification, "last_mod"}
    };

    return mapping;
}

auto WQMLControllerListFiles::createNewFile(const QString &name) -> int
{
    if (WString(name).contains({'\\', ':', '/'}))
        return -1;

    if (_fileManager->createFile (name, Document(), Extension::makeWriternote()) < 0)
        return -1;

    return 0;
}

void WQMLControllerListFiles::duplicateData(int row)
{
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
    const auto &files = this->_fileManager->getCurrentFiles();

    if (row < 0 or row >= files.size()) {
        qWarning() << "ControllerListFilesFolder::duplicateData index out of bound";
        return;
    }

    W_ASSERT(0);
    beginRemoveRows(QModelIndex(), row, row);
    //this->_removeFileFromDirectory(files.at(row).getName());
    endRemoveRows();
}

void WQMLControllerListFiles::updateList()
{
    WDebug(debug, "call");
    beginResetModel();
    endResetModel();
    //beginRemoveRows(QModelIndex(), row, row);
    //endRemoveRows();
}

auto WQMLControllerListFiles::data(const QModelIndex& index, int role) const -> QVariant
{
    const auto &files = this->_fileManager->getCurrentFiles();

    WDebug(debug, "call with size of file:" << files.size());

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
