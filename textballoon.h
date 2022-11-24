#pragma once

#include <QObject>
#include <QQuickPaintedItem>

class TextBalloon : public QQuickPaintedItem
{
    Q_OBJECT
        Q_PROPERTY(bool rightAligned READ isRightAligned WRITE setRightAligned NOTIFY rightAlignedChanged)
        QML_ELEMENT
public:
    TextBalloon(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) override;

    bool isRightAligned() const;
    void setRightAligned(bool rightAligned)
    {
        rightAligned = rightAligned;
    };

private:
    bool rightAligned;

signals:
    void rightAlignedChanged();
};
