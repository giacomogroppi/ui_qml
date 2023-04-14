#include "WQMLControllerHighlighter.h"
#include <QPainter>
#include <QBrush>
#include "core/WPixmap.h"
#include "core/core.h"
#include <QRunnable>
#include <functional>
#include <QQuickWindow>

WQMLControllerHighlighter::WQMLControllerHighlighter(QQuickItem *parent)
        : QQuickPaintedItem(parent)
        , ToolController(false)
{
    qDebug() << "WQMLCanvasComponent constructor call";
    //WQMLControllerHighlighter::registerDrawer(this);
    this->setAntialiasing(true);
}

void WQMLControllerHighlighter::paint(QPainter *painter)
{
    const auto w = this->width();
    const auto h = this->height();
}

void WQMLControllerHighlighter::callUpdate()
{
    this->update();
}
