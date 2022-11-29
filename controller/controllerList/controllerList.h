#pragma once

#include <qqml.h>
#include <QDebug>
#include <QObject>
#include <QList>
#include <QObjectList>
#include <QAbstractListModel>

class DataTesting {
public:
    DataTesting(const QString &name, const QString &cognome, int eta)
    {
        _nome = name;
        _cognome = cognome;
        _eta = eta;
    }

    int _eta;
    QString _nome, _cognome;
};

class controllerList: public QAbstractListModel
{
    Q_OBJECT
public:
    controllerList(QObject *parent = nullptr);
    ~controllerList() = default;

    enum Roles {
        NamePerson = Qt::UserRole,
        CognomePerson,
        Eta
    };

    int rowCount(const QModelIndex& parent) const override;
    QVariant data( const QModelIndex& index, int role = Qt::DisplayRole ) const override;
    QHash<int, QByteArray> roleNames() const override;

public slots:
    void duplicateData(int row);
    void removeData(int row);

private slots:
    void growPopulation();

private: //members
    QVector< DataTesting > m_data;

};
