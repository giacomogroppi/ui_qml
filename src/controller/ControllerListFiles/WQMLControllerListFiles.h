#pragma once

#include <QObject>
#include <QAbstractListModel>
#include "file/File.h"
#include "file/Directory.h"
#include "core/pointer/SharedPtr.h"
#include "file/FileManager.h"

class WQMLControllerListFiles: public QAbstractListModel
{
    Q_OBJECT

public:
    explicit WQMLControllerListFiles(QObject *parent,
                                     const SharedPtr<FileManager>& fileManager);

    ~WQMLControllerListFiles() override = default;

    enum Roles {
        Path = Qt::UserRole, /* QByteArray */
        LastModification /*  */
    };

    [[nodiscard]] int rowCount(const QModelIndex& parent) const override;
    QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;
    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

    auto createNewFile(const QString &name) -> int;

public slots:
    void duplicateData(int row);
    void removeData(int row);

private:
    const SharedPtr<FileManager>& _fileManager;

public:
    void updateList();
};
