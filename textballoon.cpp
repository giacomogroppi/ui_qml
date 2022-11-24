#include "textballoon.h"
#include <QPainter>
#include <QBrush>

TextBalloon::TextBalloon(QQuickItem *parent)
    : QQuickPaintedItem(parent),
      rightAligned(false)
{
    this->update();
}

void TextBalloon::paint(QPainter *painter)
{
    QPen _pen(QColor(127, 127, 127, 255));

    painter->setPen(_pen);
    painter->setRenderHint(QPainter::Antialiasing);

    painter->drawRect(0, 0, width(), height());
}

bool TextBalloon::isRightAligned() const
{
    return this->rightAligned;
}
