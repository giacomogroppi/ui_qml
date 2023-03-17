#pragma once

#include <QObject>

class ControllerColor : public QObject
{
    Q_OBJECT
public:
    explicit ControllerColor(QObject *parent = nullptr);
    ~ControllerColor() = default;

public slots:
    bool isDarkMode() const;

signals:

};


