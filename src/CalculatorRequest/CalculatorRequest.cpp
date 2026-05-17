#include "CalculatorRequest.h"

std::atomic<int> CalculatorRequest::nextID{0};

CalculatorRequest::CalculatorRequest(const QString& expression, int delay) :
                   m_expression(expression),
                   m_delay(delay)
{
    m_id = getNextID();
}

int CalculatorRequest::getID()
{
    return m_id;
}

QString CalculatorRequest::getExpression()
{
    return m_expression;
}

int CalculatorRequest::getDelay()
{
    return m_delay;
}

int CalculatorRequest::getNextID()
{
    return nextID.fetch_add(1);
}
