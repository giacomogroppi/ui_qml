#include "ControllerAudio.h"

ControllerAudio::ControllerAudio(QObject *parent)
    : QObject(parent)
{

}

ControllerAudio::~ControllerAudio()
{

}

bool ControllerAudio::isRecording()
{
    return false;
}

void ControllerAudio::setRecording(bool recording)
{
    emit isRecordingChange();
}

size_t ControllerAudio::getSecondRecording()
{
    return 0;
}
