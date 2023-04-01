#pragma once

#include <QObject>
#include <QQuickPaintedItem>
#include <QTimer>

class WQMLCanvasComponent: public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem *targetTouchArea READ targetTouchArea WRITE setTargetTouchArea NOTIFY targetTouchAreaChanged)

public:
    WQMLCanvasComponent(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) override;

    bool eventFilter(QObject *, QEvent *event) override {
        if (event->type() == QEvent::TouchUpdate || event->type() == QEvent::TouchBegin || event->type() == QEvent::TouchEnd) {
            this->touchEventPrivate(dynamic_cast<QTouchEvent *>(event));
        }
        // other Touch events here...

        return QQuickPaintedItem::event(event);
        return false;
    }

    QQuickItem *targetTouchArea() const {
        return _targetTouchArea;
    }

    void setTargetTouchArea(QQuickItem *targetTouchArea) {
        if (targetTouchArea == _targetTouchArea)
            return;

        if (_targetTouchArea)
            _targetTouchArea->removeEventFilter(this);

        _targetTouchArea = targetTouchArea;

        if (_targetTouchArea)
            _targetTouchArea->installEventFilter(this);

        emit targetTouchAreaChanged();
    }

private:
    void touchEventPrivate(QTouchEvent *event);

private:
    QQuickItem *_targetTouchArea;

signals:
    void targetTouchAreaChanged();
};
