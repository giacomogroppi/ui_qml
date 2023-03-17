#pragma once

#include <QObject>

class ControllerAudio: public QObject {
    Q_OBJECT
public:
    explicit ControllerAudio(QObject *parent);
    ~ControllerAudio();

    Q_PROPERTY(bool isRecording READ isRecording WRITE setRecording NOTIFY isRecordingChange);
    bool isRecording();
    void setRecording(bool recording);
    Q_SIGNAL void isRecordingChange();

    Q_PROPERTY(size_t secondRecording READ getSecondRecording NOTIFY secondRecordingChange);
    size_t getSecondRecording();
    Q_SIGNAL void secondRecordingChange();
};
