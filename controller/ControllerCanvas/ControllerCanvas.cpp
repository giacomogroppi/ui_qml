#include "ControllerCanvas.h"
#include <QPainter>
#include <QImage>
#include <QTimer>
#include <QDebug>

ControllerCanvas::ControllerCanvas(QObject *parent)
    : QObject(parent)
{
    qmlRegisterType<WQMLCanvasComponent>("WQMLCanvasComponent", 1, 0, "WQMLCanvasComponent");
}
