#include "WQMLCanvasComponent.h"
#include <QPainter>
#include <QBrush>
#include "ControllerCanvas.h"
#include "core/Pixmap/WPixmap.h"
#include "core/core.h"
#include <QRunnable>
#include <functional>
#include <QQuickWindow>
#include <QThread>
#include <QOpenGLTexture>
#include <QOpenGLFramebufferObject>
#include <QOpenGLBuffer>

WQMLCanvasComponentStroke::WQMLCanvasComponentStroke(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , _index(0)
    , _getImg([](QPainter &, double, WFlags<UpdateEvent::UpdateEventType>) {})
    , _functionSet(false)
{
    qDebug() << "WQMLCanvasComponentStroke constructor call";
    ControllerCanvas::registerDrawerStroke(this);
    this->setAntialiasing(true);
    this->setFlag(QQuickItem::Flag::ItemClipsChildrenToShape);
    this->callUpdate(this->getIndex());
    qDebug() << this->width() << this->height();
    //Q_ASSERT(false);
}

void WQMLCanvasComponentStroke::paint(QPainter *painter)
{
    const auto width = this->width();
    static int i = 0;

    TIME_START_STATIC(paint_hz);
    TIME_START(paint_var);

    if (this->_functionSet) {
        this->_getImg(*painter, width, WFlags{UpdateEvent::stroke});
    }

    /*
    if (i > 200)
        i = 0;
    i++;*/

    const auto e = std::chrono::high_resolution_clock::now();
    const auto hz =  1./((e - paint_hz).count() * 1e-9);
    paint_hz = e;

    if (hz < 50 or 1) {
        qDebug() << "problemi signori: " << hz << "\t" << (void *)this << this->getIndex();
    }

    TIME_STOP_STATIC(paint_hz, "Paint call: ");
    //TIME_STOP(paint_var, "Paint: ");
    if (getIndex() == 0){
        //update();
    }
}

bool WQMLCanvasComponentStroke::event(QEvent *event)
{
    return QQuickPaintedItem::event(event);
}

void WQMLCanvasComponentStroke::setXPosition(double x)
{
    this->_x = x;
    WDebug(true, "call");
    emit onXPositionChanged();
}

double WQMLCanvasComponentStroke::xPosition() const
{
    return this->_x;
}

double WQMLCanvasComponentStroke::yPosition() const
{
    return this->_y;
}

int WQMLCanvasComponentStroke::getIndex() const
{
    //qDebug() << "getIndex" << (void*)this << _index;
    return this->_index;
}

void WQMLCanvasComponentStroke::setIndex(int index)
{
    if (this->_index != index) {
        this->_index = index;
        emit onIndexChanged();
        this->callUpdate(index);
    }
}

void WQMLCanvasComponentStroke::setFunc(std::function<void (QPainter &painter, double width, WFlags<UpdateEvent::UpdateEventType>)> getImg)
{
    assert(_functionSet == false);
    this->_functionSet = true;
    this->_getImg = std::move(getImg);
}

void WQMLCanvasComponentStroke::callUpdate(int page)
{
    if (page == this->_index) {
        this->update();
        WDebug(false, "call");
    }
}

void WQMLCanvasComponentStroke::setYPosition(double y)
{
    this->_y = y;
    emit onYPositionChanged();
    WDebug(true, "call");
}
