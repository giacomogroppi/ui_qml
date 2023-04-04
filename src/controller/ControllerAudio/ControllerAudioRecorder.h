#pragma once

#include <QObject>

class ControllerAudioRecorder: public QObject {
    Q_OBJECT
public:
    explicit ControllerAudioRecorder(QObject *parent);
    ~ControllerAudioRecorder();

    Q_PROPERTY(bool isRecording READ isRecording WRITE setRecording NOTIFY isRecordingChange);
    bool isRecording();
    void setRecording(bool recording);
    Q_SIGNAL void isRecordingChange();

    Q_PROPERTY(size_t secondRecording READ getSecondRecording NOTIFY secondRecordingChange);
    size_t getSecondRecording();
    Q_SIGNAL void secondRecordingChange();
};
