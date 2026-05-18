#include "CalculatorOutputWriter.h"

#include "../CalculatorResponse/CalculatorResponse.h"
#include "../CalculatorRequest/CalculatorRequest.h"

CalculatorOutputWriter::CalculatorOutputWriter(QObject* ptrParent) :
                        QObject(ptrParent)
{

}

void CalculatorOutputWriter::writeRequest(std::unique_ptr<CalculatorRequest>& calculatorRequest)
{
    if(!calculatorRequest)
    {
        return;
    }

    QString logMessage("<span style='color: blue;'>Отправили запрос с ID: %1\n"
                                                  "Выражение: %2</span>");
    logMessage = logMessage.arg(calculatorRequest->getID()).arg(calculatorRequest->getExpression());

    emit sendLogMessage(logMessage);
}

void CalculatorOutputWriter::writeResponse(std::unique_ptr<CalculatorResponse>& calculatorResponse)
{
    if(!calculatorResponse)
    {
        return;
    }

    if(calculatorResponse->isError())
    {
        QString logMessage("<span style='color: yellow;'>Приняли ответ с ID: %1\n"
                                                      "Ошибка: %2</span>\n");
        logMessage =  logMessage.arg(calculatorResponse->getID()).arg(calculatorResponse->getErrorString());

        emit sendLogMessage(logMessage);
    }
    else
    {
        QString logMessage("<span style='color: green;'>Приняли ответ с ID: %1\n"
                                                      "Результат: %2</span>\n");
        logMessage = logMessage.arg(calculatorResponse->getID()).arg(calculatorResponse->getResultCalculation());

        emit sendLogMessage(logMessage);
    }
}