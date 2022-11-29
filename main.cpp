#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "textballoon.h"
#include <QStringLiteral>
#include "controller/controllerList/controllerList.h"
#include <QQmlContext>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/testing_qml/main.qml"));

    controllerList controller(nullptr);

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    qmlRegisterType<TextBalloon>("TextBalloon", 1, 0, "Disegnatore");

    QQmlContext *context = engine.rootContext();
    context->setContextProperty("_controllerListPreview", &controller);

    engine.load(url);

    return app.exec();
}
