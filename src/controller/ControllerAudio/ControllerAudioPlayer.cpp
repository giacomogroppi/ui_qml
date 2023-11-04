#include "ControllerAudioPlayer.h"

ControllerAudioPlayer::ControllerAudioPlayer(QObject *parent,
                                             AudioPlayer& audioPlayer)
    : QObject (parent)
    , _audioPlayer (audioPlayer)
{
    w_connect_listener(&audioPlayer, onTimeChanged, this, audioPositionChanged);
}

auto ControllerAudioPlayer::getPositionInSeconds() const -> unsigned
{
    return _audioPlayer.getCurrentTimeSecond().seconds();
}

auto ControllerAudioPlayer::isPlaying() const -> bool
{
    return _audioPlayer.isPlaying();
}

auto ControllerAudioPlayer::audioPositionChanged(Unsigned position) -> void
{
    emit onPositionChanged();
}

auto ControllerAudioPlayer::getDuration() const -> unsigned
{
    return this->_audioPlayer.getCurrentDurationSeconds();
}

auto ControllerAudioPlayer::durationChanged() -> void
{
    emit onDurationChanged();
}

auto ControllerAudioPlayer::getPosition() const -> unsigned
{
    return this->_audioPlayer.getCurrentTimeSecond().seconds();
}

void ControllerAudioPlayer::setPosition(unsigned newPosition)
{
    const auto currentPosition = this->getPositionInSeconds();

    if (currentPosition != newPosition) {
        this->_audioPlayer.setPositionSecond(Unsigned(newPosition));
    }
}
