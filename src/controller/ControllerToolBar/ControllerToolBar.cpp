#include "ControllerToolBar.h"
#include <QDebug>
#include "core/WMutexLocker.h"
#include "touch/dataTouch/stroke/StrokePre.h"
#include <QThreadPool>
#include <QRunnable>

extern StrokePre *__tmp;

ControllerToolBar::ControllerToolBar(QObject *parent, TabletController *tabletController)
    : QObject(parent)
    , _type(Pen)
    , _color(Qt::black)
    , _tabletController(tabletController)
    , _sem(0)
{
    QObject::connect(this, &ControllerToolBar::colorChanged, [this]() {
        _tabletController->selectColor(this->_color);
    });

    QObject::connect(this->_tabletController, &TabletController::onNeedRefresh, this, &ControllerToolBar::needRefresh, Qt::QueuedConnection);

    /*QThreadPool::globalInstance()->startOnReservedThread(
        [this]() {
            for (;;) {
                this->_sem.acquire();

                this->_mutexListPoints.lock();
                const auto point = this->_points.takeFirst();
                this->_mutexListPoints.unlock();

                _mutexInternalData.lock();
                switch (point.type) {
                case 0: // begin
                    this->_tabletController->touchBegin(point.point, point.pressure);
                    break;
                case 1:
                    this->_tabletController->touchUpdate(point.point, point.pressure);
                    break;
                case 2:
                    this->_tabletController->touchEnd(point.point, point.pressure);
                    break;
                }
                this->_mutexInternalData.unlock();
            }
        }
    );*/
}

ControllerToolBar::~ControllerToolBar()
{
    delete __tmp;
}

void ControllerToolBar::needRefresh ()
{
    emit this->onNeedRefresh();
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

void ControllerToolBar::getImg(QPainter &painter, double width)
{
    /*
    const auto target = QRect (
        0, 0,
        width,
        img.height() * width / img.width()
    );
    */
    this->_tabletController->getImg(painter, width);
    //img.save("/Users/giacomo/Desktop/tmp_foto/prova.png", "PNG");
}

void ControllerToolBar::touchBegin(const QPointF &point, double pressure)
{
    //WMutexLocker _(this->_mutexListPoints);
    //this->_sem.release();
    //this->_points.append(EventStack(point, pressure, 0));
    WDebug(false, "call");
    emit this->onNeedRefresh();
    this->_tabletController->touchBegin(point, pressure);
}

void ControllerToolBar::touchUpdate(const QPointF &point, double pressure)
{
    //WMutexLocker _(this->_mutexListPoints);
    //this->_sem.release();
    //this->_points.append(EventStack(point, pressure, 1));

    emit this->onNeedRefresh();
    WDebug(false, "call");
    this->_tabletController->touchUpdate(point, pressure);
}

void ControllerToolBar::touchEnd(const QPointF &point, double pressure)
{
    //WMutexLocker _(this->_mutexListPoints);
    //this->_sem.release();
    //this->_points.append(EventStack(point, pressure, 2));

    WDebug(false, "call");
    emit this->onNeedRefresh();

    this->_tabletController->touchEnd(point, pressure);
}

void ControllerToolBar::positionChanged(const QPointF &newPosition)
{
    this->_tabletController->positionDocChanged(newPosition);
}
