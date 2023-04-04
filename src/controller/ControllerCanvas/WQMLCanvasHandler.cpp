#include "WQMLCanvasHandler.h"
#include <QPainter>
#include <QBrush>
#include "ControllerCanvas.h"
#include "touch/dataTouch/page/Page.h"
#include "utils/WCommonScript.h"

WQMLCanvasHandler::WQMLCanvasHandler(QQuickItem *parent)
    : QQuickItem(parent)
    , _targetTouchArea(nullptr)
    , _waitingForEnd(false)
    , _w(0)
    , _h(0)
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
        if (!_h or !_w)
            return false;

        const double pressure = 0.3; e->points().at(0).pressure() * 5.;
        const double dw = 1.675;
        const double dh = 1.6655;
        const QPointF point = QPointF (
                                    (e->position().x() - 34.8548) * dw,
                                    (e->position().y() - 34.6371) * dh
                                  ) + QPointF(34.8548, 34.6371);
        qDebug() << point;
        if (e->isBeginEvent()) {
            emit touchBegin(point, pressure);
        } else if (e->isUpdateEvent()) {
            emit touchUpdate(point, pressure);
        } else {
            W_ASSERT(e->isEndEvent());
            emit touchEnd(point, pressure);
        }
        return true;
    }

    if (event->type() == QEvent::TouchUpdate || event->type() == QEvent::TouchBegin || event->type() == QEvent::TouchEnd) {
        //this->touchEventPrivate(dynamic_cast<QTouchEvent *>(event));
        //return true;
    }

    return false;
}
