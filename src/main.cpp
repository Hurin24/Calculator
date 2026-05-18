#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickView>
#include <QUrl>

#include "CalculatorExpressionTokenizer/CalculatorExpressionTokenizer.h"
#include "CalclulatorInputValidator/CalclulatorInputValidator.h"
#include "CalculatorRequestQueue/CalculatorRequestQueue.h"
#include "CalculatorRequestWorker/CalculatorRequestWorker.h"
#include "CalculatorResponseQueue/CalculatorResponseQueue.h"
#include "CalculatorResponseWorker/CalculatorResponseWorker.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    qmlRegisterType<CalclulatorInputValidator>("Calculator", 1, 0, "CalclulatorInputValidator");
    qmlRegisterType<CalculatorRequestQueue>("Calculator", 1, 0, "CalculatorRequestQueue");
    qmlRegisterType<CalculatorRequestWorker>("Calculator", 1, 0, "CalculatorRequestWorker");
    qmlRegisterType<CalculatorResponseQueue>("Calculator", 1, 0, "CalculatorResponseQueue");
    qmlRegisterType<CalculatorResponseWorker>("Calculator", 1, 0, "CalculatorResponseWorker");

    QQmlApplicationEngine engine;

    QUrl url(QStringLiteral("qrc:/MainWindow.qml"));

    engine.load(url);

    QString tempString = "-123.4353 + 1231 - 12331 / 1434.340 * 1233.888";
    tempString.remove(' ');

    // CalculatorExpressionTokenizer calculatorExpressionTokenizer;
    // calculatorExpressionTokenizer.reset();
    // int offset = 0;

    // while(offset < tempString.size())
    // {
    //     int newOffset = calculatorExpressionTokenizer.parse(tempString, offset);

    //     if(calculatorExpressionTokenizer.getTokenType() == CalculatorExpressionTokenizer::TokenType::ErrorToken)
    //     {
    //         qDebug() << calculatorExpressionTokenizer.getLastError();
    //         break;
    //     }

    //     if(calculatorExpressionTokenizer.getState() == CalculatorExpressionTokenizer::CalculatorExpressionTokenizerState::Error)
    //     {
    //         qDebug() << calculatorExpressionTokenizer.getLastError();
    //         break;
    //     }

    //     qDebug() << "Нашли токен" << calculatorExpressionTokenizer.getToken();

    //     offset += newOffset;
    // }

    // CalculatorRequestQueue calculatorRequestQueue;
    // CalculatorRequestWorker calculatorRequestWorker;
    // CalculatorResponseQueue calculatorResponseQueue;
    // CalculatorResponseWorker calculatorResponseWorker;

    // calculatorRequestQueue.setCalculatorRequestWorker(&calculatorRequestWorker);
    // calculatorRequestWorker.setCalculatorRequestQueue(&calculatorRequestQueue);
    // calculatorRequestWorker.setCalculatorResponseQueue(&calculatorResponseQueue);

    // calculatorResponseQueue.setCalculatorResponseWorker(&calculatorResponseWorker);
    // calculatorResponseWorker.setCalculatorResponseQueue(&calculatorResponseQueue);

    // calculatorRequestQueue.addRequest("123321 + 123", 3);
    // calculatorRequestQueue.addRequest("123321 + 123", 3);
    // calculatorRequestQueue.addRequest("123321 + 123", 3);


    // Проверка успешности загрузки
    if (engine.rootObjects().isEmpty())
        return -1;

    return app.exec();
}
