#pragma once

#include <QObject>
#include <QAbstractListModel>
#include "Folder.h"
#include "ControllerListFiles.h"

class ControllerListFilesFolder: public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ControllerListFilesFolder(QObject *parent = nullptr);
    ~ControllerListFilesFolder() = default;

    enum Roles {
        FolderName = Qt::UserRole, /* QByteArray */
    };

    [[nodiscard]] int rowCount(const QModelIndex& parent) const override;
    QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;
    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

    Q_PROPERTY(bool isVisible READ isVisible WRITE setVisible NOTIFY isVisibleChanged);
    [[nodiscard]] bool isVisible() const;
    void setVisible(bool visible);
    Q_SIGNAL void isVisibleChanged();

    Q_PROPERTY(QString dir_selected READ getDirSelected NOTIFY onDirSelectedChanged);
    [[nodiscard]] QString getDirSelected() const;
    Q_SIGNAL void onDirSelectedChanged();

public slots:
    void duplicateData(int row);
    void removeData(int row);
    void click(int index);

private:
    QList<Folder> _folder;
    bool _is_visible;
    int _selected;
    ControllerListFiles *_controllerListFiles;
};
