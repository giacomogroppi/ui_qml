#include "ControllerAudioRecorder.h"

ControllerAudioRecorder::ControllerAudioRecorder(QObject *parent)
    : QObject(parent)
{

}

ControllerAudioRecorder::~ControllerAudioRecorder()
{

}

bool ControllerAudioRecorder::isRecording()
{
    return false;
}

void ControllerAudioRecorder::setRecording(bool recording)
{
    emit isRecordingChange();
}

size_t ControllerAudioRecorder::getSecondRecording()
{
    return 0;
}
