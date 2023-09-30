#pragma once

#include <QObject>
#include "AudioData/AudioData.h"
#include "audiorecord/AudioRecorderQt.h"
#include "utils/WCommonScript.h"

class ControllerAudioRecorder: public QObject {
    Q_OBJECT

    Q_PROPERTY(bool isRecording READ isRecording WRITE setRecording NOTIFY isRecordingChange);
    Q_PROPERTY(unsigned secondRecording READ getSecondRecording NOTIFY secondRecordingChange);

    AudioRecord& _audioRecorder;

public:
    explicit ControllerAudioRecorder(QObject *parent, AudioRecord& audioRecord);
    ~ControllerAudioRecorder() override;

    nd auto isRecording() const -> bool;
    void setRecording(bool recording);

    nd auto getSecondRecording() const -> unsigned;

signals:
    void isRecordingChange();
    void secondRecordingChange();

};
