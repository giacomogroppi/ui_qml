#include "ControllerList.h"
#include "controller/ControllerList/WQMLItemListComponent.h"
#include <QImage>
#include <QDebug>
#include <QTimer>
#include <QList>
#include "controller/Controller.h"

static ControllerList *instanceObject;
static QList<WQMLItemListComponent*> item = {};

static bool init = false;

ControllerList::ControllerList(QObject *parent)
    : QAbstractListModel(parent)
    , _isVisible(true)
    , m_data()
{
    Q_ASSERT(init == false);
    init = true;

    qmlRegisterType<WQMLItemListComponent>("writernote.WQMLItemListPreview",
                                           1, 0,
                                           "WItemListPreview");
    /*
    m_data
        << Data("Denmark", "Gianfranco", 5.6)
        << Data("Sweden", "Genoveffo", 9.6)
        << Data("Iceland", "Rossi", 0.3)
        << Data("Norway", "Forlanini", 5.1)
        << Data("Finland", "Agnelli", 5.4);
    */

    auto *growthTimer = new QTimer(this);
    connect(growthTimer, &QTimer::timeout, this, &ControllerList::growPopulation);

    instanceObject = this;

    qDebug() << "Controller List constructor" << this;
    //growthTimer->start(2000);
}

int ControllerList::rowCount( const QModelIndex& parent) const
{
    if (parent.isValid())
        return 0;

    //qDebug() << "rowCount";

    return m_data.count();
}

QVariant ControllerList::data(const QModelIndex &index, int role) const
{
    if ( !index.isValid() )
        return QVariant();

    qDebug() << "data" << role << index.row();

    //const Data &data = m_data.at(index.row());
    return QVariant();
}

//--> slide
QHash<int, QByteArray> ControllerList::roleNames() const
{
    static QHash<int, QByteArray> mapping {
        {Nome, "nome"},
        {Cognome, "cognome"},
        {Eta, "eta"}
    };

    //qDebug() << "roleNames";

    return mapping;
}

bool ControllerList::isVisible() const
{
    qDebug() << "ControllerList::isVisible" << this->_isVisible;
    return this->_isVisible;
}

void ControllerList::setVisible(bool visibility)
{
    const auto change = visibility != this->_isVisible;
    this->_isVisible = visibility;

    if (change) {
        emit isVisibleChanged();
    }
}

void ControllerList::duplicateData(int row)
{
    if (row < 0 || row >= m_data.count())
        return;

    const auto &data = m_data[row];
    const int rowOfInsert = row + 1;

    beginInsertRows(QModelIndex(), rowOfInsert, rowOfInsert);
    m_data.insert(rowOfInsert, data);
    endInsertRows();
}

void ControllerList::removeData(int row)
{
    if (row < 0 || row >= m_data.count())
        return;

    beginRemoveRows(QModelIndex(), row, row);
    m_data.removeAt(row);
    endRemoveRows();
}

void ControllerList::modifiedPages(int page)
{
    item.at(page)->needRefresh();
}

void ControllerList::modifiedPages(const std::vector<int> &page)
{
    for (const auto index : page) {
        this->modifiedPages(index);
    }
}

void ControllerList::growPopulation()
{
    const double growthFactor = 0.01 / RAND_MAX;

    const int count = m_data.count();

    // we've just updated all rows...
    const QModelIndex startIndex = index(0, 0);
    const QModelIndex endIndex   = index(count - 1, 0);

    // ...but only the population field
    emit dataChanged(startIndex, endIndex, QVector<int>() << Eta);
}

const QImage &ControllerList::getImg(int index)
{
    qDebug() << "ControllerList::getImg call";
    auto *i = new QImage;
    return *i;
}

ControllerList *ControllerList::instance()
{
    Q_ASSERT(instanceObject != nullptr);
    return instanceObject;
}

void ControllerList::registerItem(WQMLItemListComponent *object)
{
    Q_ASSERT(object != nullptr);
    qDebug() << "ControllerList::registerItem call";
    item.append(object);
}

//emit beginInsertRows(QModelIndex(), m_data.length() - 1, m_data.length() - 1);
//m_data << DataTesting("g6", "c6", 54);
//emit endInsertRows();
