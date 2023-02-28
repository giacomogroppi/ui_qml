#pragma once

#include <QObject>
#include <QAbstractListModel>
#include "Files.h"

class ControllerListFilesFolder: public QAbstractListModel
{
    Q_OBJECT

public:
    explicit ControllerListFilesFolder(QObject *parent = nullptr);

    enum Roles {
        Path = Qt::UserRole, /* QByteArray */
        LastModification /*  */
    };

    [[nodiscard]] int rowCount(const QModelIndex& parent) const override;
    QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;
    [[nodiscard]] QHash<int, QByteArray> roleNames() const override;

    Q_PROPERTY(bool isVisible READ isVisible WRITE setVisible NOTIFY isVisibleChanged);
    [[nodiscard]] bool isVisible() const;
    void setVisible(bool visible);
    Q_SIGNAL void isVisibleChanged();

public slots:
    void duplicateData(int row);
    void removeData(int row);
    void modifiedPages(int page);
    void modifiedPages(const std::vector<int> &page);

private:
    QVector<Files> _files;
    bool _is_visible;
};
