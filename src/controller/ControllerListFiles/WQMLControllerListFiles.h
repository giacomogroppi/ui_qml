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

    [[nodiscard]]
    auto rowCount(const QModelIndex& parent) const -> int override;

    [[nodiscard]]
    auto data( const QModelIndex& index, int role = Qt::DisplayRole ) const -> QVariant override;

    [[nodiscard]]
    auto roleNames() const -> QHash<int, QByteArray> override;

    auto createNewFile(const QString &name) -> int;

public slots:
    void duplicateData(int row);
    void removeData(int row);

private:
    const SharedPtr<FileManager>& _fileManager;
    static constexpr auto debug = true;
public:
    void updateList();
};
