#include "WQMLCanvasComponent.h"
#include <QPainter>
#include <QBrush>
#include "ControllerCanvas.h"
#include "core/WPixmap.h"
#include "core/core.h"
#include <functional>

WQMLCanvasComponent::WQMLCanvasComponent(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , _getImg([](QPainter &, double) {
    })
    , _functionSet(false)
{
    qDebug() << "WQMLCanvasComponent constructor call";
    ControllerCanvas::registerDrawer(this);
    this->setAntialiasing(true);
    this->setRenderTarget(QQuickPaintedItem::Image);
}

void WQMLCanvasComponent::paint(QPainter *painter)
{
    const auto width = this->width();
    const auto height = this->height();

    core::painter_set_antialiasing(*painter);
    painter->setRenderHint(QPainter::LosslessImageRendering);

    TIME_START(paint_var);

    if (this->_functionSet) {
        //const QImage img = this->_getImg();

        this->_getImg(*painter, width);
    }

    TIME_STOP(paint_var, "Paint: ");
    //qDebug() << "Paint T=" << diff << "ms" << "Time for getImg(): " << (timeNew - timeOld).count() << "["<< 1./(double(diff) / 1000.) << "Hz]";
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

void WQMLCanvasComponent::setFunc(std::function<void (QPainter &painter, double width)> getImg)
{
    this->_functionSet = true;
    this->_getImg = std::move(getImg);
}

void WQMLCanvasComponent::callUpdate()
{
    this->update();
}

void WQMLCanvasComponent::setYPosition(double y)
{
    this->_y = y;
    emit onYPositionChanged();
}
