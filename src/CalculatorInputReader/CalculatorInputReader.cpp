#include "CalculatorInputReader.h"

#include "../CalculatorRequestQueue/CalculatorRequestQueue.h"

CalculatorInputReader::CalculatorInputReader(QObject* ptrParent):
                       QObject(ptrParent)
{

}

bool CalculatorInputReader::tryAppendText(QString text)
{
    QString newText(m_text + text);

    if(!isValidText(newText))
    {
        emit invalidCharacter();
        return false;
    }

    m_text.append(text);
    emit textChanged();

    return true;
}

void CalculatorInputReader::chopText()
{
    m_text.chop(1);

    emit textChanged();
}

void CalculatorInputReader::createRequest()
{
    if(m_calculatorRequestQueue)
    {
        m_calculatorRequestQueue->addRequest(m_text, m_delay);
    }
}

void CalculatorInputReader::clear()
{
    m_text.clear();

    emit textChanged();
}

QString CalculatorInputReader::getText() const
{
    return m_text;
}

void CalculatorInputReader::setText(QString text)
{
    if(m_text != text)
    {
        m_text = text;

        emit textChanged();
    }
}

int CalculatorInputReader::getDelay() const
{
    return m_delay;
}

void CalculatorInputReader::setDelay(int delay)
{
    if(m_delay != delay)
    {
        m_delay = delay;
        emit delayChanged();
    }
}

CalculatorRequestQueue* CalculatorInputReader::getCalculatorRequestQueue()
{
    return m_calculatorRequestQueue;
}

void CalculatorInputReader::setCalculatorRequestQueue(CalculatorRequestQueue* calculatorRequestQueue)
{
    if(m_calculatorRequestQueue != calculatorRequestQueue)
    {
        m_calculatorRequestQueue = calculatorRequestQueue;

        emit calculatorRequestQueueChanged();
    }
}

bool CalculatorInputReader::isValidText(const QString& text)
{
    m_calculatorExpressionTokenizer.reset();

    int offset = 0;

    while(offset < text.size())
    {
        int shift = m_calculatorExpressionTokenizer.parse(text, offset);

        if(m_calculatorExpressionTokenizer.getTokenType() == CalculatorExpressionTokenizer::TokenType::ErrorToken)
        {
            return false;
            break;
        }

        if(m_calculatorExpressionTokenizer.getState() == CalculatorExpressionTokenizer::CalculatorExpressionTokenizerState::Error)
        {
            return false;
            break;
        }

        offset += shift;
    }

    return true;
}
