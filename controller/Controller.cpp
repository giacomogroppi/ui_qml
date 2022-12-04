#include "Controller.h"
#include <QQmlContext>

Controller::Controller(QObject *parent, QQmlContext *content, QQmlApplicationEngine *engine, QObject *instance)
    : QObject(parent),
      _content(content),
      _engine(engine),
      _instance(instance)
{
    this->_audio = new ControllerAudio(this);
    this->_listPreview = new controllerList(this);
    this->_canvas = new ControllerCanvas();

    this->registerType();
}

Controller::~Controller()
{
    delete this->_instance;
}

QObject *Controller::instance()
{
    return _instance;
}

void Controller::registerType()
{
    _content->setContextProperty("_controllerListPreview", this->_listPreview);
    _content->setContextProperty("_controllerAudio", this->_audio);

    {
        constexpr const char *controllerCanvasName = "_controllerCanvas";
        _content->setContextProperty(controllerCanvasName, this->_canvas);
        _engine->addImageProvider(controllerCanvasName, this->_canvas);
    }

}
