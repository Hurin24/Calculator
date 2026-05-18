#ifndef CALCULATOR_RESPONSE_QUEUE_H
#define CALCULATOR_RESPONSE_QUEUE_H

#include "../CalculatorResponse/CalculatorResponse.h"
#include "../CalculatorRequest/CalculatorRequest.h"

#include <list>
#include <mutex>
#include <memory>

#include <QObject>

class CalculatorResponseWorker;

class CalculatorResponseQueue : public QObject
{
    Q_OBJECT

    Q_PROPERTY(CalculatorResponseWorker* calculatorResponseWorker READ getCalculatorResponseWorker WRITE setCalculatorResponseWorker NOTIFY calculatorResponseWorkerChanged)
    Q_PROPERTY(int size READ getSize NOTIFY sizeChanged)

    friend class CalculatorResponseWorker;


public:
    CalculatorResponseQueue(QObject* ptrParent = nullptr);

    CalculatorResponseWorker* getCalculatorResponseWorker();
    void setCalculatorResponseWorker(CalculatorResponseWorker* newCalculatorWorker);

    void addResponse(const CalculatorRequest& calculatorRequest, double resultCalculation);
    void addResponse(const CalculatorRequest& calculatorRequest, QString errorString);

    int getSize();


private:
    std::unique_ptr<CalculatorResponse> getResponse();

    CalculatorResponseWorker* m_calculatorResponseWorker = nullptr;

    std::mutex m_calculatorResponseListMutex;
    std::list<std::unique_ptr<CalculatorResponse>> m_calculatorResponseList;


signals:
    void calculatorResponseWorkerChanged();
    void sizeChanged();
};

#endif //CALCULATOR_RESPONSE_QUEUE_H
