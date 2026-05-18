#include "CalculatorResponse.h"

#include "../CalculatorRequest/CalculatorRequest.h"

CalculatorResponse::CalculatorResponse(const CalculatorRequest& calculatorRequest, double resultCalculation) :
                    m_id(calculatorRequest.m_id),
                    m_resultCalculation(resultCalculation),
                    m_delay(calculatorRequest.m_delay)
{

}

CalculatorResponse::CalculatorResponse(const CalculatorRequest& calculatorRequest, QString errorString) :
                    m_id(calculatorRequest.m_id),
                    m_errorString(errorString),
                    m_isError(true),
                    m_delay(calculatorRequest.m_delay)
{

}

int CalculatorResponse::getID()
{
    return m_id;
}

double CalculatorResponse::getResultCalculation()
{
    return m_resultCalculation;
}

QString CalculatorResponse::getErrorString()
{
    return m_errorString;
}

bool CalculatorResponse::isError()
{
    return m_isError;
}

int CalculatorResponse::getDelay()
{
    return m_delay;
}
