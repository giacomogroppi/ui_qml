#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QStringLiteral>
#include "controller/Controller.h"
#include <QQmlContext>
#include <QTimer>

extern QQmlContext *_content;
extern StrokePre *__tmp;

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QQuickWindow::setGraphicsApi(QSGRendererInterface::Metal);
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/src/main.qml"));

    /**
     * Dobbiamo instanzare lo strokePre in questo punto devo codice
     * perchè vogliamo assicurare a tutto il codice che accede a tale
     * oggetti che esso è valido. --> [non vogliamo controllare che sia nullo :)] 
    */
    __tmp = new StrokePre();

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
