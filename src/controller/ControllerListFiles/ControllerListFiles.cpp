#include <QQuickWindow>
#include <utility>
#include "ControllerListFiles.h"
#include "core/WDir.h"
#include "controller/Controller.h"

static ControllerListFiles *instance;

ControllerListFiles::ControllerListFiles(
            QObject *parent,
            const Fn<WString()>& getCurrentPath
        )
    : QObject(parent)
    , _getCurrentPath(getCurrentPath)
    , _controllerFiles(new WQMLControllerListFiles(this, _getCurrentFiles, _removeFileFromFolder))
    , _controllerFolders(new WQMLControllerListFolder(this, _controllerFiles))
{
    Controller::registerType("_controllerListFilesModel", _controllerFiles);
    Controller::registerType("_controllerListFoldersModel", _controllerFolders);

    instance = this;
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
    WString currentPath = _getCurrentPath().addSlashIfNecessary() + name;

    if (Directory::exists(currentPath.toUtf8()))
        return false;

    _controllerFolders->addFolder(Directory(currentPath.toUtf8()));
    return true;
}
