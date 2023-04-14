#pragma once

#include <QPainter>
#include <QPixmap>
#include "utils/WCommonScript.h"
#include "touch/pen/Pen.h"

class ToolController {
private:
    bool _selected;
public:
    explicit ToolController(bool selected);

    void select();
    void deselect();

    bool  isSelected() const;

    virtual int getType() = 0;
    virtual void callUpdate() = 0;
};

inline void ToolController::deselect()
{
    this->_selected = false;
    this->callUpdate();
}

inline void ToolController::select()
{
    this->_selected = true;
    this->callUpdate();
}

