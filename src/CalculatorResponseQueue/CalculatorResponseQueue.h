#ifndef CALCULATOR_RESPONSE_QUEUE_H
#define CALCULATOR_RESPONSE_QUEUE_H

#include "../CalculatorResponse/CalculatorResponse.h"
#include "../CalculatorRequest/CalculatorRequest.h"

#include <list>
#include <mutex>
#include <memory>

#include <QObject>

class CalculatorResponseWorker;
class CalculatorOutputWriter;

class CalculatorResponseQueue : public QObject
{
    Q_OBJECT

    Q_PROPERTY(CalculatorResponseWorker* calculatorResponseWorker READ getCalculatorResponseWorker WRITE setCalculatorResponseWorker NOTIFY calculatorResponseWorkerChanged)
    Q_PROPERTY(CalculatorOutputWriter* calculatorOutputWriter READ getCalculatorOutputWriter WRITE setCalculatorOutputWriter NOTIFY calculatorOutputWriterChanged)
    Q_PROPERTY(int size READ getSize NOTIFY sizeChanged)

    friend class CalculatorResponseWorker;


public:
    CalculatorResponseQueue(QObject* ptrParent = nullptr);

    CalculatorResponseWorker* getCalculatorResponseWorker();
    void setCalculatorResponseWorker(CalculatorResponseWorker* newCalculatorWorker);

    CalculatorOutputWriter* getCalculatorOutputWriter() const;
    void setCalculatorOutputWriter(CalculatorOutputWriter* calculatorOutputWriter);

    int getSize();

    void addResponse(const CalculatorRequest& calculatorRequest, double resultCalculation);
    void addResponse(const CalculatorRequest& calculatorRequest, QString errorString);


private:
    std::unique_ptr<CalculatorResponse> getResponse();

    CalculatorResponseWorker* m_calculatorResponseWorker = nullptr;
    CalculatorOutputWriter* m_calculatorOutputWriter = nullptr;

    std::mutex m_calculatorResponseListMutex;
    std::list<std::unique_ptr<CalculatorResponse>> m_calculatorResponseList;


signals:
    void calculatorResponseWorkerChanged();
    void calculatorOutputWriterChanged();
    void sizeChanged();
};

#endif //CALCULATOR_RESPONSE_QUEUE_H
