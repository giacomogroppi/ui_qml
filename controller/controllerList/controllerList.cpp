#include "controllerList.h"
#include <QDebug>
#include <QTimer>

controllerList::controllerList(QObject *parent) :
    QAbstractListModel(parent)
{
    m_data
        << DataTesting("g1", "c1", 51)
        << DataTesting("g2", "c2", 94)
        << DataTesting("g3", "c3", 14)
        << DataTesting("g4", "c4", 49)
        << DataTesting("g5", "c5", 5);

    QTimer *growthTimer = new QTimer(this);
    connect(growthTimer, &QTimer::timeout, this, &controllerList::growPopulation);
    growthTimer->start(2000);
}

int controllerList::rowCount( const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;

    return m_data.count();
}

QVariant controllerList::data(const QModelIndex &index, int role) const
{
    if ( !index.isValid() )
        return QVariant();

    const auto &data = m_data.at(index.row());
    if ( role == Roles::NamePerson ){
        return data._nome;
    }
    else if ( role == Roles::CognomePerson )
        return data._cognome;
    else if( role == Roles::Eta )
        return data._eta;
    else
        return QVariant();
}

//--> slide
QHash<int, QByteArray> controllerList::roleNames() const
{
    static QHash<int, QByteArray> mapping {
        {Roles::NamePerson, "name"},
        {Roles::CognomePerson, "flag"},
        {Roles::Eta, "eta"}
    };
    return mapping;
}
//<-- slide

void controllerList::duplicateData(int row)
{
    if (row < 0 || row >= m_data.count())
        return;

    const DataTesting data = m_data[row];
    const int rowOfInsert = row + 1;

    beginInsertRows(QModelIndex(), rowOfInsert, rowOfInsert);
    m_data.insert(rowOfInsert, data);
    endInsertRows();
}

void controllerList::removeData(int row)
{
    if (row < 0 || row >= m_data.count())
        return;

    beginRemoveRows(QModelIndex(), row, row);
    m_data.removeAt(row);
    endRemoveRows();
}

void controllerList::growPopulation()
{
    const double growthFactor = 0.01 / RAND_MAX;

    const int count = m_data.count();
    for (int i = 0; i < count; ++i) {
        m_data[i]._eta += m_data[i]._eta * rand() * growthFactor;
    }

    // we've just updated all rows...
    const QModelIndex startIndex = index(0, 0);
    const QModelIndex endIndex   = index(count - 1, 0);

    // ...but only the population field
    emit dataChanged(startIndex, endIndex, QVector<int>() << Roles::Eta);

    emit beginInsertRows(QModelIndex(), m_data.length() - 1, m_data.length() - 1);
    m_data << DataTesting("g6", "c6", 54);
    emit endInsertRows();
}
