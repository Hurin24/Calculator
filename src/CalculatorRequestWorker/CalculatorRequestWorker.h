#ifndef CALCULATOR_REQUEST_WORKER_H
#define CALCULATOR_REQUEST_WORKER_H

#include "../CalculatorExpressionTokenizer/CalculatorExpressionTokenizer.h"

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>

#include <QObject>

class CalculatorRequest;
class CalculatorRequestQueue;
class CalculatorResponseQueue;

class CalculatorRequestWorker : public QObject
{
    Q_OBJECT
    Q_PROPERTY(CalculatorRequestQueue* calculatorRequestQueue READ getCalculatorRequestQueue WRITE setCalculatorRequestQueue NOTIFY calculatorRequestQueueChanged)
    Q_PROPERTY(CalculatorResponseQueue* calculatorResponseQueue READ getCalculatorResponseQueue WRITE setCalculatorResponseQueue NOTIFY calculatorResponseQueueChanged)

    friend class CalculatorRequestQueue;

public:
    CalculatorRequestWorker(QObject* ptrParent = nullptr);
    ~CalculatorRequestWorker();

    CalculatorRequestWorker(const CalculatorRequestWorker&) = delete;
    CalculatorRequestWorker& operator=(const CalculatorRequestWorker&) = delete;

    CalculatorRequestWorker(CalculatorRequestWorker&& other) = delete;
    CalculatorRequestWorker& operator=(CalculatorRequestWorker&& other) = delete;

    CalculatorRequestQueue* getCalculatorRequestQueue();
    void setCalculatorRequestQueue(CalculatorRequestQueue* calculatorRequestQueue);

    CalculatorResponseQueue* getCalculatorResponseQueue();
    void setCalculatorResponseQueue(CalculatorResponseQueue* calculatorResponseQueue);

private:
    void notify();
    void start();
    void stop();
    void process();

    std::thread m_thread;
    std::atomic<bool> m_isWork{true};

    std::mutex m_conditionVariableMutex;
    std::condition_variable m_conditionVariable;

    CalculatorRequestQueue* m_calculatorRequestQueue = nullptr;
    CalculatorResponseQueue* m_calculatorResponseQueue = nullptr;

    CalculatorExpressionTokenizer m_calculatorExpressionTokenizer;

    void calculate(std::unique_ptr<CalculatorRequest>& calculatorRequest);

signals:
    void calculatorRequestQueueChanged();
    void calculatorResponseQueueChanged();
};

#endif //CALCULATOR_REQUEST_WORKER_H
