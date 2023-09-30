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

auto ToolController::isSelected() const -> bool
{
    return this->_selected;
}
