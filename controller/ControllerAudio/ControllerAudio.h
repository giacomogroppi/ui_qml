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
};
