#include "ControllerCanvas.h"
#include <QPainter>
#include <QImage>
#include <QTimer>
#include <QDebug>
#include "controller/Controller.h"

ControllerCanvas::ControllerCanvas(QObject *parent)
    : QObject(parent),
      _timer(new QTimer(this)),
      _heigth(1000),
      _width(1000),
      _status(waitingFor::begin)
{
    qmlRegisterType<WQMLCanvasComponent>("writernote.WQMLCanvasComponent",
                                         1, 0,
                                         "WCanvasComponent");
    QObject::connect(_timer, &QTimer::timeout, this, &ControllerCanvas::endTimer);
    //_timer->start(500);
}

void ControllerCanvas::endTimer()
{
    this->wSetHeigth(this->heigthObject() + 100);
    _timer->start(1000);
    qDebug() << "ControllerCanvas::endTimer" << this->heigthObject();
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

int ControllerCanvas::heigthObject()
{
    return this->_heigth;
}

int ControllerCanvas::widthObject() const
{
    return this->_width;
}

void ControllerCanvas::refresh()
{
    emit this->widthObjectChanged();
    emit this->heigthObjectChanged();
}

void ControllerCanvas::touchBegin(double x, double y, double pressure)
{
    Q_ASSERT(_status == waitingFor::end);
    _status = waitingFor::begin;
    emit this->onTouchBegin(QPointF(x, y), pressure);
}

void ControllerCanvas::touchUpdate(double x, double y, double pressure)
{
    Q_ASSERT(_status == waitingFor::begin || _status == waitingFor::update);
    _status = waitingFor::update;
    emit this->onTouchUpdate(QPointF(x, y), pressure);
}

void ControllerCanvas::touchEnd(double x, double y, double pressure)
{
    Q_ASSERT(_status == waitingFor::begin || _status == waitingFor::update);
    _status = waitingFor::end;
    emit this->onTouchEnd(QPointF(x, y), pressure);
}
