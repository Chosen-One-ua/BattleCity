#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "GameController.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

	GameController* game {new GameController(&app, &engine)};

    engine.load(QUrl(QLatin1String("qrc:/qml/main.qml")));

    return app.exec();
}
