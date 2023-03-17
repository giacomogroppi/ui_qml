#pragma once

#include <qqml.h>
#include <QDebug>
#include <QObject>
#include <QList>
#include <QObjectList>
#include <QAbstractListModel>

struct Data {
    Data() {}
    Data( const QString& name, const QString& flag, double population ) {};

};

class ControllerList : public QAbstractListModel
{
    Q_OBJECT
private:
    bool _isVisible;

public:
    enum Roles {
        Nome = Qt::UserRole,
        Cognome,
        Eta
    };

    explicit ControllerList(QObject *parent = nullptr);

    int rowCount(const QModelIndex& parent) const override;
    QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;
    QHash<int, QByteArray> roleNames() const override;

    Q_PROPERTY(bool isVisible READ isVisible WRITE setVisible NOTIFY isVisibleChanged);
    bool isVisible() const;
    void setVisible(bool visible);
    Q_SIGNAL void isVisibleChanged();

public slots:
    void duplicateData(int row);
    void removeData(int row);
    void modifiedPages(int page);
    void modifiedPages(const std::vector<int> &page);

private slots:
    void growPopulation();

private: //members

    friend class WQMLItemListComponent;

    const QImage &getImg(int index);

    QVector< Data > m_data;

    static ControllerList *instance();
    static void registerItem(class WQMLItemListComponent *item);
};
