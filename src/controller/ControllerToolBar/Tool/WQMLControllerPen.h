#pragma once

#include <QObject>
#include <QQuickPaintedItem>
#include <QTimer>
#include "ToolController.h"
#include <QPixmap>

class WQMLControllerPen: public QQuickPaintedItem, public ToolController
{
Q_OBJECT

public:
    explicit WQMLControllerPen(QQuickItem *parent = nullptr);

public slots:
    void callUpdate() final;
    virtual int getType() final;
    void paint(QPainter *painter) override;
};
