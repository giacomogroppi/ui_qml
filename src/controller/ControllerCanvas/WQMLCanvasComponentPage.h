#pragma once

#include <QObject>
#include <QQuickPaintedItem>

#include "touch/UpdateEvent.h"
#include "Scheduler/WObject.h"

class WQMLCanvasComponentPage: public QQuickPaintedItem, public WObject
{
    Q_OBJECT
    Q_PROPERTY(double xPosition READ xPosition  WRITE setXPosition  NOTIFY onXPositionChanged);
    Q_PROPERTY(double yPosition READ yPosition  WRITE setYPosition  NOTIFY onYPositionChanged);
    Q_PROPERTY(int indexDrawer  READ getIndex   WRITE setIndex      NOTIFY onIndexChanged);
public:
    explicit WQMLCanvasComponentPage(QQuickItem *parent = nullptr);

    void setXPosition(double x);
    double xPosition() const;

    void setYPosition(double y);
    double yPosition() const;

    int getIndex() const;
    void setIndex(int index);

    void setFunc(std::function<void (QPainter &, double, WFlags<UpdateEvent::UpdateEventType>)> getImg);

signals:
    void onXPositionChanged();
    void onYPositionChanged();
    void onIndexChanged();

public slots:
    void callUpdate(int page);

    void paint(QPainter *painter) override;

    W_EMITTABLE_0(FinishDraw);

private:
    int _index;
    bool event(QEvent *event) override;
    int _x, _y;
    std::function<void(QPainter &painter, double width, WFlags<UpdateEvent::UpdateEventType> updateFlag)> _getImg;
    bool _functionSet;
};


