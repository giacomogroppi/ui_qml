#include "ControllerCanvas.h"
#include <QPainter>
#include <QImage>
#include <QTimer>
#include <QDebug>
#include "controller/Controller.h"

ControllerCanvas::ControllerCanvas()
    : QQuickImageProvider(QQuickImageProvider::Pixmap),
      _need_refresh(false)
{
    this->_timer = new QTimer(this);
    QObject::connect(_timer, &QTimer::timeout, this, &ControllerCanvas::timerEnd);

    _timer->start(500);
}

QPixmap ControllerCanvas::requestPixmap(const QString &id, QSize *size, const QSize &requestedSize)
{
    const auto img = this->requestImage(id, size, requestedSize);

    return QPixmap::fromImage(img);
}

QImage ControllerCanvas::requestImage(const QString &id, QSize *size, const QSize &requestedSize)
{
    constexpr int h = 10000;
    constexpr int w = 1200;
    QImage img(w, h, QImage::Format_ARGB32);
    QPainter painter(&img);

    if(size)
        *size = QSize(w, h);

    qDebug() << "requestImage";

    painter.setPen(Qt::SolidLine);
    painter.drawLine(10, 10, w, h);

    painter.drawText(QPoint(250, 250), QString::number(this->_value));

    painter.end();

    return img;
}

void ControllerCanvas::timerEnd()
{
    this->_value ++;
    //qDebug() << "value change";
    _timer->start(500);
}
