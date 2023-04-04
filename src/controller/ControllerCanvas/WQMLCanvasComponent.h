#pragma once

#include <QObject>
#include <QQuickPaintedItem>
#include <QTimer>

class WQMLCanvasComponent: public QQuickPaintedItem
{
    Q_OBJECT

public:
    explicit WQMLCanvasComponent(QQuickItem *parent = nullptr);
    void paint(QPainter *painter) override;

    Q_PROPERTY(double xPosition READ xPosition  WRITE setXPosition  NOTIFY onXPositionChanged);
    void setXPosition(double x);
    double xPosition() const;
    Q_SIGNAL void onXPositionChanged();

    Q_PROPERTY(double yPosition READ yPosition  WRITE setYPosition  NOTIFY onYPositionChanged);
    void setYPosition(double y);
    double yPosition() const;
    Q_SIGNAL void onYPositionChanged();

    void setFunc(std::function<const QImage &()> getImg);

public slots:
    void callUpdate();

private:
    int _x, _y;
    std::function<const QImage&()> _getImg;
    bool _functionSet;
};
