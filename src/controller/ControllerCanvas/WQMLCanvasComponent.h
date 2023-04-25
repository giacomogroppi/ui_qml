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
    Q_PROPERTY(double xPosition READ xPosition  WRITE setXPosition  NOTIFY onXPositionChanged);
    Q_PROPERTY(double yPosition READ yPosition  WRITE setYPosition  NOTIFY onYPositionChanged);
    Q_PROPERTY(int index        READ getIndex   WRITE setIndex      NOTIFY onIndexChanged);
public:
    explicit WQMLCanvasComponent(QQuickItem *parent = nullptr);

    void setXPosition(double x);
    double xPosition() const;

    void setYPosition(double y);
    double yPosition() const;

    int getIndex() const;
    void setIndex(int index);

    void setFunc(std::function<void (QPainter &painter, double width)> getImg);

signals:
    void onXPositionChanged();
    void onYPositionChanged();
    void onIndexChanged();

public slots:
    void callUpdate(int page);

    void paint(QPainter *painter) override;

private:
    int _index;
    bool event(QEvent *event) override;
    int _x, _y;
    std::function<void(QPainter &painter, double width)> _getImg;
    bool _functionSet;
};
