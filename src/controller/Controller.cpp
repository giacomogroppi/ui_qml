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
    , _tabletController(new TabletController(nullptr,
            [this]() { return _audioRecorder->getSecondRecording(); },
            [this] () { return this->_audioPlayer->isPlaying(); },
            [this] () { return this->_audioPlayer->getPositionInSeconds();
      }))
    , _engine(engine)
    , _listPreview(new ControllerList(this))
    , _audioRecorder(new ControllerAudioRecorder(this))
    , _audioPlayer(new ControllerAudioPlayer(this))
    , _toolBar(new ControllerToolBar(this, _tabletController))
    , _canvas(new ControllerCanvas(nullptr))
    , _pageCounter(new ControllerPageCounter(this))
    , _listFiles(new ControllerListFilesFolder(this))
    , _color(new ControllerColor(this))
    , _uiSelected(uiSelected::Main)
{
    controller = this;
    this->registerPrivateType();

    registerControllerCanvas(_canvas);
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

void Controller::registerControllerCanvas(ControllerCanvas *controllerCanvas)
{
    const auto getImg = [](QPainter &painter, double width) {
        return Controller::instance()->_toolBar->getImg(painter, width);
    };
    W_ASSERT(controllerCanvas);
    Controller::instance()->_canvas = controllerCanvas;

    Controller::instance()->_canvas->setFunc(getImg);

    QObject::connect(Controller::instance()->_canvas, &ControllerCanvas::onTouchBegin,    Controller::instance()->_toolBar, &ControllerToolBar::touchBegin, Qt::DirectConnection);
    QObject::connect(Controller::instance()->_canvas, &ControllerCanvas::onTouchUpdate,   Controller::instance()->_toolBar, &ControllerToolBar::touchUpdate, Qt::DirectConnection);
    QObject::connect(Controller::instance()->_canvas, &ControllerCanvas::onTouchEnd,      Controller::instance()->_toolBar, &ControllerToolBar::touchEnd, Qt::DirectConnection);
    QObject::connect(Controller::instance()->_toolBar, &ControllerToolBar::onDocSizeChanged, Controller::instance()->_canvas, &ControllerCanvas::sizeHasChanged, Qt::DirectConnection);

    QObject::connect(Controller::instance()->_canvas,   &ControllerCanvas::positionChanged, Controller::instance()->_toolBar, &ControllerToolBar::positionChanged, Qt::DirectConnection);
    QObject::connect(Controller::instance()->_toolBar,  &ControllerToolBar::onNeedRefresh, Controller::instance()->_canvas, &ControllerCanvas::refresh, Qt::DirectConnection);
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

Controller::~Controller()
{
    delete this->_tabletController;
}

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

