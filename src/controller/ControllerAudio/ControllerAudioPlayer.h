#pragma once

#include <QObject>
#include "Scheduler/Scheduler.h"
#include "core/WElement.h"

class ControllerAudioPlayer : public QObject
{
    Q_OBJECT
public:
    explicit ControllerAudioPlayer(QObject *parent);

    int getPositionInSeconds() const;

    bool isPlaying() const;


    DEFINE_LISTENER_1(audioPositionChanged, Unsigned, time);
};
