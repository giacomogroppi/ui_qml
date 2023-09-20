#pragma once

#include <QObject>
#include <QQmlApplicationEngine>

#include "ControllerList/ControllerList.h"
#include "ControllerCanvas/ControllerCanvas.h"
#include "ControllerToolBar/ControllerToolBar.h"
#include "ControllerPageCounter/ControllerPageCounter.h"
#include "ControllerListFiles/ControllerListFilesFolder.h"
#include "ControllerColor/ControllerColor.h"
#include "ControllerAudio/ControllerAudioRecorder.h"
#include "ControllerAudio/ControllerAudioPlayer.h"
#include "QtQml/qqmlcontext.h"

/* writernote include */
#include "touch/TabletController.h"

class Controller: public QObject
{
    Q_OBJECT
private:
    TabletController *_tabletController;

    QQmlApplicationEngine *_engine;

    ControllerList              *_listPreview;
    ControllerAudioRecorder     *_audioRecorder;
    ControllerAudioPlayer       *_audioPlayer;
    ControllerToolBar           *_toolBar;
    ControllerCanvas            *_canvas;
    ControllerPageCounter       *_pageCounter;
    ControllerListFilesFolder   *_listFiles;
    ControllerColor             *_color;

    void registerPrivateType();

    static QQmlContext *getContent();

    enum uiSelected {
        Main,
        Settings,
        ListFiles
    };

    enum uiSelected _uiSelected;

public:
    explicit Controller(QObject *parent, QQmlContext* content, QQmlApplicationEngine* engine);
    ~Controller() override;

    static void registerType(const QString &name, QObject *object)
    {
        QQmlContext *content = Controller::getContent();
        content->setContextProperty(name, object);
    };

    Q_PROPERTY(QString uiSelected READ getUiSelected WRITE setCurrentPage NOTIFY onUiSelectedChanged);
    [[nodiscard]] auto getUiSelected() const -> QString;
    Q_SIGNAL void onUiSelectedChanged();

    void setCurrentPage(QString currentPage);

    static Controller *instance();
    static void registerControllerCanvas(ControllerCanvas *controllerCanvas);

public slots:
    void newFile();
    void clickSetting();
    void clickBack();
    void showMain();
};
