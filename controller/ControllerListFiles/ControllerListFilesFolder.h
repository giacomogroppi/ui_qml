#pragma once

#include <QObject>
#include <QAbstractListModel>

class ControllerListFilesFolder: public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ControllerListFilesFolder(QObject *parent = nullptr);

private:
};
