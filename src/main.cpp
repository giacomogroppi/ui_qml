#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStringLiteral>
#include "controller/Controller.h"
#include <QQmlContext>

extern QQmlContext *_content;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));

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

    return app.exec();
}
