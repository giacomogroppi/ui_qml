#include "ControllerCanvas.h"
#include <QPainter>
#include <QImage>
#include <QTimer>
#include <QDebug>
#include "WQMLCanvasHandler.h"
#include "utils/WCommonScript.h"
#include "touch/dataTouch/page/Page.h"

WQMLCanvasHandler *handler = nullptr;
ControllerCanvas *controllerCanvas = nullptr;
static QList<WQMLCanvasComponent *> drawer;

ControllerCanvas::ControllerCanvas(QObject *parent, std::function<void (QPainter &painter, double width)> getImg)
    : QObject(parent)
    , _timer(new QTimer(nullptr))
    , _heigth(Page::getHeight())
    , _width(Page::getWidth())
    , _getImg(std::move(getImg))
    , _positionX(0.)
    , _positionY(0.)
#ifdef DEBUGINFO
    , _status(waitingFor::begin)
#endif
{
    qmlRegisterType<WQMLCanvasComponent>("writernote.WQMLCanvasComponent",
                                         1, 0,
                                        "WCanvasComponent");
    qmlRegisterType<WQMLCanvasHandler>("writernote.WQMLCanvasHandler",
                                       1, 0,
                                        "WCanvasHandler");
    QObject::connect(_timer, &QTimer::timeout, this, &ControllerCanvas::endTimer);
    controllerCanvas = this;
    //_timer->start(500);
}

void ControllerCanvas::endTimer()
{
    //this->wSetHeigth(this->heigthObject() + 100);
    //_timer->start(1);
    qDebug() << "ControllerCanvas::endTimer" << this->heigthObject();

    for (int i = 0; i < drawer.size(); i++) {
        drawer[i]->callUpdate(i);
    }
}

bool ControllerCanvas::event(QEvent *event)
{
    //qDebug() << event->type();
    return QObject::event(event);
}

void ControllerCanvas::wSetWidth(int newWidth)
{
    this->_width = newWidth;
    emit widthObjectChanged();
}

void ControllerCanvas::wSetHeigth(int newHeigth)
{
    this->_heigth = newHeigth;
    emit heigthObjectChanged();
}

int ControllerCanvas::heigthObject() const
{
    return this->_heigth;
}

int ControllerCanvas::widthObject() const
{
    return this->_width;
}

double ControllerCanvas::positionX() const
{
    return this->_positionX;
}

double ControllerCanvas::positionY() const
{
    return this->_positionY;
}

void ControllerCanvas::setPositionX(double newPosition)
{
    W_ASSERT(newPosition >= 0.);

    if (newPosition != this->_positionX) {
        _positionX = newPosition;
        WDebug(true, "Call");
        emit this->positionXChanged();
        emit this->positionChanged({this->_positionX, this->_positionY});
    }
}

void ControllerCanvas::setPositionY(double newPosition)
{
    W_ASSERT(newPosition >= 0.);

    if (newPosition != this->_positionY) {
        _positionY = newPosition;
        WDebug(true, "call");
        emit this->positionYChanged();
        emit this->positionChanged({this->_positionX, this->_positionY});
    }
}

void ControllerCanvas::registerDrawer(WQMLCanvasComponent *object)
{
    W_ASSERT(object != nullptr);
    W_ASSERT(controllerCanvas != nullptr);

    drawer.append(object);

    QObject::connect(object, &WQMLCanvasComponent::onXPositionChanged, [object]() {
        emit controllerCanvas->positionChanged(QPointF(object->xPosition(), 0.));
    });

    QObject::connect(object, &WQMLCanvasComponent::onYPositionChanged, [object]() {
        emit controllerCanvas->positionChanged(QPointF(0., object->yPosition()));
    });
    object->setFunc(controllerCanvas->_getImg);
}

void ControllerCanvas::callUpdate(int page)
{
    W_ASSERT(page == -1 || (page >= 0 && page < drawer.size()));
    drawer[page]->callUpdate(page);
}

void ControllerCanvas::callUpdate(int pageMin, int pageMax, bool all)
{
#if defined(DEBUGINFO)
    if (!all) {
        W_ASSERT(pageMin < pageMax);
        W_ASSERT(pageMin >= 0 && pageMin <  drawer.size());
        W_ASSERT(pageMax >= 1 && pageMax <= drawer.size());
    }
#endif

    if (all) {
        ControllerCanvas::callUpdate(-1);
    } else {
        for (int i = pageMin; i < pageMax; i++) {
            ControllerCanvas::callUpdate(i);
        }
    }
}

void ControllerCanvas::refresh(int page)
{
    //emit this->widthObjectChanged();
    //emit this->heigthObjectChanged();
    ControllerCanvas::callUpdate(page);
}

void ControllerCanvas::sizeHasChanged(const QSizeF &size)
{
    qDebug() << size;

    this->_width = size.width();
    this->_heigth = size.height();

    WDebug(true, "Call");

    emit this->widthObjectChanged();
    emit this->heigthObjectChanged();

    ControllerCanvas::callUpdate(0, 0, true);
}

void ControllerCanvas::touchBegin(const QPointF &point, double pressure)
{
    W_ASSERT(_status == waitingFor::begin);
    DO_IF_DEBUG(_status = waitingFor::update);

    emit this->onTouchBegin(point, pressure);
}

void ControllerCanvas::touchUpdate(const QPointF &point, double pressure)
{
    W_ASSERT(_status == waitingFor::update);
    DO_IF_DEBUG(_status = waitingFor::update);
    emit this->onTouchUpdate(point, pressure);
}

void ControllerCanvas::touchEnd(const QPointF &point, double pressure)
{
    W_ASSERT(_status == waitingFor::update);
    DO_IF_DEBUG(_status = waitingFor::begin);
    emit this->onTouchEnd(point, pressure);
}

void ControllerCanvas::registerHangler(WQMLCanvasHandler *object)
{
    W_ASSERT(controllerCanvas != nullptr);
    W_ASSERT(handler == nullptr);
    handler = object;
    QObject::connect(handler, &WQMLCanvasHandler::touchBegin,   controllerCanvas, &ControllerCanvas::touchBegin);
    QObject::connect(handler, &WQMLCanvasHandler::touchUpdate,  controllerCanvas, &ControllerCanvas::touchUpdate);
    QObject::connect(handler, &WQMLCanvasHandler::touchEnd,     controllerCanvas, &ControllerCanvas::touchEnd);
}

