#pragma once

#include <QObject>
#include <QAbstractListModel>
#include "WQMLControllerListFiles.h"
#include "file/Directory.h"
#include "core/pointer/SharedPtr.h"
#include <filesystem>
#include "file/FileManager.h"

class WQMLControllerListFolder: public QAbstractListModel
{
    Q_OBJECT

    using Path = std::filesystem::path;

public:
    explicit WQMLControllerListFolder(QObject *parent, const SharedPtr<FileManager>& fileManager);
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

public slots:
    void duplicateData(int row);
    void removeData(int row);
    void click(int index);

private:
    const SharedPtr<FileManager> &_fileManager;
    bool _is_visible;
    //WQMLControllerListFiles *_controllerListFiles;

    /**
     * \brief This method reset all the data structure and add all the object
     * to the view.
     * */
    auto updateList() -> void;

    static
    auto getPath(const WString &path) -> Path;
};
