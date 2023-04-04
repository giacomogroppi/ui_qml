#include "Controller.h"
#include <QQmlContext>

QQmlContext *_content;
Controller *controller = nullptr;

QQmlContext *Controller::getContent()
{
    Q_ASSERT(_content != nullptr);
    return _content;
}

Controller::Controller(QObject *parent,
                       QQmlContext *content,
                       QQmlApplicationEngine *engine)
    : QObject(parent)
    , _tabletController(new TabletController(this,
            [this]() { return _audioRecorder->getSecondRecording(); },
            [this] () { return this->_audioPlayer->isPlaying(); },
            [this] () { return this->_audioPlayer->getPositionInSeconds(); }))
    , _engine(engine)
    , _audioRecorder(new ControllerAudioRecorder(this))
    , _audioPlayer(new ControllerAudioPlayer(this))
    , _listPreview(new ControllerList(this))
    , _canvas(new ControllerCanvas(this, [this]() -> const QImage &{ return this->_tabletController->getImg(); }))
    , _toolBar(new ControllerToolBar(this, _tabletController))
    , _pageCounter(new ControllerPageCounter(this))
    , _listFiles(new ControllerListFilesFolder(this))
    , _color(new ControllerColor(this))
    , _uiSelected(uiSelected::Main)
{
    controller = this;
    this->registerPrivateType();

    QObject::connect(_canvas, &ControllerCanvas::onTouchBegin,    _toolBar, &ControllerToolBar::touchBegin, Qt::ConnectionType::DirectConnection);
    QObject::connect(_canvas, &ControllerCanvas::onTouchUpdate,   _toolBar, &ControllerToolBar::touchUpdate, Qt::ConnectionType::DirectConnection);
    QObject::connect(_canvas, &ControllerCanvas::onTouchEnd,      _toolBar, &ControllerToolBar::touchEnd, Qt::ConnectionType::DirectConnection);

    QObject::connect(_canvas,   &ControllerCanvas::positionChanged, _toolBar, &ControllerToolBar::positionChanged, Qt::ConnectionType::DirectConnection);
    QObject::connect(_toolBar,  &ControllerToolBar::onNeedRefresh, _canvas, &ControllerCanvas::refresh, Qt::ConnectionType::DirectConnection);
}

QString Controller::getUiSelected() const
{
    constexpr char const* listFiles = "qrc:/src/ui/listOfFiles/MainWindowListFile.qml";
    constexpr char const* settings  = "qrc:/src/ui/settings/Settings.qml";
    constexpr char const* main      = "qrc:/src/ui/pageCanvas/MainWindow.qml";

    switch (_uiSelected) {
    case uiSelected::Main:
        return main;
    case uiSelected::Settings:
        return settings;
    case uiSelected::ListFiles:
        return listFiles;
    }
    Q_ASSERT(0);
}

Controller *Controller::instance()
{
    Q_ASSERT(controller != nullptr);
    return controller;
}

void Controller::newFile()
{
    qWarning() << "Need to implement";
#pragma "need to implement"
}

void Controller::clickSetting()
{
    this->_uiSelected = uiSelected::Settings;
    emit onUiSelectedChanged();
}

void Controller::clickBack()
{
    this->_uiSelected = uiSelected::ListFiles;
    emit onUiSelectedChanged();
}

void Controller::showMain()
{
    this->_uiSelected = uiSelected::Main;
    emit onUiSelectedChanged();
}

Controller::~Controller() = default;

void Controller::registerPrivateType()
{
    registerType("_controllerListPreview",      this->_listPreview);
    registerType("_controllerAudioRecorder",    this->_audioRecorder);
    registerType("_controllerAudioPlayer",      this->_audioPlayer);
    registerType("_controllerCanvas",           this->_canvas);
    registerType("_controllerToolBar",          this->_toolBar);
    registerType("_controllerPageCounter",      this->_pageCounter);
    registerType("_controllerListFilesFolder",  this->_listFiles);
    registerType("_controllerColor",            this->_color);
}

