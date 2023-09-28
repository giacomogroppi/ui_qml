#include "ControllerToolBar.h"
#include <QDebug>
#include "core/WMutexLocker.h"
#include "touch/dataTouch/stroke/StrokePre.h"
#include <QThreadPool>
#include "Tool/WQMLControllerHighlighter.h"
#include "Tool/WQMLControllerPen.h"
#include <QRunnable>
#include "Tool/WQMLControllerRubber.h"

extern StrokePre *__tmp;

static ControllerToolBar *controllerToolBar = nullptr;
static QList<ToolController *> tools;

ControllerToolBar::ControllerToolBar(QObject *parent, TabletController *tabletController)
    : QObject(parent)
    , _color(Qt::black)
    , _tabletController(tabletController)
{
    controllerToolBar = this;

    QObject::connect(this, &ControllerToolBar::colorChanged, [this]() {
        _tabletController->selectColor(WColor(this->_color));
    });

    w_connect_lambda(_tabletController, onNeedRefresh, [this](const UpdateEvent& event) {
        emit this->onNeedRefresh(event);
    });

    w_connect_listener(_tabletController, onNumberOfPageChanged, this, numberOfPageChanged);

    qmlRegisterType<WQMLControllerHighlighter>( "writernote.WQMLControllerHighlighter", 1, 0, "WHighlighterButton");
    qmlRegisterType<WQMLControllerPen>(         "writernote.WQMLControllerPen",         1, 0, "WPenButton");
    qmlRegisterType<WQMLControllerRubber>(      "writernote.WQMLControllerRubber",      1, 0, "WRubberButton");

    this->_tabletController->selectType(Pen::type());

    QTimer::singleShot(50, []() {
        for (auto *t : tools) {
            continue;
            t->callUpdate();

            if (t->getType() == controllerToolBar->_tabletController->getCurrentTool()->getType()) {
                t->select();
            } else {
                t->deselect();
            }
        }
    });
}

void ControllerToolBar::selectTool(int tool)
{
    if (tool != this->_tabletController->getCurrentTool()->getType()) {
        this->_tabletController->selectType(tool);

        this->updateGui();

        emit toolHasChanged();
    }
}

ControllerToolBar::~ControllerToolBar()
{
    delete __tmp;
}

void ControllerToolBar::numberOfPageChanged(int n)
{
    const auto w = Page::getWidth();
    const auto h = Page::getHeight() * n;
    emit onDocSizeChanged(QSizeF(w, h));
}

void ControllerToolBar::clickSelectPen()
{
    this->selectTool(Pen::type());
}

void ControllerToolBar::clickRubber()
{
    this->selectTool(Rubber::type());
}

void ControllerToolBar::clickHand()
{
    //this->selectTool(Hand::type());
    W_ASSERT_TEXT(false, "to_do");
}

void ControllerToolBar::clickHighlighter()
{
    this->selectTool(Highlighter::type());
}

void ControllerToolBar::clickCut()
{
    this->selectTool(Square::type());
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
    return this->_tabletController->getCurrentTool()->getType() == Pen::type();
}

bool ControllerToolBar::isRubber() const
{
    return this->_tabletController->getCurrentTool()->getType() == Rubber::type();
}

bool ControllerToolBar::isHand() const
{
    return this->_tabletController->getCurrentTool()->getType() == Square::type();
}

bool ControllerToolBar::isHighlighter() const
{
    return this->_tabletController->getCurrentTool()->getType() == Highlighter::type();
}

bool ControllerToolBar::isCut() const
{
    return this->_tabletController->getCurrentTool()->getType() == Square::type();
}

void ControllerToolBar::getImg(QPainter &painter, double width, WFlags<UpdateEvent::UpdateEventType> flags)
{
    WPainter adapterPainter (&painter);
    this->_tabletController->getImg(adapterPainter, width, flags);
    //this->_tabletController->getImg(adapterPainter, width);
}

void ControllerToolBar::registerTool(ToolController *tool)
{
    tools.append(tool);
    QTimer::singleShot(0, controllerToolBar, &ControllerToolBar::updateGui);
}

void ControllerToolBar::updateGui()
{
    const auto current = this->_tabletController->getCurrentTool()->getType();
    for (auto *t: tools) {
        if (t->getType() == current) {
            t->select();
        } else {
            t->deselect();
        }
        t->callUpdate();
    }
}

QColor ControllerToolBar::getColor()
{
    return controllerToolBar->_color;
}

void ControllerToolBar::touchBegin(const QPointF &point, double pressure)
{
    WDebug(false, "call");
    // in teoria tabletController chiama già l'evento di update quindi possiamo non chiamarlo
    //emit this->onNeedRefreshPage(0, 1);
    this->_tabletController->touchBegin({point.x(), point.y()}, pressure);
}

void ControllerToolBar::touchUpdate(const QPointF &point, double pressure)
{
    WDebug(false, "call");

    this->_tabletController->touchUpdate({point.x(), point.y()}, pressure);
    //emit this->onNeedRefreshPage(0, 1);
}

void ControllerToolBar::touchEnd(const QPointF &point, double pressure)
{
    WDebug(false, "call");
    //emit this->onNeedRefreshPage(0, 1);
    this->_tabletController->touchEnd({point.x(), point.y()}, pressure);
}

void ControllerToolBar::positionChanged(const QPointF &newPosition)
{
    this->_tabletController->positionDocChanged({newPosition.x(), newPosition.y()});
}
