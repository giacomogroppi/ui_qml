#pragma once

#include <QObject>
#include <QAbstractListModel>
#include "file/File.h"
#include "file/Directory.h"

class WQMLControllerListFiles: public QAbstractListModel
{
    Q_OBJECT
public:
    explicit WQMLControllerListFiles(QObject *parent,
                                     Fn<const WListFast<WFile>&()> getCurrentFiles,
                                     Fn<int(QString name)> removeFileFromDirectory );

    ~WQMLControllerListFiles() override = default;

    enum Roles {
        Path = Qt::UserRole, /* QByteArray */
        LastModification /*  */
    };

    [[nodiscard]] int rowCount(const QModelIndex& parent) const override;
    QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;
    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

public slots:
    void duplicateData(int row);
    void removeData(int row);
    void clickFile(int index);

private:
    Fn<const WListFast<WFile>&()> _getCurrentFiles;
    Fn<int(QString file)> _removeFileFromDirectory;

public:
    void updateList();
};
