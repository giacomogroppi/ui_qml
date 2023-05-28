#include "WQMLControllerHighlighter.h"
#include <QPainter>
#include <QBrush>
#include "core/WPixmap.h"
#include "core/core.h"
#include <QRunnable>
#include <functional>
#include <QQuickWindow>
#include "controller/ControllerToolBar/ControllerToolBar.h"

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
    QPen pen;
    pen.setColor(Qt::black);
    painter->setPen(pen);

    //painter->fillRect(QRect{0, 0, 50, 34}, Qt::white);
    painter->setRenderHint(QPainter::Antialiasing);

    QPointF bl = {
            14., 22.
    };

    QPointF br = {
            22., 31.
    };

    QPointF tip = {
            11., 34.
    };

    QPolygonF pol1(QList<QPointF>{bl, {30., 5.}, {38., 14.}, br});
    QPolygonF pol2(QList<QPointF>{bl, tip, br});

    ToolController::scale(pol1, .8);
    ToolController::scale(pol2, .8);
    ToolController::scale(bl, .8);
    ToolController::scale(br, .8);
    ToolController::scale(tip, .8);

    if (this->isSelected()) {
        painter->setBrush(Qt::black);

        painter->drawPolygon(pol1, Qt::FillRule::OddEvenFill);

        const auto color = ControllerToolBar::getColor();

        painter->setBrush(color);
        painter->drawPolygon(pol2);

        pen.setBrush(Qt::NoBrush);
        pen.setWidthF(1.2);
        pen.setColor(Qt::white);
        painter->setPen(pen);

        painter->drawPolygon(pol1);
        painter->drawPolygon(pol2);
        painter->drawLine(bl, br);

        painter->drawLine(tip, QPointF {tip.x() + 15, tip.y()});
    } else {
        painter->drawPolygon(pol1);
        painter->drawPolygon(pol2);
    }
}

void WQMLControllerHighlighter::callUpdate()
{
    this->update();
}

int WQMLControllerHighlighter::getType() const
{
    return Highligter::type();
}
