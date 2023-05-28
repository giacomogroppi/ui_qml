#include "WQMLControllerRubber.h"
#include <QPainter>
#include <QBrush>
#include "core/WPixmap.h"
#include "core/core.h"
#include <QRunnable>
#include <functional>
#include <QQuickWindow>
#include "controller/ControllerToolBar/ControllerToolBar.h"
#include "touch/rubber/Rubber.h"

WQMLControllerRubber::WQMLControllerRubber(QQuickItem *parent)
        : QQuickPaintedItem(parent)
        , ToolController(false)
{
    this->setAntialiasing(true);
}

void WQMLControllerRubber::paint(QPainter *painter)
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

    QPolygonF pol1(QList<QPointF>{bl, {30., 5.}, {38., 14.}, br});

    ToolController::scale(pol1, .8);
    ToolController::scale(bl, .8);
    ToolController::scale(br, .8);

    QRectF rect {
        bl - QPointF(1.5, 1.5),
        br + QPointF(1.5, 1.5)
    };

    int startAngle = -40 * 16;
    int spanAngle = -180 * 16;

    if (this->isSelected()) {
        painter->setBrush(Qt::black);

        painter->drawPolygon(pol1, Qt::FillRule::OddEvenFill);

        const auto color = ControllerToolBar::getColor();

        painter->setBrush(color);

        pen.setBrush(Qt::NoBrush);
        pen.setWidthF(1.2);
        pen.setColor(Qt::white);
        painter->setPen(pen);

        painter->drawPolygon(pol1);
        painter->drawLine(bl, br);

        painter->setBrush(Qt::white);
        painter->drawArc(rect, startAngle, spanAngle);
    } else {
        painter->drawPolygon(pol1);

        painter->drawArc(rect, startAngle, spanAngle);
    }
}

void WQMLControllerRubber::callUpdate()
{
    this->update();
}

int WQMLControllerRubber::getType() const
{
    return Rubber::type();
}
