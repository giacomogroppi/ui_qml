#pragma once

#include <QObject>
#include <QQmlApplicationEngine>

#include "ControllerList/ControllerList.h"
#include "ControllerAudio/ControllerAudio.h"
#include "ControllerCanvas/ControllerCanvas.h"
#include "ControllerToolBar/ControllerToolBar.h"
#include "ControllerPageCounter/ControllerPageCounter.h"
#include "ControllerListFiles/ControllerListFilesFolder.h"
#include "ControllerColor/ControllerColor.h"
#include "QtQml/qqmlcontext.h"

/* writernote include */
#include "touch/TabletController.h"

class Controller: public QObject {
    Q_OBJECT
private:
    TabletController *_tabletController;

    ControllerList              *_listPreview;
    ControllerAudio             *_audio;
    ControllerCanvas            *_canvas;
    ControllerToolBar           *_toolBar;
    ControllerPageCounter       *_pageCounter;
    ControllerListFilesFolder   *_listFiles;
    ControllerColor             *_color;

    QQmlApplicationEngine *_engine;

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
    ~Controller();

    static void registerType(const QString &name, QObject *object)
    {
        QQmlContext *content = Controller::getContent();
        content->setContextProperty(name, object);
    };

    Q_PROPERTY(QString uiSelected READ getUiSelected NOTIFY onUiSelectedChanged);
    [[nodiscard]] QString getUiSelected() const;
    Q_SIGNAL void onUiSelectedChanged();

    static Controller *instance();

public slots:
    void newFile();
    void clickSetting();
    void clickBack();
    void showMain();
};
