#include "Controller.h"
#include <QQmlContext>

Controller::Controller(QObject *parent, QQmlContext *content, QQmlApplicationEngine *engine)
    : QObject(parent),
      _content(content),
      _engine(engine)
{
    this->_audio = new ControllerAudio(this);
    this->_listPreview = new ControllerList(this);
    this->_canvas = new ControllerCanvas(this);

    this->registerType();
}

Controller::~Controller()
{
}

void Controller::registerType()
{
    _content->setContextProperty("_controllerListPreview", this->_listPreview);
    _content->setContextProperty("_controllerAudio", this->_audio);
    _content->setContextProperty("_controllerCanvas", this->_canvas);
}

