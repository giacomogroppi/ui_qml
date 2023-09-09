#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStringLiteral>
#include "controller/Controller.h"
#include <QQmlContext>
#include <QTimer>
#include "Scheduler/Scheduler.h"
#include "controller/ControllerCanvas/WQMLCanvasComponentPage.h"

extern QQmlContext *_content;
extern StrokePre *__tmp;

int main(int argc, char *argv[])
{
    auto *scheduler = new Scheduler();
    qputenv("QSG_RENDER_LOOP", "basic");
    QGuiApplication app(argc, argv);
    //QQuickWindow::setGraphicsApi(QSGRendererInterface::Metal);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/src/main.qml"));

    /**
     * Dobbiamo instanzare lo strokePre in questo punto devo codice
     * perchè vogliamo assicurare a tutto il codice che accede a tale
     * oggetti che esso è valido. --> [non vogliamo controllare che sia nullo :)] 
    */
    __tmp = new StrokePre();

    qmlRegisterType<WQMLCanvasComponentStroke>("writernote.WQMLCanvasComponentStroke",
                                               1, 0,
                                               "WCanvasComponent");
    qmlRegisterType<WQMLCanvasComponentPage>("writernote.WQMLCanvasComponentPage",
                                               1, 0,
                                               "WCanvasComponentPage");
    qmlRegisterType<WQMLCanvasHandler>("writernote.WQMLCanvasHandler",
                                       1, 0,
                                       "WCanvasHandler");

    _content = engine.rootContext();
    Controller controller(nullptr, engine.rootContext(), &engine);
    QQmlContext *context = engine.rootContext();

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    context->setContextProperty("_controller", &controller);

    engine.load(url);

    //qGuiApp->processEvents(QEventLoop::ExcludeUserInputEvents);

    const auto res = app.exec();

    delete scheduler;

    return res;
}
