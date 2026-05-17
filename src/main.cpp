#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QUrl>
#include <QSslSocket>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;

    QUrl url(QStringLiteral("qrc:/MainWindow.qml"));

    engine.load(url);

    // Проверка успешности загрузки
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
