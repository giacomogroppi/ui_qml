#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "textballoon.h"
#include <QStringLiteral>

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

    engine.load(url);

    return app.exec();
}
