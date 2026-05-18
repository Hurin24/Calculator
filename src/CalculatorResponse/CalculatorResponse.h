#ifndef CALCULATOR_RESPONSE_H
#define CALCULATOR_RESPONSE_H

#include <QString>

class CalculatorRequest;

class CalculatorResponse
{
public:
    CalculatorResponse(const CalculatorRequest& calculatorResponse, double resultCalculation);
    CalculatorResponse(const CalculatorRequest& calculatorResponse, QString errorString);

    int getID();
    double getResultCalculation();
    QString getErrorString();
    bool isError();
    int getDelay();

private:
    int m_id = 0;
    double m_resultCalculation = 0;
    QString m_errorString = "Нет ошибок";
    bool m_isError = false;
    int m_delay = 0;
};

#endif //CALCULATOR_RESPONSE_H
