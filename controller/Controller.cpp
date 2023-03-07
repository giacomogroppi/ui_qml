#include "Controller.h"
#include <QQmlContext>

QQmlContext *_content;

QQmlContext *Controller::getContent()
{
    Q_ASSERT(_content != nullptr);
    return _content;
}

Controller::Controller(QObject *parent,
                       QQmlContext *content,
                       QQmlApplicationEngine *engine)
    : QObject(parent),
      _engine(engine),
      _audio(new ControllerAudio(this)),
      _listPreview(new ControllerList(this)),
      _canvas(new ControllerCanvas(this)),
      _toolBar(new ControllerToolBar(this)),
      _pageCounter(new ControllerPageCounter(this)),
      _listFiles(new ControllerListFilesFolder(this))
{
    this->registerPrivateType();
}

void Controller::newFile()
{
    qWarning() << "Need to implement";
#pragma "need to implement"
}

Controller::~Controller() = default;

void Controller::registerPrivateType()
{
    registerType("_controllerListPreview",      this->_listPreview);
    registerType("_controllerAudio",            this->_audio);
    registerType("_controllerCanvas",           this->_canvas);
    registerType("_controllerToolBar",          this->_toolBar);
    registerType("_controllerPageCounter",      this->_pageCounter);
    registerType("_controllerListFilesFolder",  this->_listFiles);
}

