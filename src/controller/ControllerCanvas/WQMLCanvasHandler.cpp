#include "WQMLCanvasHandler.h"
#include <QPainter>
#include <QBrush>

WQMLCanvasHandler::WQMLCanvasHandler(QQuickItem *parent)
    : QQuickItem(parent)
    , _targetTouchArea(nullptr)
    , _waitingForEnd(false)
{
    this->update();

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
    if (dynamic_cast<QMouseEvent*>(event)) {

    }

    if (event->type() == QEvent::TouchUpdate || event->type() == QEvent::TouchBegin || event->type() == QEvent::TouchEnd) {
        //this->touchEventPrivate(dynamic_cast<QTouchEvent *>(event));
        //return true;
    }
    // other Touch events here...

    //qDebug() << "WQMLCanvasHandler::eventFilter" << event->type();

    return false;
}
