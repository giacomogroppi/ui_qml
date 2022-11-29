#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "textballoon.h"
#include <QStringLiteral>
#include "controller/controllerList/controllerList.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/testing_qml/main.qml"));

    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    qmlRegisterType<TextBalloon>("TextBalloon", 1, 0, "Disegnatore");
    qmlRegisterType<controllerList>("ControllerList", 1, 0, "ControllerList");

    engine.load(url);

    return app.exec();
}
