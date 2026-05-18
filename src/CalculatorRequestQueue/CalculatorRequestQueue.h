#ifndef CALCULATOR_REQUEST_QUEUE_H
#define CALCULATOR_REQUEST_QUEUE_H

#include "../CalculatorRequest/CalculatorRequest.h"

#include <list>
#include <mutex>
#include <memory>

#include <QObject>

class CalculatorRequestWorker;

class CalculatorRequestQueue : public QObject
{
    Q_OBJECT

    Q_PROPERTY(CalculatorRequestWorker* calculatorRequestWorker READ getCalculatorRequestWorker WRITE setCalculatorRequestWorker NOTIFY calculatorRequestWorkerChanged)
    Q_PROPERTY(int size READ getSize NOTIFY sizeChanged)

    friend class CalculatorRequestWorker;

public:
    CalculatorRequestQueue(QObject* ptrParent = nullptr);

    CalculatorRequestWorker* getCalculatorRequestWorker();
    void setCalculatorRequestWorker(CalculatorRequestWorker* newCalculatorRequestWorker);

    Q_INVOKABLE void addRequest(QString newRequest, int delay);

    int getSize();


private:
    std::unique_ptr<CalculatorRequest> getRequest();

    CalculatorRequestWorker* m_calculatorRequestWorker = nullptr;

    std::mutex m_calculatorRequestListMutex;
    std::list<std::unique_ptr<CalculatorRequest>> m_calculatorRequestList;


signals:
    void calculatorRequestWorkerChanged();
    void sizeChanged();
};

#endif //CALCULATOR_REQUEST_QUEUE_H
