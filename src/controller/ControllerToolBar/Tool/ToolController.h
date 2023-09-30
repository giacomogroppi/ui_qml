#pragma once

#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include "utils/WCommonScript.h"
#include "touch/pen/Pen.h"

class ToolController {
private:
    bool _selected;
public:
    explicit ToolController(bool selected);
    ~ToolController();

    void select();
    void deselect();

    nd auto isSelected() const -> bool;

    virtual int getType() const = 0;
    virtual void callUpdate() = 0;

    static void scale(QPolygonF &pol, double scaleFactor);
    static void scale(QPointF &point, double scaleFactor);
    static void scale(QRectF &rect, double scaleFactor);
};

inline void ToolController::scale(QPolygonF &pol, double scaleFactor)
{
    for(auto &point: pol) {
        ToolController::scale(point, scaleFactor);
    }
}

inline void ToolController::scale(QRectF &rect, double scaleFactor)
{
    QPointF tl, br;
    tl = rect.topLeft();
    br = rect.bottomRight();

    ToolController::scale(tl, scaleFactor);
    ToolController::scale(br, scaleFactor);
    rect = {
        tl, br
    };
}

inline void ToolController::scale(QPointF &pol, double scaleFactor)
{
    pol *= scaleFactor;
}

inline void ToolController::deselect()
{
    qDebug() << "Deselect for " << this->getType();
    this->_selected = false;
    this->callUpdate();
}

inline void ToolController::select()
{
    qDebug() << "Select for " << this->getType();

    this->_selected = true;
    this->callUpdate();
}

