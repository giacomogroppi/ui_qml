#pragma once

#include <QObject>
#include <QAbstractListModel>
#include "WQMLControllerListFiles.h"
#include "file/Directory.h"

class WQMLControllerListFolder: public QAbstractListModel
{
    Q_OBJECT

public:
    explicit WQMLControllerListFolder(QObject *parent = nullptr, WQMLControllerListFiles *files = nullptr);
    ~WQMLControllerListFolder() override = default;

    enum Roles {
        FolderName = Qt::UserRole, /* QByteArray */
    };

    [[nodiscard]] int rowCount(const QModelIndex& parent) const override;
    QVariant data( const QModelIndex& index, int role ) const override;
    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

    Q_PROPERTY(bool isVisible READ isVisible WRITE setVisible NOTIFY isVisibleChanged);
    [[nodiscard]] bool isVisible() const;
    void setVisible(bool visible);
    Q_SIGNAL void isVisibleChanged();

    Q_PROPERTY(QString dir_selected READ getDirSelected NOTIFY onDirSelectedChanged);
    [[nodiscard]] QString getDirSelected() const;
    Q_SIGNAL void onDirSelectedChanged();

    void addFolder(Directory &&directory);
    auto getFiles() const -> const WListFast<WFile> &;

    /**
     * \return &lt 0 in case of error
     * */
    auto removeFile(QString name) -> int;

public slots:
    void duplicateData(int row);
    void removeData(int row);
    void click(int index);

private:
    WListFast<Directory> _folder;
    bool _is_visible;
    int _selected;
    WQMLControllerListFiles *_controllerListFiles;
};
