#pragma once

#include <QObject>
#include <QQuickPaintedItem>
#include <QTimer>
#include "ToolController.h"

class WQMLControllerHighlighter: public QQuickPaintedItem, public ToolController
{
Q_OBJECT

public:
    explicit WQMLControllerHighlighter(QQuickItem *parent = nullptr);

public slots:
    void callUpdate() final;

    void paint(QPainter *painter) override;
    int getType() const final;
};
