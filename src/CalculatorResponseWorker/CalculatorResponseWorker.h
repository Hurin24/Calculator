#ifndef CALCULATOR_RESPONSE_WORKER_H
#define CALCULATOR_RESPONSE_WORKER_H

#include <atomic>
#include <condition_variable>
#include <mutex>
#include <thread>

#include <QObject>

class CalculatorResponseQueue;
class CalculatorResponse;

class CalculatorResponseWorker : public QObject
{
    Q_OBJECT
    Q_PROPERTY(CalculatorResponseQueue* calculatorResponseQueue READ getCalculatorResponseQueue WRITE setCalculatorResponseQueue NOTIFY calculatorResponseQueueChanged)

    friend class CalculatorResponseQueue;


public:
    CalculatorResponseWorker(QObject* ptrParent = nullptr);
    ~CalculatorResponseWorker();

    CalculatorResponseWorker(const CalculatorResponseWorker&) = delete;
    CalculatorResponseWorker& operator=(const CalculatorResponseWorker&) = delete;

    CalculatorResponseWorker(CalculatorResponseWorker&& other) = delete;
    CalculatorResponseWorker& operator=(CalculatorResponseWorker&& other) = delete;

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

    CalculatorResponseQueue* m_calculatorResponseQueue = nullptr;


signals:
    void calculatorResponseQueueChanged();
    void printResponse(QString response);
};

#endif //CALCULATOR_RESPONSE_WORKER_H
