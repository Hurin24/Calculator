#include "CalculatorRequestWorker.h"
#include "../CalculatorRequestQueue/CalculatorRequestQueue.h"
#include "../CalculatorRequest/CalculatorRequest.h"

#include <memory>

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
        }
    }
}
