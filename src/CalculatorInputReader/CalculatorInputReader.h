#ifndef CALCULATOR_INPUT_VALIDATOR_H
#define CALCULATOR_INPUT_VALIDATOR_H

#include "../CalculatorExpressionTokenizer/CalculatorExpressionTokenizer.h"

#include <QObject>
#include <QString>

class CalculatorRequest;
class CalculatorRequestQueue;

class CalculatorInputReader : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString text READ getText WRITE setText NOTIFY textChanged)
    Q_PROPERTY(int delay READ getDelay WRITE setDelay NOTIFY delayChanged)
    Q_PROPERTY(CalculatorRequestQueue* calculatorRequestQueue READ getCalculatorRequestQueue WRITE setCalculatorRequestQueue NOTIFY calculatorRequestQueueChanged)

public:
    CalculatorInputReader(QObject* ptrParent = nullptr);

    Q_INVOKABLE bool tryAppendText(QString text);
    Q_INVOKABLE void chopText();
    Q_INVOKABLE void createRequest();
    Q_INVOKABLE void clear();

    QString getText() const;
    void setText(QString text);

    int getDelay() const;
    void setDelay(int delayOperation);

    CalculatorRequestQueue* getCalculatorRequestQueue();
    void setCalculatorRequestQueue(CalculatorRequestQueue* calculatorRequestQueue);

private:
    QString m_text;
    int m_delay = 1; //Секунда
    CalculatorRequestQueue* m_calculatorRequestQueue = nullptr;

    CalculatorExpressionTokenizer m_calculatorExpressionTokenizer;

    bool isValidText(const QString& text);

signals:
    void textChanged();
    void invalidCharacter();
    void delayChanged();
    void calculatorRequestQueueChanged();
};

#endif //CALCULATOR_INPUT_VALIDATOR_H
