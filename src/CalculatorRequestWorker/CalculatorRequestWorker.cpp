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

            if(!request)
            {
                break;
            }

            conditionVariableUniqueLock.unlock();

            qDebug() << QString("Получили запрос c ID: %1 и выражением %2 и задержкой %3").arg(request->getID()).arg(request->getExpression()).arg(request->getDelay());
            std::this_thread::sleep_for(std::chrono::seconds(request->getDelay()));

            conditionVariableUniqueLock.lock();

            if(m_calculatorResponseQueue)
            {
                m_calculatorResponseQueue->addResponse(*request, 0.0);
            }

            conditionVariableUniqueLock.unlock();

            qDebug() << QString("Отправили ответ c ID: %1").arg(request->getID());
        }
    }
}

void CalculatorRequestWorker::calculate(QString& expression)
{
    if(expression.isEmpty())
    {

    }

    std::stringstream tempStream(expression.toStdString());

    char operation;
    double operandA = 0;
    double operandB = 0;

    QString error = "Нет ошибок";

    if(!(tempStream >> operandA))
    {
        error = "";
    }

    while(true)
    {
        if(!(tempStream >> operation)) break;
        if(!(tempStream >> operandB)) break;

        switch(operation)
        {
            case '+':
                operandA = doIt(TypeWork::Addition, operandA, operandB);
                break;
            case '-':
                operandA = doIt(TypeWork::Addition, operandA, operandB);
                break;
            case '*':
                operandA = doIt(TypeWork::Multiplication, operandA, operandB);
                break;
            case '/':
                operandA = doIt(TypeWork::Division, operandA, operandB);
                break;
            default:
                error = "Неизвестная операция";
                break;
        }
    }
}
