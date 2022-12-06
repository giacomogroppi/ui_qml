#pragma once

#include <QObject>
#include <QQuickImageProvider>
#include <QTimer>

#include "WQMLCanvasComponent.h"

class ControllerCanvas: public QObject {
    Q_OBJECT
private:
    WQMLCanvasComponent *_component;
public:
    ControllerCanvas(QObject *parent);
    ~ControllerCanvas() = default;
};
