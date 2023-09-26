#include "ControllerAudioRecorder.h"
#include "controller/Controller.h"

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
    if (recording)
        Controller::instance()->stopRecording();
    else
        Controller::instance()->startRecording();

    emit isRecordingChange();
}

size_t ControllerAudioRecorder::getSecondRecording()
{
    return 0;
}
