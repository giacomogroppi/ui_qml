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
      _width(1000)
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
