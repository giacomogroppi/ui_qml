#pragma once

#include <QObject>
#include <QQmlApplicationEngine>

#include "ControllerList/ControllerList.h"
#include "ControllerAudio/ControllerAudio.h"
#include "ControllerCanvas/ControllerCanvas.h"


class Controller: public QObject {
    Q_OBJECT
private:
    ControllerList *_listPreview;
    ControllerAudio *_audio;
    ControllerCanvas *_canvas;

    QQmlContext *_content;
    QQmlApplicationEngine *_engine;

    void registerType();

public:
    explicit Controller(QObject *parent, QQmlContext* content, QQmlApplicationEngine* engine);
    ~Controller();
};
