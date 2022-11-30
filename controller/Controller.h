#pragma once

#include <QObject>

#include "controllerList/controllerList.h"
#include "ControllerAudio/ControllerAudio.h"

class Controller: public QObject {
    Q_OBJECT
private:
    controllerList *_listPreview;
    ControllerAudio *_audio;
    QQmlContext *_content;

    void registerType();

public:
    explicit Controller(QObject *parent, QQmlContext* content);
    ~Controller();

};
