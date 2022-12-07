#pragma once

#include <QObject>
#include <QQuickImageProvider>
#include <QTimer>

#include "WQMLCanvasComponent.h"

class ControllerCanvas: public QObject {
    Q_OBJECT
private:
    WQMLCanvasComponent *_component;
    QTimer *_timer;

    int _width;
    int _heigth;

    void wSetWidth(int newWidth);
    void wSetHeigth(int newHeigth);

public:
    ControllerCanvas(QObject *parent);
    ~ControllerCanvas() = default;

    Q_PROPERTY(int heigthObject READ heigthObject NOTIFY heigthObjectChanged);
    int heigthObject();
    Q_SIGNAL void heigthObjectChanged();

    Q_PROPERTY(int widthObject READ widthObject NOTIFY widthObjectChanged);
    int widthObject() const;
    Q_SIGNAL void widthObjectChanged();

public slots:
    void refresh();

private slots:
    void endTimer();
};
