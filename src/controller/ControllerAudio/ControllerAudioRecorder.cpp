#include "ControllerAudioRecorder.h"
#include "controller/Controller.h"

ControllerAudioRecorder::ControllerAudioRecorder(QObject *parent, AudioRecord& audioRecorder)
    : QObject(parent)
    , _audioRecorder(audioRecorder)
{

}

ControllerAudioRecorder::~ControllerAudioRecorder() = default;

auto ControllerAudioRecorder::isRecording() const -> bool
{
    return _audioRecorder.isRecording();
}

void ControllerAudioRecorder::setRecording(bool recording)
{
    if (recording)
        Controller::instance()->stopRecording();
    else
        Controller::instance()->startRecording();

    emit isRecordingChange();
}

auto ControllerAudioRecorder::getSecondRecording() const -> unsigned
{
    return _audioRecorder.getCurrentTime().seconds();
}
