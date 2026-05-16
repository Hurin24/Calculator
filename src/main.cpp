#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QUrl>
#include <QSslSocket>

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qDebug() << QSslSocket::sslLibraryBuildVersionString();
    qDebug() << QSslSocket::supportsSsl();
    qDebug() << QSslSocket::sslLibraryVersionString();

    QQmlApplicationEngine engine;

    QUrl url(QStringLiteral("qrc:/MainWindow.qml"));

    engine.load(url);

    // Проверка успешности загрузки
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
