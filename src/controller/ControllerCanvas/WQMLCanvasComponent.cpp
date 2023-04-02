#include "WQMLCanvasComponent.h"
#include <QPainter>
#include <QBrush>

WQMLCanvasComponent::WQMLCanvasComponent(QQuickItem *parent)
    : QQuickPaintedItem(parent)
{
    this->update();

    qDebug() << "WQMLCanvasComponent constructor call";
}

void WQMLCanvasComponent::paint(QPainter *painter)
{
    const auto width = this->width();
    const auto height = this->height();
    QPen _pen(QColor(127, 127, 127, 255));

    qDebug() << "paint";

    painter->setPen(_pen);
    painter->setRenderHint(QPainter::Antialiasing);

    painter->drawLine(0, 0, width, height);
    painter->drawRect(0, 0, width, height);
}
