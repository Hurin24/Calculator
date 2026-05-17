#ifndef CALCULATOR_REQUEST_WORKER_H
#define CALCULATOR_REQUEST_WORKER_H

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>

#include <QObject>

class CalculatorRequest;
class CalculatorRequestQueue;

class CalculatorRequestWorker : public QObject
{
    Q_OBJECT
    Q_PROPERTY(CalculatorRequestQueue* calculatorRequestWorker READ getCalculatorRequestQueue WRITE setCalculatorRequestQueue NOTIFY calculatorRequestQueueChanged)

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

signals:
    void calculatorRequestQueueChanged();
};

#endif //CALCULATOR_REQUEST_WORKER_H
