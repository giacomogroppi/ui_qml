#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStringLiteral>
#include "controller/Controller.h"
#include <QQmlContext>
#include <QTimer>
#include "Scheduler/Scheduler.h"
#include "Scheduler/WTaskAllocator.h"
#include "controller/ControllerCanvas/WQMLCanvasComponentPage.h"
#include "core/Allocators.h"

extern QQmlContext *_content;
extern StrokePre *__tmp;

int main(int argc, char *argv[])
{
    qputenv("QSG_RENDER_LOOP", "basic");
    QGuiApplication app(argc, argv);

    auto *scheduler = new Scheduler();
    Allocators::init();

    //QQuickWindow::setGraphicsApi(QSGRendererInterface::Metal);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/src/main.qml"));

    qmlRegisterType<WQMLCanvasComponentStroke>("writernote.WQMLCanvasComponentStroke",
                                               1, 0,
                                               "WCanvasComponentStroke");
    qmlRegisterType<WQMLCanvasComponentPage>("writernote.WQMLCanvasComponentPage",
                                               1, 0,
                                               "WCanvasComponentPage");
    qmlRegisterType<WQMLCanvasHandler>("writernote.WQMLCanvasHandler",
                                       1, 0,
                                       "WCanvasHandler");

    _content = engine.rootContext();

    Controller *c = (Controller *) malloc(sizeof(Controller));
    { extern Controller *controller; controller = c; }
    new (c) Controller (nullptr, engine.rootContext(), &engine);

    QQmlContext *context = engine.rootContext();

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    context->setContextProperty("_controller", c);

    engine.load(url);

    //qGuiApp->processEvents(QEventLoop::ExcludeUserInputEvents);

    const auto res = QGuiApplication::exec();

    c->~Controller();
    free(c);

    delete scheduler;
    Allocators::exit();

    return res;
}
