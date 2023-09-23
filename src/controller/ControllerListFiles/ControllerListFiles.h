#pragma once

#include <QObject>

#include "WQMLControllerListFiles.h"
#include "WQMLControllerListFolder.h"
#include "core/pointer/SharedPtr.h"
#include "file/FileManager.h"

class ControllerListFiles: public QObject
{
    Q_OBJECT
private:
    const SharedPtr<FileManager> &_fileManager;
public:
    ControllerListFiles(QObject *parent, const SharedPtr<FileManager>& fileManager);
    ~ControllerListFiles() override = default;

public:
    Q_INVOKABLE void selectFile(QString name);
    Q_INVOKABLE void selectFolder(QString name);
    Q_INVOKABLE bool createNewFolder(QString name);
    Q_INVOKABLE bool createNewFile(QString name);

    static
    auto getInstance() -> ControllerListFiles *;

signals:
    void onSelectFile(QString name);
    void onSelectFolder(QString name);

private:

    WQMLControllerListFiles  *_controllerFiles;
    WQMLControllerListFolder *_controllerFolders;
};
