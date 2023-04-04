#include "WQMLCanvasHandler.h"
#include <QPainter>
#include <QBrush>
#include "ControllerCanvas.h"
#include "utils/WCommonScript.h"

WQMLCanvasHandler::WQMLCanvasHandler(QQuickItem *parent)
    : QQuickItem(parent)
    , _targetTouchArea(nullptr)
    , _waitingForEnd(false)
{
    this->update();

    ControllerCanvas::registerHangler(this);

    qDebug() << "WQMLCanvasComponent constructor call";
}

void WQMLCanvasHandler::touchEventPrivate(QTouchEvent *event)
{
    qDebug() << "WQMLCanvasComponent::touchEvent " << event->type();
    //return QQuickPaintedItem::touchEvent(event);
}

QQuickItem *WQMLCanvasHandler::targetTouchArea() const
{
    return this->_targetTouchArea;
}

void WQMLCanvasHandler::setTargetTouchArea(QQuickItem *targetTouchArea)
{
    if (targetTouchArea == _targetTouchArea)
        return;

    if (_targetTouchArea)
        _targetTouchArea->removeEventFilter(this);

    _targetTouchArea = targetTouchArea;

    if (_targetTouchArea)
        _targetTouchArea->installEventFilter(this);

    emit targetTouchAreaChanged();
}

bool WQMLCanvasHandler::eventFilter(QObject * obj, QEvent *event)
{
    if (auto *e = dynamic_cast<QMouseEvent*>(event)) {
        const double pressure = e->points().at(0).pressure() * 5;
        if (e->isBeginEvent()) {
            emit touchBegin(e->position(), pressure);
        } else if (e->isUpdateEvent()) {
            emit touchUpdate(e->position(), pressure);
        } else {
            W_ASSERT(e->isEndEvent());
            emit touchEnd(e->position(), pressure);
        }
        return true;
    }

    if (event->type() == QEvent::TouchUpdate || event->type() == QEvent::TouchBegin || event->type() == QEvent::TouchEnd) {
        //this->touchEventPrivate(dynamic_cast<QTouchEvent *>(event));
        //return true;
    }

    return false;
}
