#include "WQMLCanvasComponent.h"
#include <QPainter>
#include <QBrush>
#include "ControllerCanvas.h"

WQMLCanvasComponent::WQMLCanvasComponent(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , _img(nullptr)
{
    qDebug() << "WQMLCanvasComponent constructor call";
    ControllerCanvas::registerDrawer(this);
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

void WQMLCanvasComponent::setXPosition(double x)
{
    this->_x = x;
    emit onXPositionChanged();
}

double WQMLCanvasComponent::xPosition() const
{
    return this->_x;
}

double WQMLCanvasComponent::yPosition() const
{
    return this->_y;
}

void WQMLCanvasComponent::update(const QImage &img)
{
    this->_img = &img;
    callUpdate();
}

void WQMLCanvasComponent::callUpdate()
{
    QQuickPaintedItem::update();
}

void WQMLCanvasComponent::setYPosition(double y)
{
    this->_y = y;
    emit onYPositionChanged();
}
