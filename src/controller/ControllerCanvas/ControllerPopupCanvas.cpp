#include "ControllerPopupCanvas.h"
#include "core/PointF.h"
#include <QPointF>

ControllerPopupCanvas::ControllerPopupCanvas(QObject *parent)
    : QObject{parent}
    , _types(0)
    , _isVisible(false)
{

}

ControllerPopupCanvas::~ControllerPopupCanvas() = default;

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

bool ControllerPopupCanvas::isPasteSelectable() const
{
    return _types & paste;
}

bool ControllerPopupCanvas::isVisible() const
{
    return _isVisible;
}

void ControllerPopupCanvas::copySelectable(bool selectable)
{
    const auto shouldEmit = selectable != !!(_types & copy);

    if (selectable)
        this->_types |= PopupVisibility::copy;
    else
        this->_types &= ~PopupVisibility::copy;

    if (shouldEmit) emit clickableChanged();
}

void ControllerPopupCanvas::deleteSelectable(bool selectable)
{
    const auto shouldEmit = selectable != !!(_types & del);

    if (selectable)
        this->_types |= PopupVisibility::del;
    else
        this->_types &= ~PopupVisibility::del;

    if (shouldEmit) emit clickableChanged();
}

void ControllerPopupCanvas::cutSelectable(bool selectable)
{
    const auto shouldEmit = selectable != !!(_types & cut);

    if (selectable)
        this->_types |= PopupVisibility::cut;
    else
        this->_types &= ~PopupVisibility::cut;

    if (shouldEmit) emit clickableChanged();
}

void ControllerPopupCanvas::pasteSelectable(bool selectable)
{
    const auto shouldEmit = selectable != !!(_types & paste);

    if (selectable)
        this->_types |= PopupVisibility::paste;
    else
        this->_types &= ~PopupVisibility::paste;

    if (shouldEmit) emit clickableChanged();
}

void ControllerPopupCanvas::visibilityChanged(bool isVisible)
{
    if (isVisible != this->_isVisible) {
        this->_isVisible = isVisible;
        emit onVisibilityChanged();
    }
}

void ControllerPopupCanvas::clickCopy()
{
    W_EMIT_0(copyClicked);
}

void ControllerPopupCanvas::clickDelete()
{
    W_EMIT_0(deleteClicked);
}

void ControllerPopupCanvas::clickCut()
{
    W_EMIT_0(cutClicked);
}

void ControllerPopupCanvas::clickPaste()
{
    W_EMIT_0(pasteClicked);
}

void ControllerPopupCanvas::propertyShow(const PointF& point, ActionProperty actionProperty)
{
    // TODO: use the point passed as parameter
    this->copySelectable(!!(actionProperty & ActionProperty::PROPERTY_SHOW_COPY));
    this->deleteSelectable(!!(actionProperty & ActionProperty::PROPERTY_SHOW_DELETE));
    this->cutSelectable(!!(actionProperty & ActionProperty::PROPERTY_SHOW_CUT));
    this->pasteSelectable(!!(actionProperty & ActionProperty::PROPERTY_SHOW_PASTE));

    this->_isVisible = !!actionProperty;

    if (actionProperty)
        emit onVisibilityChanged();
}