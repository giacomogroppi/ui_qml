#pragma once

#include <QObject>
#include <QQuickPaintedItem>
#include <QTimer>

// opengl
#include <QQuickPaintedItem>
#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLContext>
#include <QQuickWindow>

class WQMLCanvasComponent: public QQuickPaintedItem
{
    Q_OBJECT

public:
    explicit WQMLCanvasComponent(QQuickItem *parent = nullptr);

    Q_PROPERTY(double xPosition READ xPosition  WRITE setXPosition  NOTIFY onXPositionChanged);
    void setXPosition(double x);
    double xPosition() const;
    Q_SIGNAL void onXPositionChanged();

    Q_PROPERTY(double yPosition READ yPosition  WRITE setYPosition  NOTIFY onYPositionChanged);
    void setYPosition(double y);
    double yPosition() const;
    Q_SIGNAL void onYPositionChanged();

    void setFunc(std::function<void (QPainter &painter, double width)> getImg);

public slots:
    void callUpdate();

    void paint(QPainter *painter) override;

private:
    int _x, _y;
    std::function<void(QPainter &painter, double width)> _getImg;
    bool _functionSet;
};
