#include "CalculatorRequestQueue.h"

#include "../CalculatorRequestWorker/CalculatorRequestWorker.h"

CalculatorRequestQueue::CalculatorRequestQueue()
{

}

CalculatorRequestWorker* CalculatorRequestQueue::getCalculatorRequestWorker()
{
    return m_calculatorRequestWorker;
}

void CalculatorRequestQueue::setCalculatorRequestWorker(CalculatorRequestWorker* newCalculatorRequestWorker)
{
    if(m_calculatorRequestWorker != newCalculatorRequestWorker)
    {
        m_calculatorRequestWorker = newCalculatorRequestWorker;

        if(m_calculatorRequestWorker)
        {

        }

        emit calculatorRequestWorkerChanged();
    }
}

void CalculatorRequestQueue::addRequest(QString newRequest, int delay)
{
    if(delay < 0)
    {
        delay = 0;
    }

    std::unique_lock<std::mutex> uniqueLock(m_calculatorRequestListMutex);

    m_calculatorRequestList.emplace_back(new CalculatorRequest(newRequest, delay));

    uniqueLock.unlock();

    if(m_calculatorRequestWorker)
    {
        m_calculatorRequestWorker->notify();
    }

    emit sizeChanged();
}

int CalculatorRequestQueue::getSize()
{
    std::lock_guard<std::mutex> lockGuard(m_calculatorRequestListMutex);
    return m_calculatorRequestList.size();
}

std::unique_ptr<CalculatorRequest> CalculatorRequestQueue::getRequest()
{
    std::lock_guard<std::mutex> lockGuard(m_calculatorRequestListMutex);

    auto iterator = m_calculatorRequestList.begin();

    if(iterator != m_calculatorRequestList.end())
    {
        std::unique_ptr<CalculatorRequest> returnPtr(std::move(*iterator));
        m_calculatorRequestList.erase(iterator);
        return returnPtr;
    }
    else
    {
        return std::unique_ptr<CalculatorRequest>(nullptr);
    }
}
