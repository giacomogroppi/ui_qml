#pragma once

#include <QObject>
#include <QQuickPaintedItem>
#include <QTimer>

class WQMLCanvasComponent: public QQuickPaintedItem
{
    Q_OBJECT
    //QML_ELEMENT

public:
    WQMLCanvasComponent(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) override;
};
