#pragma once

#include <QObject>

class ControllerAudioPlayer : public QObject
{
    Q_OBJECT
public:
    explicit ControllerAudioPlayer(QObject *parent);

    int getPositionInSeconds() const;

    bool isPlaying() const;
signals:

};
