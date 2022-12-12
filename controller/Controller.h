#pragma once

#include <QObject>
#include <QQmlApplicationEngine>

#include "ControllerList/ControllerList.h"
#include "ControllerAudio/ControllerAudio.h"
#include "ControllerCanvas/ControllerCanvas.h"
#include "ControllerToolBar/ControllerToolBar.h"
#include "ControllerPageCounter/ControllerPageCounter.h"

class Controller: public QObject {
    Q_OBJECT
private:
    ControllerList          *_listPreview;
    ControllerAudio         *_audio;
    ControllerCanvas        *_canvas;
    ControllerToolBar       *_toolBar;
    ControllerPageCounter   *_pageCounter;

    QQmlContext *_content;
    QQmlApplicationEngine *_engine;

    void registerType();

public:
    explicit Controller(QObject *parent, QQmlContext* content, QQmlApplicationEngine* engine);
    ~Controller();
};
