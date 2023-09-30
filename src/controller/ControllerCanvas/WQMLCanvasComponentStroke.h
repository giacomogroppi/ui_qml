#pragma once

#include <QObject>
#include <QQuickPaintedItem>
#include <QTimer>

#include <QQuickPaintedItem>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLContext>
#include <QQuickWindow>

#include "core/WFlags.h"
#include "touch/UpdateEvent.h"

class WQMLCanvasComponentStroke: public QQuickPaintedItem
{
    Q_OBJECT
    Q_PROPERTY(double xPosition READ xPosition  WRITE setXPosition  NOTIFY onXPositionChanged);
    Q_PROPERTY(double yPosition READ yPosition  WRITE setYPosition  NOTIFY onYPositionChanged);
public:
    explicit WQMLCanvasComponentStroke(QQuickItem *parent = nullptr);
    ~WQMLCanvasComponentStroke() override;

    void setXPosition(double x);
    double xPosition() const;

    void setYPosition(double y);
    double yPosition() const;

    void setFunc(std::function<void (QPainter &painter, double width, WFlags<UpdateEvent::UpdateEventType>)> getImg);

signals:
    void onXPositionChanged();
    void onYPositionChanged();
    void onIndexChanged();

public slots:
    void callUpdate();

    void paint(QPainter *painter) override;

private:
    int _index;
    bool event(QEvent *event) override;
    int _x, _y;
    std::function<void(QPainter &painter, double width, WFlags<UpdateEvent::UpdateEventType> type)> _getImg;
    bool _functionSet;
};
