#include "textballoon.h"
#include <QPainter>
#include <QBrush>

TextBalloon *_instanceText;

TextBalloon::TextBalloon(QQuickItem *parent)
    : QQuickPaintedItem(parent),
      rightAligned(false),
      _timer(new QTimer(this)),
      _width(500),
      _heigth(500),
      _need_refresh(true)
{
    this->update();
    QObject::connect(_timer, &QTimer::timeout, this, &TextBalloon::endTimer);
    _timer->start(500);

    _instanceText = this;
    qDebug() << "TextBalloon constructor call";
}

void TextBalloon::paint(QPainter *painter)
{
    QPen _pen(QColor(127, 127, 127, 255));

    qDebug() << "paint";

    painter->setPen(_pen);
    painter->setRenderHint(QPainter::Antialiasing);

    painter->drawLine(0, 0, width(), height());
    painter->drawRect(0, 0, width(), height());
}

bool TextBalloon::isRightAligned() const
{
    return this->rightAligned;
}

int TextBalloon::heigthObject()
{
    qDebug() << "heigth" << this->_heigth;
    return this->_heigth;
}

int TextBalloon::widthObject() const
{
    qDebug() << "width" << this->_width;
    return this->_width;
}

bool TextBalloon::needRefresh() const
{
    qDebug() << "needRefresh" << this->_need_refresh;
    return this->_need_refresh;
}

void TextBalloon::setNeedRefresh()
{
    qDebug() << "setNeedRefresh";
    this->_need_refresh = true;
    emit needRefreshChanged();
}

void TextBalloon::endTimer()
{
    qDebug() << "Timer end" << _width;
    _width += 1000;
    _heigth += 1000;
    _timer->start(500);
    emit widthObjectChanged();
}
