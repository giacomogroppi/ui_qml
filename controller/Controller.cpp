#include "Controller.h"
#include <QQmlContext>

Controller::Controller(QObject *parent, QQmlContext *content, QQmlApplicationEngine *engine)
    : QObject(parent),
      _content(content),
      _engine(engine),
      _audio(new ControllerAudio(this)),
      _listPreview(new ControllerList(this)),
      _canvas(new ControllerCanvas(this)),
      _toolBar(new ControllerToolBar(this)),
      _pageCounter(new ControllerPageCounter(this))
{
    this->registerType();
}

Controller::~Controller()
{
}

void Controller::registerType()
{
    auto registerType = [this](const QString &name, QObject *object) {
        _content->setContextProperty(name, object);
    };

    registerType("_controllerListPreview",  this->_listPreview);
    registerType("_controllerAudio",        this->_audio);
    registerType("_controllerCanvas",       this->_canvas);
    registerType("_controllerToolBar",      this->_toolBar);
    registerType("_controllerPageCounter",  this->_pageCounter);
}

