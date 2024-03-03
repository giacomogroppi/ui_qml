#include "ControllerPopupCanvas.h"

ControllerPopupCanvas::ControllerPopupCanvas(QObject *parent)
    : QObject{parent}
    , _types(0)
{

}

bool ControllerPopupCanvas::isCopySelectable() const
{
    return _types & copy;
}

bool ControllerPopupCanvas::isCutSelectable() const
{
    return _types & cut;
}

bool ControllerPopupCanvas::isDeleteSelectable() const
{
    return _types & del;
}
