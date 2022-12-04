#include "controllerList.h"
#include <QDebug>
#include <QTimer>

controllerList::controllerList(QObject *parent) :
    QAbstractListModel(parent)
{
    m_data
        << Data("Denmark", "Gianfranco", 5.6)
        << Data("Sweden", "Genoveffo", 9.6)
        << Data("Iceland", "Rossi", 0.3)
        << Data("Norway", "Forlanini", 5.1)
        << Data("Finland", "Agnelli", 5.4);

    QTimer *growthTimer = new QTimer(this);
    connect(growthTimer, &QTimer::timeout, this, &controllerList::growPopulation);
    //growthTimer->start(2000);
}

int controllerList::rowCount( const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;

    //qDebug() << "rowCount";

    return m_data.count();
}

QVariant controllerList::data(const QModelIndex &index, int role) const
{
    if ( !index.isValid() )
        return QVariant();

    //qDebug() << "data" << role << index.row();

    const Data &data = m_data.at(index.row());
    if ( role == Nome ){
        return data.nome;
    }
    else if ( role == Cognome )
        return data.flag;
    else if ( role == Eta )
        return data.population;
    else
        return QVariant();
}

//--> slide
QHash<int, QByteArray> controllerList::roleNames() const
{
    static QHash<int, QByteArray> mapping {
        {Nome, "nome"},
        {Cognome, "cognome"},
        {Eta, "eta"}
    };

    //qDebug() << "roleNames";

    return mapping;
}
//<-- slide

void controllerList::duplicateData(int row)
{
    if (row < 0 || row >= m_data.count())
        return;

    const Data data = m_data[row];
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
        m_data[i].population += m_data[i].population * rand() * growthFactor;
    }

    // we've just updated all rows...
    const QModelIndex startIndex = index(0, 0);
    const QModelIndex endIndex   = index(count - 1, 0);

    // ...but only the population field
    emit dataChanged(startIndex, endIndex, QVector<int>() << Eta);
}
    //emit beginInsertRows(QModelIndex(), m_data.length() - 1, m_data.length() - 1);
    //m_data << DataTesting("g6", "c6", 54);
    //emit endInsertRows();

