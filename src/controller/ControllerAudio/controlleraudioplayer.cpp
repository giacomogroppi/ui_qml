#include "controlleraudioplayer.h"

ControllerAudioPlayer::ControllerAudioPlayer(QObject *parent)
    : QObject{parent}
{

}

int ControllerAudioPlayer::getPositionInSeconds() const
{
    return 0;
}

bool ControllerAudioPlayer::isPlaying() const
{
    return false;
}
