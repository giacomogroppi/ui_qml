#pragma once

#include <QObject>

#include "currenttitle/document.h"

class ControllerDocument : public QObject
{
    Q_OBJECT
public:
    explicit ControllerDocument(QObject *parent);

    Document &getDoc();


};
