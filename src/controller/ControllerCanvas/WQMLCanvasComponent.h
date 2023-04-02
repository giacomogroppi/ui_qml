#pragma once

#include <QObject>
#include <QQuickPaintedItem>
#include <QTimer>

class WQMLCanvasComponent: public QQuickPaintedItem
{
    Q_OBJECT

public:
    explicit WQMLCanvasComponent(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) override;
};
