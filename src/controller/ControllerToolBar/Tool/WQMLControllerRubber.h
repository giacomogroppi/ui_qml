#pragma once

#include <QObject>
#include <QQuickPaintedItem>
#include <QTimer>
#include "ToolController.h"

class WQMLControllerRubber: public QQuickPaintedItem, public ToolController
{
Q_OBJECT

public:
    explicit WQMLControllerRubber(QQuickItem *parent = nullptr);

public slots:
    void callUpdate() final;

    void paint(QPainter *painter) override;
    int getType() const final;
};
