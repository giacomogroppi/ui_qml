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
        : nome(name),
          cognome(cognome),
          eta(eta) {}

    int eta;
    QString nome, cognome;
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
    QHash<int, QByteArray> roleNames() const override {
        static QHash<int, QByteArray> mapping {
            {Roles::NamePerson,     "nome"},
            {Roles::CognomePerson,  "cognome"},
            {Roles::Eta,            "eta"}
        };

        qDebug() << "roleNames";

        return mapping;
    }

public slots:
    void duplicateData(int row);
    void removeData(int row);

private slots:
    void growPopulation();

private: //members
    QVector< DataTesting > m_data;

};
