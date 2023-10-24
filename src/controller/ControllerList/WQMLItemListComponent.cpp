#include "WQMLItemListComponent.h"
#include <QPainter>
#include "ControllerList.h"
#include "core/PointF.h"

WQMLItemListComponent::WQMLItemListComponent(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    qDebug() << "WQMLItemListComponent constructor";
    ControllerList::registerItem(this);
}

void WQMLItemListComponent::paint(QPainter *painter)
{
    auto *instance = ControllerList::instance();
    const auto &img = instance->getImg(this->indexObject());
    painter->drawImage(QPointF {0., 0.}, img);
}

int WQMLItemListComponent::indexObject()
{
    return this->_index;
}

void WQMLItemListComponent::setIndexObject(int index)
{
    this->_index = index;
    qDebug() << "Index set" << index;
    emit indexChangedObject();
}

void WQMLItemListComponent::needRefresh()
{
    this->update();
}
