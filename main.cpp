#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "textballoon.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    const QUrl url(u"qrc:/testing_qml/main.qml"_qs);
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);

    qmlRegisterType<TextBalloon>("TextBalloon", 1, 0, "Disegnatore");

    engine.load(url);

    return app.exec();
}
