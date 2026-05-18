#include "CalculatorResponseWorker.h"
#include "../CalculatorResponseQueue/CalculatorResponseQueue.h"
#include "../CalculatorResponse/CalculatorResponse.h"

#include <memory>

#include <QDebug>

CalculatorResponseWorker::CalculatorResponseWorker(QObject* ptrParent) :
                          QObject(ptrParent)
{
    start();
}

CalculatorResponseWorker::~CalculatorResponseWorker()
{
    stop();
}

CalculatorResponseQueue* CalculatorResponseWorker::getCalculatorResponseQueue()
{
    return m_calculatorResponseQueue;
}

void CalculatorResponseWorker::setCalculatorResponseQueue(CalculatorResponseQueue* calculatorResponseQueue)
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


void CalculatorResponseWorker::notify()
{
    m_conditionVariable.notify_one();
}

void CalculatorResponseWorker::start()
{
    if(m_thread.joinable())
    {
        return;
    }

    m_isWork = true;
    m_thread = std::thread(CalculatorResponseWorker::process, this);
}

void CalculatorResponseWorker::stop()
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

void CalculatorResponseWorker::process()
{
    while(m_isWork)
    {
        std::unique_lock<std::mutex> conditionVariableUniqueLock(m_conditionVariableMutex);

        m_conditionVariable.wait(conditionVariableUniqueLock, [this] { return !m_isWork || m_calculatorResponseQueue != nullptr && m_calculatorResponseQueue->getSize() > 0; });

        conditionVariableUniqueLock.unlock();

        while(true)
        {
            conditionVariableUniqueLock.lock();

            if(!m_calculatorResponseQueue)
            {
                break;
            }

            if(m_calculatorResponseQueue->getSize() <= 0)
            {
                break;
            }

            auto response = m_calculatorResponseQueue->getResponse();

            if(!response)
            {
                break;
            }

            conditionVariableUniqueLock.unlock();

            std::this_thread::sleep_for(std::chrono::seconds(response->getDelay()*2));

            if(response->isError())
            {
                qDebug() << QString("Получили ответ c ID: %1. 2").arg(response->getID()).arg(response->getErrorString());
            }
            else
            {
                qDebug() << QString("Получили ответ c ID: %1. Результат %2").arg(response->getID()).arg(response->getResultCalculation());
            }
        }
    }
}
