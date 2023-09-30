#include "ToolController.h"
#include "controller/ControllerToolBar/ControllerToolBar.h"

ToolController::ToolController(bool selected)
    : _selected(selected)
{
    ControllerToolBar::registerTool(this);
}

ToolController::~ToolController()
{
    ControllerToolBar::unregisterTool(this);
}

bool ToolController::isSelected() const
{
    return this->_selected;
}
