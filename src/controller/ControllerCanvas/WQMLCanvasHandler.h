#pragma once

#include <QObject>
#include <QQuickItem>


class WQMLCanvasHandler: public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem *targetTouchArea READ targetTouchArea WRITE setTargetTouchArea NOTIFY targetTouchAreaChanged)

public:
    WQMLCanvasHandler(QQuickItem *parent = nullptr);

    bool eventFilter(QObject *, QEvent *event) override;

    QQuickItem *targetTouchArea() const;

    void setTargetTouchArea(QQuickItem *targetTouchArea);

private:
    void touchEventPrivate(QTouchEvent *event);

    bool _waitingForEnd;

private:
    QQuickItem *_targetTouchArea;

signals:
    void targetTouchAreaChanged();

};


