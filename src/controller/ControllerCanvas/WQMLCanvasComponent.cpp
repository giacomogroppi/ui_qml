#include "WQMLCanvasComponent.h"
#include <QPainter>
#include <QBrush>
#include "ControllerCanvas.h"
#include "core/WPixmap.h"
#include "core/core.h"
#include <QRunnable>
#include <functional>
#include <QQuickWindow>
#include <QThread>
#include <QOpenGLTexture>
#include <QOpenGLFramebufferObject>
#include <QOpenGLBuffer>

WQMLCanvasComponent::WQMLCanvasComponent(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , _getImg([](QPainter &, double) {
    })
    , _functionSet(false)
    , _index(0)
{
    qDebug() << "WQMLCanvasComponent constructor call";
    ControllerCanvas::registerDrawer(this);
    this->setAntialiasing(true);
    this->setFlag(QQuickItem::Flag::ItemClipsChildrenToShape);
    this->callUpdate(this->getIndex());
    qDebug() << this->width() << this->height();
    //Q_ASSERT(false);
}

void WQMLCanvasComponent::paint(QPainter *painter)
{
    const auto width = this->width();
    static int i = 0;

    TIME_START_STATIC(paint_hz);
    TIME_START(paint_var);

    if (this->_functionSet) {
        WDebug(true, "call");
        //this->_getImg(*painter, width);
    }

    painter->drawLine(0 + i, 0 + i, 300 + i, 300 + i);

    /*
    if (i > 200)
        i = 0;
    i++;*/

    const auto e = std::chrono::high_resolution_clock::now();
    const auto hz =  1./((e - paint_hz).count() * 1e-9);
    paint_hz = e;

    if (hz < 50) {
        qDebug() << "problemi signori: " << hz;
    }

    //TIME_STOP_STATIC(paint_hz, "Paint call: ");
    //TIME_STOP(paint_var, "Paint: ");
    if (_index == 0)
        update();
}

bool WQMLCanvasComponent::event(QEvent *event)
{
    return QQuickPaintedItem::event(event);
}

void WQMLCanvasComponent::setXPosition(double x)
{
    this->_x = x;
    WDebug(true, "call");
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

int WQMLCanvasComponent::getIndex() const
{
    return this->_index;
}

void WQMLCanvasComponent::setIndex(int index)
{
    if (this->_index != index) {
        this->_index = index;
        emit onIndexChanged();
        this->callUpdate(index);
    }
}

void WQMLCanvasComponent::setFunc(std::function<void (QPainter &painter, double width)> getImg)
{
    assert(_functionSet == false);
    this->_functionSet = true;
    this->_getImg = std::move(getImg);
}

void WQMLCanvasComponent::callUpdate(int page)
{
    if (page == this->_index) {
        //this->update();
        WDebug(true, "call");
    }
}

void WQMLCanvasComponent::setYPosition(double y)
{
    this->_y = y;
    emit onYPositionChanged();
    WDebug(true, "call");
}
