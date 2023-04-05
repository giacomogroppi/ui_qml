#include "ControllerToolBar.h"
#include <QDebug>
#include "touch/dataTouch/stroke/StrokePre.h"

extern StrokePre *__tmp;

ControllerToolBar::ControllerToolBar(QObject *parent, TabletController *tabletController)
    : QObject(parent)
    , _type(Pen)
    , _color(Qt::black)
    , _tabletController(tabletController)
{
    QObject::connect(this, &ControllerToolBar::colorChanged, [this]() {
        _tabletController->selectColor(this->_color);
    });

    QObject::connect(this->_tabletController, &TabletController::onNeedRefresh, [this] () {
        emit onNeedRefresh();
    });
}

ControllerToolBar::~ControllerToolBar()
{
    delete __tmp;
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

const QPixmap &ControllerToolBar::getImg()
{
    return this->_tabletController->getImg();
}

void ControllerToolBar::touchBegin(const QPointF &point, double pressure)
{
    //this->points.append(EventStack(point, pressure, 0));
    this->_tabletController->touchBegin(point, pressure);
}

void ControllerToolBar::touchUpdate(const QPointF &point, double pressure)
{
    //this->points.append(EventStack(point, pressure, 1));
    this->_tabletController->touchUpdate(point, pressure);
}

void ControllerToolBar::touchEnd(const QPointF &point, double pressure)
{
    //this->points.append(EventStack(point, pressure, 2));
    this->_tabletController->touchEnd(point, pressure);
}

void ControllerToolBar::positionChanged(const QPointF &newPosition)
{
    this->_tabletController->positionDocChanged(newPosition);
}

/*
void ControllerToolBar::endDraw()
{
    if (points.isEmpty())
        return;
    const auto &first = this->points.at(0);
    points.removeFirst();
    switch (first.type) {
    case 0:
        //_tabletController->touchBegin(first.point, first.pressure);
        break;
    case 1:
        _tabletController->touchUpdate(first.point, first.pressure);
        break;
    case 2:
        _tabletController->touchEnd(first.point, first.pressure);
    };
}
*/
