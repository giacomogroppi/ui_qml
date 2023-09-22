#pragma once

#include <QObject>

#include "WQMLControllerListFiles.h"
#include "WQMLControllerListFolder.h"

class ControllerListFiles: public QObject
{
    Q_OBJECT
public:
    ControllerListFiles(QObject *parent, const Fn<WString()>& getCurrentPath);
    ~ControllerListFiles() override = default;

public:
    Q_INVOKABLE void selectFile(QString name);
    Q_INVOKABLE void selectFolder(QString name);
    Q_INVOKABLE bool createNewFolder(QString name);

    static
    auto getInstance() -> ControllerListFiles *;

signals:
    void onSelectFile(QString name);
    void onSelectFolder(QString name);

private:
    Fn<const WListFast<WFile>& ()> _getCurrentFiles = [] { return ControllerListFiles::getInstance()->_controllerFolders->getFiles(); };
    Fn<int(QString name)> _removeFileFromFolder = [] (QString name) { return ControllerListFiles::getInstance()->_controllerFolders->removeFile(name); };
    Fn<WString()> _getCurrentPath;

    WQMLControllerListFiles  *_controllerFiles;
    WQMLControllerListFolder *_controllerFolders;
};
