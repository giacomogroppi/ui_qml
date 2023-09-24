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
                                             [this] { return _audioRecorder->getSecondRecording(); },
                                             [this] { return this->_audioPlayer->isPlaying(); },
                                             [this] {
                                                 return this->_audioPlayer->getPositionInSeconds();
                                             }, ControllerSettings::getDefaultSavePath()))
    , _engine(engine)
    , _listPreview(new ControllerList(this))
    , _audioRecorder(new ControllerAudioRecorder(this))
    , _audioPlayer(new ControllerAudioPlayer(this))
    , _toolBar(new ControllerToolBar(this, _tabletController))
    , _canvas(new ControllerCanvas(nullptr))
    , _pageCounter(new ControllerPageCounter(this))
    , _color(new ControllerColor(this))
    , _settings(new ControllerSettings(this, _getPath))
    , _listOfFiles(new ControllerListFiles(this, _tabletController->getFileManager()))
    , _uiSelected(uiSelected::ListFiles)
{
    controller = this;
    this->registerPrivateType();

    registerControllerCanvas(_canvas);

    w_connect_lister(_tabletController, onPathChanged, [this] { emit this->onPathSavingChanged(); });

    QObject::connect(this, &Controller::onPathSavingChanged, _settings, &ControllerSettings::onPositionChanged);

    QObject::connect(_settings, &ControllerSettings::onPositionFileChange, [&] {
        this->_tabletController->setCurrentPathSaving(_settings->getPositionFile());
    });

    QObject::connect(_listOfFiles, &ControllerListFiles::onSelectFile, this, &Controller::openFile);
}

void Controller::openFile (QString name)
{
    _tabletController->openFile(name);
}

auto Controller::getUiSelected() const -> QString
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

void Controller::setCurrentPage(QString value)
{
    // TODO: define a way to save the current state in base of the current one
    if (value == "Main") _uiSelected = Controller::Main;
    else if (value == "Settings") _uiSelected = Controller::Settings;
    else if (value == "ListFiles") _uiSelected = Controller::ListFiles;
    else W_ASSERT(0);
}

auto Controller::instance() -> Controller *
{
    Q_ASSERT(controller != nullptr);
    return controller;
}

void Controller::registerControllerCanvas(ControllerCanvas *controllerCanvas)
{
    const auto getImg = [](QPainter &painter, double width, WFlags<UpdateEvent::UpdateEventType> typeUpdate) {
        return Controller::instance()->_toolBar->getImg(painter, width, typeUpdate);
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
    registerType("_controllerColor",            this->_color);
    registerType("_controllerSettings",         this->_settings);
    registerType("_controllerListFiles",        this->_listOfFiles);
}

