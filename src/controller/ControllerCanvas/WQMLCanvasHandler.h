#pragma once

#include <QObject>
#include <QQuickItem>


class WQMLCanvasHandler: public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(QQuickItem *targetTouchArea READ targetTouchArea WRITE setTargetTouchArea NOTIFY targetTouchAreaChanged)
    Q_PROPERTY(int heightObject READ getHeightObject WRITE setHeightObject);
    Q_PROPERTY(int widthObject READ getWidthObject WRITE setWidthObject);

public:
    WQMLCanvasHandler(QQuickItem *parent = nullptr);

    bool eventFilter(QObject *, QEvent *event) override;

    QQuickItem *targetTouchArea() const;

    void setTargetTouchArea(QQuickItem *targetTouchArea);

    int getHeightObject() const {return this->_h;};
    void setHeightObject(int h) {this->_h = h;};

    int getWidthObject() const {return this->_w;};
    void setWidthObject(int w) {this->_w = w;};

private:
    void touchEventPrivate(QTouchEvent *event);
    int _h, _w;
    bool _waitingForEnd;

private:
    QQuickItem *_targetTouchArea;

signals:
    void targetTouchAreaChanged();

    void touchBegin(const QPointF &point, double pressure);
    void touchUpdate(const QPointF &point, double pressure);
    void touchEnd(const QPointF &point, double pressure);
};


