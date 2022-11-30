#pragma once

#include <qqml.h>
#include <QDebug>
#include <QObject>
#include <QList>
#include <QObjectList>
#include <QAbstractListModel>

struct Data {
    Data() {}
    Data( const QString& name, const QString& flag, double population )
        : nome(name), flag(flag), population(population) {}
    QString nome;
    QString flag;
    double population;
};

class controllerList : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        Nome = Qt::UserRole,
        Cognome,
        Eta
    };

    explicit controllerList(QObject *parent = nullptr);

    int rowCount(const QModelIndex& parent) const override;
    QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;
    QHash<int, QByteArray> roleNames() const override;

public slots:
    void duplicateData(int row);
    void removeData(int row);

private slots:
    void growPopulation();

private: //members
    QVector< Data > m_data;
};
