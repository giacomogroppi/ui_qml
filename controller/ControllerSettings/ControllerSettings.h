#pragma once

#include <QObject>

class ControllerSettings: public QObject {
    Q_OBJECT

public:
    Q_INVOKABLE explicit ControllerSettings(QObject *parent = nullptr);
    ~ControllerSettings() = default;
};
