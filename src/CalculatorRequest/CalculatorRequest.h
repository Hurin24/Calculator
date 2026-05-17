#ifndef CALCULATOR_REQUEST_H
#define CALCULATOR_REQUEST_H

#include <QString>
#include <atomic>

class CalculatorRequest
{
    friend class CalculatorResponse;

public:
    CalculatorRequest(const QString& expression, int delay);

    int getID();
    QString getExpression();
    int getDelay();

private:
    static std::atomic<int> nextID;
    static int getNextID();

    int m_id = 0;
    QString m_expression;
    int m_delay = 0;
};

#endif //CALCULATOR_REQUEST_H
