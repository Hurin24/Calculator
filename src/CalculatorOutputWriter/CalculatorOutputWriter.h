#ifndef CALCULATOR_OUTPUT_WRITER_H
#define CALCULATOR_OUTPUT_WRITER_H

#include <memory>

#include <QObject>
#include <QString>

class CalculatorRequest;
class CalculatorResponse;

class CalculatorOutputWriter : public QObject
{
    Q_OBJECT

public:
    CalculatorOutputWriter(QObject* ptrParent = nullptr);

    void writeRequest(std::unique_ptr<CalculatorRequest>& calculatorRequest);
    void writeResponse(std::unique_ptr<CalculatorResponse>& calculatorResponse);

signals:
    void sendLogMessage(QString logMessage);

};

#endif //CALCULATOR_OUTPUT_WRITER_H
