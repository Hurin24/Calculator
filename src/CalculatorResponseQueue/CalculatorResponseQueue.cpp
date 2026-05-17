#include "CalculatorResponseQueue.h"

#include "../CalculatorResponseWorker/CalculatorResponseWorker.h"

CalculatorResponseQueue::CalculatorResponseQueue()
{

}

CalculatorResponseWorker* CalculatorResponseQueue::getCalculatorResponseWorker()
{
    return m_calculatorResponseWorker;
}

void CalculatorResponseQueue::setCalculatorResponseWorker(CalculatorResponseWorker* newCalculatorResponseWorker)
{
    if(m_calculatorResponseWorker != newCalculatorResponseWorker)
    {
        m_calculatorResponseWorker = newCalculatorResponseWorker;

        if(m_calculatorResponseWorker)
        {

        }

        emit calculatorResponseWorkerChanged();
    }
}

void CalculatorResponseQueue::addResponse(const CalculatorRequest& calculatorRequest, double resultCalculation)
{
    std::unique_lock<std::mutex> uniqueLock(m_calculatorResponseListMutex);

    m_calculatorResponseList.emplace_back(new CalculatorResponse(calculatorRequest, resultCalculation));

    uniqueLock.unlock();

    if(m_calculatorResponseWorker)
    {
        m_calculatorResponseWorker->notify();
    }

    emit sizeChanged();
}

void CalculatorResponseQueue::addResponse(const CalculatorRequest& calculatorRequest, QString errorString)
{
    std::unique_lock<std::mutex> uniqueLock(m_calculatorResponseListMutex);

    m_calculatorResponseList.emplace_back(new CalculatorResponse(calculatorRequest, errorString));

    uniqueLock.unlock();

    if(m_calculatorResponseWorker)
    {

    }

    emit sizeChanged();
}

int CalculatorResponseQueue::getSize()
{
    std::lock_guard<std::mutex> lockGuard(m_calculatorResponseListMutex);
    return m_calculatorResponseList.size();
}

std::unique_ptr<CalculatorResponse> CalculatorResponseQueue::getResponse()
{
    std::lock_guard<std::mutex> lockGuard(m_calculatorResponseListMutex);

    auto iterator = m_calculatorResponseList.begin();

    if(iterator != m_calculatorResponseList.end())
    {
        std::unique_ptr<CalculatorResponse> returnPtr(std::move(*iterator));
        m_calculatorResponseList.erase(iterator);
        return returnPtr;
    }
    else
    {
        return std::unique_ptr<CalculatorResponse>(nullptr);
    }
}
