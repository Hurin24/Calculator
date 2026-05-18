#ifndef CALCULATOR_REQUEST_QUEUE_H
#define CALCULATOR_REQUEST_QUEUE_H

#include "../CalculatorRequest/CalculatorRequest.h"

#include <list>
#include <mutex>
#include <memory>

#include <QObject>

class CalculatorRequestWorker;
class CalculatorOutputWriter;

class CalculatorRequestQueue : public QObject
{
    Q_OBJECT

    Q_PROPERTY(CalculatorRequestWorker* calculatorRequestWorker READ getCalculatorRequestWorker WRITE setCalculatorRequestWorker NOTIFY calculatorRequestWorkerChanged)
    Q_PROPERTY(CalculatorOutputWriter* calculatorOutputWriter READ getCalculatorOutputWriter WRITE setCalculatorOutputWriter NOTIFY calculatorOutputWriterChanged)
    Q_PROPERTY(int size READ getSize NOTIFY sizeChanged)

    friend class CalculatorRequestWorker;

public:
    CalculatorRequestQueue(QObject* ptrParent = nullptr);

    CalculatorRequestWorker* getCalculatorRequestWorker() const;
    void setCalculatorRequestWorker(CalculatorRequestWorker* newCalculatorRequestWorker);

    CalculatorOutputWriter* getCalculatorOutputWriter() const;
    void setCalculatorOutputWriter(CalculatorOutputWriter* calculatorOutputWriter);

    int getSize();

    Q_INVOKABLE void addRequest(QString newRequest, int delay);

private:
    std::unique_ptr<CalculatorRequest> getRequest();

    CalculatorRequestWorker* m_calculatorRequestWorker = nullptr;
    CalculatorOutputWriter* m_calculatorOutputWriter = nullptr;

    std::mutex m_calculatorRequestListMutex;
    std::list<std::unique_ptr<CalculatorRequest>> m_calculatorRequestList;


signals:
    void calculatorRequestWorkerChanged();
    void calculatorOutputWriterChanged();
    void sizeChanged();
};

#endif //CALCULATOR_REQUEST_QUEUE_H
