#include "Tool.h"

Tool::Tool()
{

}

bool Tool::isPen() const
{
    return _type == Pen;
}

bool Tool::isRubber() const
{
    return _type == Rubber;
}

bool Tool::isHighlighter() const
{
    return _type == Highlighter;
}

bool Tool::isHand() const
{
    return _type == Hand;
}

void Tool::setPen()
{
    _type = Pen;
}

void Tool::setRubber()
{
    _type = Rubber;
}

void Tool::setHand()
{
    _type = Hand;
}

void Tool::setHighlighter()
{

}
