#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QUrl>

#include "CalculatorExpressionTokenizer/CalculatorExpressionTokenizer.h"
#include "CalculatorInputReader/CalculatorInputReader.h"
#include "CalculatorOutputWriter/CalculatorOutputWriter.h"
#include "CalculatorRequestQueue/CalculatorRequestQueue.h"
#include "CalculatorRequestWorker/CalculatorRequestWorker.h"
#include "CalculatorResponseQueue/CalculatorResponseQueue.h"
#include "CalculatorResponseWorker/CalculatorResponseWorker.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    app.setOrganizationName("RussianCalculatorCompany");
    app.setOrganizationDomain("RussianCalculator.com");
    app.setApplicationName("RussianCalculator");

    qmlRegisterType<CalculatorInputReader>("Calculator", 1, 0, "CalculatorInputReader");
    qmlRegisterType<CalculatorOutputWriter>("Calculator", 1, 0, "CalculatorOutputWriter");
    qmlRegisterType<CalculatorRequestQueue>("Calculator", 1, 0, "CalculatorRequestQueue");
    qmlRegisterType<CalculatorRequestWorker>("Calculator", 1, 0, "CalculatorRequestWorker");
    qmlRegisterType<CalculatorResponseQueue>("Calculator", 1, 0, "CalculatorResponseQueue");
    qmlRegisterType<CalculatorResponseWorker>("Calculator", 1, 0, "CalculatorResponseWorker");

    QQmlApplicationEngine engine;

    QUrl url(QStringLiteral("qrc:/MainWindow.qml"));

    engine.load(url);
    // Проверка успешности загрузки
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
