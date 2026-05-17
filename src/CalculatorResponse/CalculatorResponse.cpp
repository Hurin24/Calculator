#include "CalculatorResponse.h"

#include "../CalculatorRequest/CalculatorRequest.h"

CalculatorResponse::CalculatorResponse(const CalculatorRequest& calculatorRequest, double resultCalculation) :
                    m_id(calculatorRequest.m_id),
                    m_resultCalculation(resultCalculation)
{

}

CalculatorResponse::CalculatorResponse(const CalculatorRequest& calculatorRequest, QString errorString) :
                    m_id(calculatorRequest.m_id),
                    m_errorString(errorString)
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
