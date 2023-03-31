#include "ControllerToolBar.h"
#include <QDebug>

ControllerToolBar::ControllerToolBar(QObject *parent, TabletController *tabletController)
    : QObject(parent)
    ,  _type(Pen)
    ,  _color(Qt::black)
    , _tabletController(tabletController)
{
    QObject::connect(this, &ControllerToolBar::colorChanged, [this]() {
        _tabletController->selectColor(this->_color);
    }) ;
}

ControllerToolBar::~ControllerToolBar()
{
}

void ControllerToolBar::clickSelectPen()
{
    _type = Pen;
    this->_tabletController->selectPen();
    emit toolHasChanged();
}

void ControllerToolBar::clickRubber()
{
    _type = Rubber;
    this->_tabletController->selectRubber();
    emit toolHasChanged();
}

void ControllerToolBar::clickHand()
{
    _type = Hand;
    W_ASSERT_TEXT(false, "to_do");
    emit toolHasChanged();
}

void ControllerToolBar::clickHighlighter()
{
    _type = Highlighter;
    this->_tabletController->selectHighligter();
    emit toolHasChanged();
}

void ControllerToolBar::clickCut()
{
    _type = Cut;
    this->_tabletController->selectSquare();
    emit toolHasChanged();
}

void ControllerToolBar::clickBlack()
{
    _color = Qt::black;
    this->_tabletController->selectColor(_color);
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

void ControllerToolBar::touchBegin(const QPointF &point, double pressure)
{
    this->_tabletController->touchBegin(point, pressure);
}

void ControllerToolBar::touchUpdate(const QPointF &point, double pressure)
{
    this->_tabletController->touchUpdate(point, pressure);
}

void ControllerToolBar::touchEnd(const QPointF &point, double pressure)
{
    this->_tabletController->touchEnd(point, pressure);
}
