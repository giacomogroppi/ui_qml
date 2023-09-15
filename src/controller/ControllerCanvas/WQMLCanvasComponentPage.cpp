#include "WQMLCanvasComponentPage.h"
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

WQMLCanvasComponentPage::WQMLCanvasComponentPage(QQuickItem *parent)
        : QQuickPaintedItem(parent)
        , WObject(nullptr)
        , _index(0)
        , _getImg([](QPainter &, double, WFlags<UpdateEvent::UpdateEventType>) {})
        , _functionSet(false)
{
    qDebug() << "WQMLCanvasComponentStroke constructor call";
    ControllerCanvas::registerDrawerPage(this);
    this->setAntialiasing(true);
    this->setFlag(QQuickItem::Flag::ItemClipsChildrenToShape);
    this->callUpdate(this->getIndex());
    qDebug() << this->width() << this->height();

    //Q_ASSERT(false);
}

void WQMLCanvasComponentPage::paint(QPainter *painter)
{
    WDebug(true, "call" << _functionSet);
    if (this->_functionSet) {
        this->_getImg(*painter, width(), UpdateEvent::page | UpdateEvent::sheet);
    }
    W_EMIT_0(FinishDraw);
    painter->drawLine(200, 0, 1000, 1000);
}

bool WQMLCanvasComponentPage::event(QEvent *event)
{
    return QQuickPaintedItem::event(event);
}

void WQMLCanvasComponentPage::setXPosition(double x)
{
    this->_x = x;
    WDebug(true, "call");
    emit onXPositionChanged();
}

double WQMLCanvasComponentPage::xPosition() const
{
    return this->_x;
}

double WQMLCanvasComponentPage::yPosition() const
{
    return this->_y;
}

int WQMLCanvasComponentPage::getIndex() const
{
    //qDebug() << "getIndex" << (void*)this << _index;
    return this->_index;
}

void WQMLCanvasComponentPage::setIndex(int index)
{
    if (this->_index != index) {
        this->_index = index;
        emit onIndexChanged();
        this->callUpdate(index);
    }
}

void WQMLCanvasComponentPage::setFunc(std::function<void (QPainter &painter, double width, WFlags<UpdateEvent::UpdateEventType> updateFlag)> getImg)
{
    assert(_functionSet == false);
    this->_functionSet = true;
    this->_getImg = std::move(getImg);
}

void WQMLCanvasComponentPage::callUpdate(int page)
{
    WDebug(true, page << _index);
    if (page == this->_index) {
        this->update();
        WDebug(false, "call");
    }
}

void WQMLCanvasComponentPage::setYPosition(double y)
{
    this->_y = y;

    emit onYPositionChanged();
    WDebug(true, "call");
}
