#pragma once

#include <QObject>
#include <QQmlApplicationEngine>

#include "controllerList/controllerList.h"
#include "ControllerAudio/ControllerAudio.h"
#include "ControllerCanvas/ControllerCanvas.h"

class Controller: public QObject {
    Q_OBJECT
private:
    controllerList *_listPreview;
    ControllerAudio *_audio;
    ControllerCanvas *_canvas;

    QQmlContext *_content;
    QQmlApplicationEngine *_engine;

    void registerType();

    QObject *_instance;

public:
    explicit Controller(QObject *parent, QQmlContext* content, QQmlApplicationEngine* engine, QObject *instance);
    ~Controller();

    QObject *instance();
};
