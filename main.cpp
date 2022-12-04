#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "textballoon.h"
#include <QStringLiteral>
#include "controller/Controller.h"
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/testing_qml/main.qml"));

    Controller controller(nullptr, engine.rootContext(), &engine, engine.rootContext());
    QQmlContext *context = engine.rootContext();

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    qmlRegisterType<TextBalloon>("TextBalloon", 1, 0, "Disegnatore");

    context->setContextProperty("_controller", &controller);

    engine.load(url);

    return app.exec();
}
