#include <QQuickWindow>
#include <utility>
#include "ControllerListFiles.h"
#include "core/WDir.h"
#include "controller/Controller.h"

static ControllerListFiles *instance;

ControllerListFiles::ControllerListFiles(
            QObject *parent,
            const SharedPtr<FileManager>& fileManager
        )
    : QObject(parent)
    , _fileManager(fileManager)
    , _controllerFiles(new WQMLControllerListFiles(this, _fileManager))
    , _controllerFolders(new WQMLControllerListFolder(this, _fileManager))
{
    Controller::registerType("_controllerListFilesModel", _controllerFiles);
    Controller::registerType("_controllerListFoldersModel", _controllerFolders);

    instance = this;

    _controllerFiles->updateList();

    QObject::connect(_controllerFolders, &WQMLControllerListFolder::onDirSelectedChanged, [&] { _controllerFiles->updateList(); });
}

auto ControllerListFiles::createNewFile(QString name) -> bool
{
    const auto result = this->_controllerFiles->createNewFile(name) == 0;

    if (result)
        emit onSelectFile(name);

    return result;
}

auto ControllerListFiles::getInstance() -> ControllerListFiles *
{
    return instance;
}

auto ControllerListFiles::selectFile(QString name) -> void
{
    emit this->onSelectFile(std::move(name));
}

auto ControllerListFiles::selectFolder(QString name) -> void
{
    emit this->onSelectFolder(std::move(name));
}

auto ControllerListFiles::createNewFolder(QString name) -> bool
{
    if (_fileManager->createDirectory(name) < 0)
        return false;

    return true;
}
