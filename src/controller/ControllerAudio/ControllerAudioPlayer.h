#pragma once

#include <QObject>
#include "Scheduler/Scheduler.h"
#include "core/WElement.h"
#include "audioplay/AudioPlayerQt.h"
#include "AudioData/AudioData.h"

class ControllerAudioPlayer : public QObject
{
    Q_OBJECT

    Q_PROPERTY(unsigned positionSecond READ getPosition WRITE setPosition NOTIFY onPositionChanged);
    Q_PROPERTY(unsigned duration READ getDuration NOTIFY onDurationChanged);

    AudioPlayer& _audioPlayer;
public:
    explicit ControllerAudioPlayer(QObject *parent, AudioPlayer& player);

    /**
     * \return The number of seconds pass
     * */
    [[nodiscard]]
    auto getPositionInSeconds() const -> unsigned ;

    [[nodiscard]]
    auto isPlaying() const -> bool;

    /**
     * \return The duration in seconds
     */
    [[nodiscard]]
    auto getDuration() const -> unsigned;

    /**
     * \brief This method is equals to getPositionInSeconds
     * */
    [[nodiscard]]
    auto getPosition() const -> unsigned;


    void setPosition(unsigned newPosition);

    DEFINE_LISTENER_1(audioPositionChanged, Unsigned, time);
    DEFINE_LISTENER_0(durationChanged);
signals:
    void onPositionChanged();
    void onDurationChanged();
};
