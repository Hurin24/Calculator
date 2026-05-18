#include "CalculatorResponseQueue.h"

#include "../CalculatorResponseWorker/CalculatorResponseWorker.h"
#include "../CalculatorOutputWriter/CalculatorOutputWriter.h"

CalculatorResponseQueue::CalculatorResponseQueue(QObject* ptrParent) :
                         QObject(ptrParent)
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
            m_calculatorResponseWorker->notify();
        }

        emit calculatorResponseWorkerChanged();
    }
}

CalculatorOutputWriter* CalculatorResponseQueue::getCalculatorOutputWriter() const
{
    return m_calculatorOutputWriter;
}

void CalculatorResponseQueue::setCalculatorOutputWriter(CalculatorOutputWriter* calculatorOutputWriter)
{
    if(m_calculatorOutputWriter != calculatorOutputWriter)
    {
        m_calculatorOutputWriter = calculatorOutputWriter;

        emit calculatorOutputWriterChanged();
    }
}

int CalculatorResponseQueue::getSize()
{
    std::lock_guard<std::mutex> lockGuard(m_calculatorResponseListMutex);

    return m_calculatorResponseList.size();
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
        m_calculatorResponseWorker->notify();
    }

    emit sizeChanged();
}

std::unique_ptr<CalculatorResponse> CalculatorResponseQueue::getResponse()
{
    std::unique_lock<std::mutex> uniqueLock(m_calculatorResponseListMutex);

    auto iterator = m_calculatorResponseList.begin();

    if(iterator != m_calculatorResponseList.end())
    {
        std::unique_ptr<CalculatorResponse> returnPtr(std::move(*iterator));
        m_calculatorResponseList.erase(iterator);

        uniqueLock.unlock();

        m_calculatorOutputWriter->writeResponse(returnPtr);

        emit sizeChanged();

        return returnPtr;
    }
    else
    {
        return std::unique_ptr<CalculatorResponse>(nullptr);
    }
}
