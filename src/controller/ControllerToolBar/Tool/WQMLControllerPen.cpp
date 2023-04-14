#include "WQMLControllerPen.h"
#include <QPixmap>
#include "touch/dataTouch/page/Page.h"
#include <QGuiApplication>
#include "controller/ControllerToolBar/ControllerToolBar.h"

WQMLControllerPen::WQMLControllerPen(QQuickItem *parent)
    : QQuickPaintedItem(parent)
    , ToolController(false)
{
}

void WQMLControllerPen::paint(QPainter *painter)
{
    Define_PEN(pen);
    pen.setColor(Qt::black);
    painter->setPen(pen);

    //painter->fillRect(QRect{0, 0, 50, 34}, Qt::white);
    painter->setRenderHint(QPainter::Antialiasing);

    const QPoint bl = {
        14, 20
    };

    const QPoint br = {
        22, 29
    };

    constexpr QPoint tip = {
        11, 32
    };

    const QPolygonF pol1(QList<QPointF>{bl, {30., 3.}, {38., 12.}, br});
    const QPolygonF pol2(QList<QPointF>{bl, tip, br});

    if (this->isSelected()) {
        painter->setBrush(Qt::black);

        painter->drawPolygon(pol1, Qt::FillRule::OddEvenFill);

        const auto color = ControllerToolBar::getColor();

        painter->setBrush(color);
        painter->drawPolygon(pol2);

        pen.setBrush(Qt::NoBrush);
        pen.setWidthF(1.);
        pen.setColor(Qt::white);
        painter->setPen(pen);

        painter->drawPolygon(pol1);
        painter->drawPolygon(pol2);
        painter->drawLine(bl, br);

        painter->drawLine(tip, QPoint {tip.x() + 15, tip.y()});
    } else {
        painter->drawPolygon(pol1);
        painter->drawPolygon(pol2);
    }
}

void WQMLControllerPen::callUpdate()
{
    this->update();
}

int WQMLControllerPen::getType()
{
    return Pen::type();
}
