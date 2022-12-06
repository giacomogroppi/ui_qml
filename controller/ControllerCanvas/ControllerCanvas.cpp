#include "ControllerCanvas.h"
#include <QPainter>
#include <QImage>
#include <QTimer>
#include <QDebug>

ControllerCanvas::ControllerCanvas(QObject *parent)
    : QObject(parent)
{
    qmlRegisterType<WQMLCanvasComponent>("com.github.giacomogroppi.writernoteqt.WQMLCanvasComponent",
                                         1, 0,
                                         "WCanvasComponent");
}
