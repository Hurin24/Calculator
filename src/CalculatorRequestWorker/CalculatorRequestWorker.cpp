#include "CalculatorRequestWorker.h"

#include "../CalculatorRequestQueue/CalculatorRequestQueue.h"
#include "../CalculatorResponseQueue/CalculatorResponseQueue.h"
#include "../CalculatorRequest/CalculatorRequest.h"
#include "../Calculator/Calculator.h"


#include <memory>
#include <string>
#include <sstream>
#include <iostream>

#include <QString>
#include <QDebug>

CalculatorRequestWorker::CalculatorRequestWorker(QObject* ptrParent) :
                         QObject(ptrParent)
{
    start();
}

CalculatorRequestWorker::~CalculatorRequestWorker()
{
    stop();
}

CalculatorRequestQueue* CalculatorRequestWorker::getCalculatorRequestQueue()
{
    return m_calculatorRequestQueue;
}

void CalculatorRequestWorker::setCalculatorRequestQueue(CalculatorRequestQueue* calculatorRequestQueue)
{
    std::unique_lock<std::mutex> conditionVariableUniqueLock(m_conditionVariableMutex);

    if(m_calculatorRequestQueue != calculatorRequestQueue)
    {
        m_calculatorRequestQueue = calculatorRequestQueue;

        conditionVariableUniqueLock.unlock();

        if(m_calculatorRequestQueue)
        {
            m_conditionVariable.notify_one();
        }

        emit calculatorRequestQueueChanged();
    }
}

CalculatorResponseQueue* CalculatorRequestWorker::getCalculatorResponseQueue()
{
    return m_calculatorResponseQueue;
}

void CalculatorRequestWorker::setCalculatorResponseQueue(CalculatorResponseQueue* calculatorResponseQueue)
{
    std::unique_lock<std::mutex> conditionVariableUniqueLock(m_conditionVariableMutex);

    if(m_calculatorResponseQueue != calculatorResponseQueue)
    {
        m_calculatorResponseQueue = calculatorResponseQueue;

        conditionVariableUniqueLock.unlock();

        if(m_calculatorResponseQueue)
        {
            m_conditionVariable.notify_one();
        }

        emit calculatorResponseQueueChanged();
    }
}

void CalculatorRequestWorker::notify()
{
    m_conditionVariable.notify_one();
}

void CalculatorRequestWorker::start()
{
    if(m_thread.joinable())
    {
        return;
    }

    m_isWork = true;
    m_thread = std::thread(CalculatorRequestWorker::process, this);
}

void CalculatorRequestWorker::stop()
{
    if(!m_isWork)
    {
        return;
    }

    m_isWork = false;
    m_conditionVariable.notify_all();

    if(m_thread.joinable())
    {
        m_thread.join();
    }
}

void CalculatorRequestWorker::process()
{
    while(m_isWork)
    {
        std::unique_lock<std::mutex> conditionVariableUniqueLock(m_conditionVariableMutex);

        m_conditionVariable.wait(conditionVariableUniqueLock, [this] { return !m_isWork || m_calculatorRequestQueue != nullptr && m_calculatorRequestQueue->getSize() > 0; });

        conditionVariableUniqueLock.unlock();

        while(true)
        {
            conditionVariableUniqueLock.lock();

            if(!m_calculatorRequestQueue)
            {
                break;
            }

            if(m_calculatorRequestQueue->getSize() <= 0)
            {
                break;
            }

            auto request = m_calculatorRequestQueue->getRequest();

            conditionVariableUniqueLock.unlock();

            if(!request)
            {
                break;
            }

            calculate(request);
        }
    }
}

void CalculatorRequestWorker::calculate(std::unique_ptr<CalculatorRequest>& calculatorRequest)
{
    std::this_thread::sleep_for(std::chrono::seconds(calculatorRequest->getDelay()));

    if(!calculatorRequest)
    {
        return;
    }

    QString expression = calculatorRequest->getExpression();

    if(expression.isEmpty())
    {
        m_calculatorResponseQueue->addResponse(*calculatorRequest, "Ошибка: пустое выражение");
        return;
    }

    double operandA = 0;
    double operandB = 0;
    char operation = '+';

    m_calculatorExpressionTokenizer.reset();

    int offset = 0;

    while(offset < expression.size())
    {
        int shift = m_calculatorExpressionTokenizer.parse(expression, offset);

        if(m_calculatorExpressionTokenizer.getState() == CalculatorExpressionTokenizer::CalculatorExpressionTokenizerState::Error)
        {
            m_calculatorResponseQueue->addResponse(*calculatorRequest, "Ошибка: " + m_calculatorExpressionTokenizer.getLastError());
            break;
        }

        switch(m_calculatorExpressionTokenizer.getTokenType())
        {
            case CalculatorExpressionTokenizer::TokenType::Number:
            {
                QString token = m_calculatorExpressionTokenizer.getToken();

                if(token.isEmpty())
                {
                    m_calculatorResponseQueue->addResponse(*calculatorRequest, QString("Ошибка: пустой токен Number").arg(token));
                    return;
                }

                bool isOk = false;
                operandB = token.toDouble(&isOk);

                if(!isOk)
                {
                    m_calculatorResponseQueue->addResponse(*calculatorRequest, QString("Ошибка: не удалось перевести токен %1 в число типа double").arg(token));
                    return;
                }

                qDebug() << operandB;

                try
                {
                    switch(operation)
                    {
                        case '+':
                            operandA = doIt(TypeWork::Addition, operandA, operandB);
                            break;
                        case '-':
                            operandA = doIt(TypeWork::Subtraction, operandA, operandB);
                            break;
                        case '*':
                            operandA = doIt(TypeWork::Multiplication, operandA, operandB);
                            break;
                        case '/':
                            operandA = doIt(TypeWork::Division, operandA, operandB);
                            break;
                        default:
                            m_calculatorResponseQueue->addResponse(*calculatorRequest, QString("Ошибка: неизвестная операция ").arg(operation));
                            return;
                            break;
                    }
                }
                catch(const std::logic_error& error)
                {
                    m_calculatorResponseQueue->addResponse(*calculatorRequest, QString("Ошибка: %1").arg(error.what()));
                    return;
                }
                break;
            }
            case CalculatorExpressionTokenizer::TokenType::Operation:
            {
                QString token = m_calculatorExpressionTokenizer.getToken();

                if(token.isEmpty())
                {
                    m_calculatorResponseQueue->addResponse(*calculatorRequest, QString("Ошибка: пустой токен Operation").arg(token));
                    return;
                }

                operation = token[0].toLatin1();
                break;
            }
            case CalculatorExpressionTokenizer::TokenType::ErrorToken:
            {
                m_calculatorResponseQueue->addResponse(*calculatorRequest, "Ошибка: " + m_calculatorExpressionTokenizer.getLastError());
                return;
                break;
            }
            default:
                break;
        }

        offset += shift;
    }


    if(m_calculatorResponseQueue)
    {
        m_calculatorResponseQueue->addResponse(*calculatorRequest, operandA);
    }
}
