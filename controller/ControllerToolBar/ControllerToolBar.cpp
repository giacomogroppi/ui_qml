#include "ControllerToolBar.h"
#include <QDebug>

ControllerToolBar::ControllerToolBar(QObject *parent)
    : QObject(parent),
      _type(Pen),
      _color(Qt::black)
{
}

ControllerToolBar::~ControllerToolBar()
{
}

void ControllerToolBar::clickSelectPen()
{
    _type = Pen;
    emit toolHasChanged();
}

void ControllerToolBar::clickRubber()
{
    _type = Rubber;
    emit toolHasChanged();
}

void ControllerToolBar::clickHand()
{
    _type = Hand;
    emit toolHasChanged();
}

void ControllerToolBar::clickHighlighter()
{
    _type = Highlighter;
    emit toolHasChanged();
}

void ControllerToolBar::clickCut()
{
    _type = Cut;
    emit toolHasChanged();
}

void ControllerToolBar::clickBlack()
{
    _color = Qt::black;
    emit colorChanged();
}

void ControllerToolBar::clickBrown()
{
    _color = brown;
    emit colorChanged();
}

void ControllerToolBar::clickWhite()
{
    _color = Qt::white;
    emit colorChanged();
}

void ControllerToolBar::clickYellow()
{
    _color = Qt::yellow;
    emit colorChanged();
}

void ControllerToolBar::clickRed()
{
    _color = Qt::red;
    emit colorChanged();
}

bool ControllerToolBar::isPen() const
{
    return _type == Pen;
}

bool ControllerToolBar::isRubber() const
{
    return _type == Rubber;
}

bool ControllerToolBar::isHand() const
{
    return _type == Hand;
}

bool ControllerToolBar::isHighlighter() const
{
    return _type == Highlighter;
}

bool ControllerToolBar::isCut() const
{
    return _type == Cut;
}
