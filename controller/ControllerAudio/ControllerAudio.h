#pragma once

#include <QObject>

class ControllerAudio: public QObject {
    Q_OBJECT
public:
    Q_INVOKABLE explicit ControllerAudio(QObject *parent);
    ~ControllerAudio();
};
