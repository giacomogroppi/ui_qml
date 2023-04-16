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
WQMLCanvasComponent *drawer = nullptr;

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

    if (drawer)
        drawer->callUpdate();
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
    //qDebug() << "New position X " << newPosition;
    if (newPosition != this->_positionX) {
        _positionX = newPosition;
        emit this->positionXChanged();
        emit this->positionChanged({this->_positionX, this->_positionY});
    }
}

void ControllerCanvas::setPositionY(double newPosition)
{
    W_ASSERT(newPosition >= 0.);
    //qDebug() << "New position Y " << newPosition;
    if (newPosition != this->_positionY) {
        _positionY = newPosition;
        emit this->positionYChanged();
        emit this->positionChanged({this->_positionX, this->_positionY});
    }
}

void ControllerCanvas::registerDrawer(WQMLCanvasComponent *object)
{
    W_ASSERT(drawer == nullptr);
    W_ASSERT(controllerCanvas != nullptr);

    drawer = object;

    QObject::connect(drawer, &WQMLCanvasComponent::onXPositionChanged, []() {
        emit controllerCanvas->positionChanged(QPointF(drawer->xPosition(), 0.));
    });

    QObject::connect(drawer, &WQMLCanvasComponent::onYPositionChanged, []() {
        emit controllerCanvas->positionChanged(QPointF(0., drawer->yPosition()));
    });
    drawer->setFunc(controllerCanvas->_getImg);
}

void ControllerCanvas::refresh()
{
    emit this->widthObjectChanged();
    emit this->heigthObjectChanged();
    drawer->callUpdate();
}

void ControllerCanvas::sizeHasChanged(const QSizeF &size)
{
    qDebug() << size;
    this->_width = size.width();
    this->_heigth = size.height();

    emit this->widthObjectChanged();
    emit this->heigthObjectChanged();
    drawer->callUpdate();
}

void ControllerCanvas::touchBegin(const QPointF &point, double pressure)
{
    W_ASSERT(_status == waitingFor::begin);
    DO_IF_DEBUG(_status = waitingFor::update;);

    emit this->onTouchBegin(point, pressure);
}

void ControllerCanvas::touchUpdate(const QPointF &point, double pressure)
{
    W_ASSERT(_status == waitingFor::update);
    DO_IF_DEBUG(_status = waitingFor::update;);
    emit this->onTouchUpdate(point, pressure);
}

void ControllerCanvas::touchEnd(const QPointF &point, double pressure)
{
    W_ASSERT(_status == waitingFor::update);
    DO_IF_DEBUG(_status = waitingFor::begin;);
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

