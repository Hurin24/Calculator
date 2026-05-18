#include "CalculatorRequestQueue.h"

#include "../CalculatorRequestWorker/CalculatorRequestWorker.h"
#include "../CalculatorOutputWriter/CalculatorOutputWriter.h"

CalculatorRequestQueue::CalculatorRequestQueue(QObject* ptrParent) :
                        QObject(ptrParent)
{

}

CalculatorRequestWorker* CalculatorRequestQueue::getCalculatorRequestWorker() const
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
            m_calculatorRequestWorker->notify();
        }

        emit calculatorRequestWorkerChanged();
    }
}

CalculatorOutputWriter* CalculatorRequestQueue::getCalculatorOutputWriter() const
{
    return m_calculatorOutputWriter;
}

void CalculatorRequestQueue::setCalculatorOutputWriter(CalculatorOutputWriter* calculatorOutputWriter)
{
    if(m_calculatorOutputWriter != calculatorOutputWriter)
    {
        m_calculatorOutputWriter = calculatorOutputWriter;

        emit calculatorOutputWriterChanged();
    }
}

int CalculatorRequestQueue::getSize()
{
    std::lock_guard<std::mutex> lockGuard(m_calculatorRequestListMutex);

    return m_calculatorRequestList.size();
}

void CalculatorRequestQueue::addRequest(QString newRequest, int delay)
{
    if(delay < 0)
    {
        delay = 0;
    }

    std::unique_ptr<CalculatorRequest> newCalculatorRequest(new CalculatorRequest(newRequest, delay));
    m_calculatorOutputWriter->writeRequest(newCalculatorRequest);


    std::unique_lock<std::mutex> uniqueLock(m_calculatorRequestListMutex);

    m_calculatorRequestList.push_back(std::move(newCalculatorRequest));

    uniqueLock.unlock();


    if(m_calculatorRequestWorker)
    {
        m_calculatorRequestWorker->notify();
    }

    emit sizeChanged();
}

std::unique_ptr<CalculatorRequest> CalculatorRequestQueue::getRequest()
{
    std::unique_lock<std::mutex> uniqueLock(m_calculatorRequestListMutex);

    auto iterator = m_calculatorRequestList.begin();

    if(iterator != m_calculatorRequestList.end())
    {
        std::unique_ptr<CalculatorRequest> returnPtr(std::move(*iterator));
        m_calculatorRequestList.erase(iterator);

        uniqueLock.unlock();

        emit sizeChanged();

        return returnPtr;
    }
    else
    {
        return std::unique_ptr<CalculatorRequest>(nullptr);
    }
}
