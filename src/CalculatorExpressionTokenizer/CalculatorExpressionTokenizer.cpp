#include "CalculatorExpressionTokenizer.h"

#include <QDebug>

int CalculatorExpressionTokenizer::parse(const QString& expression, int offset)
{
    m_token.clear();

    if(expression.isEmpty())
    {
        setLastError("Пустое выражение");
        m_state = Error;
        m_tokenType = ErrorToken;
        return 0;
    }

    for(int i = 0; offset + i < expression.size(); ++i)
    {
        QChar symbol = expression[offset + i];

        SymbolType type = getSymbolType(symbol);

        m_state = m_transitionTable[m_state][type];

        switch(m_state)
        {
            case WaitNegativeSymbol:
            case WaitStartIntegerPartNumber:
            case WaitEndIntegerPartNumber:
            case WaitStartFractionalPartNumber:
            case WaitEndFractionalPartNumber:
            {
                m_token.append(symbol);
                break;
            }
            case WasFoundNumber:
            {
                m_state = WaitStartOperationSymbol;
                m_tokenType = Number;
                return i;
                break;
            }
            case WaitStartOperationSymbol:
            case WaitEndOperationSymbol:
            {
                m_token.append(symbol);
                break;
            }
            case WasFoundOperationSymbol:
            {
                m_state = WaitNegativeSymbol;
                m_tokenType = Operation;
                return i;
                break;
            }
            case Error:
            {
                m_tokenType = ErrorToken;
                setLastError(QString("Не допустимый символ %1 в состоянии %2").arg(symbol).arg(m_state));
                return i;
                break;
            }
        }
    }

    switch(m_state)
    {
        case WaitNegativeSymbol:
        case WaitStartIntegerPartNumber:
        case WaitEndIntegerPartNumber:
        case WaitStartFractionalPartNumber:
        case WaitEndFractionalPartNumber:
        case WasFoundNumber:
        {
            m_state = WaitStartOperationSymbol;
            m_tokenType = Number;
            break;
        }
        case WaitStartOperationSymbol:
        case WaitEndOperationSymbol:
        case WasFoundOperationSymbol:
        {
            m_state = WaitNegativeSymbol;
            m_tokenType = Operation;
            break;
        }
        case Error:
        {
            m_tokenType = ErrorToken;
            setLastError(QString("Ошибка токенизации"));
            break;
        }
    }

    return expression.size() - offset;
}

void CalculatorExpressionTokenizer::reset()
{
    m_token.clear();
    m_tokenType = ErrorToken;
    m_state = WaitNegativeSymbol;
    m_lastError.clear();
}

CalculatorExpressionTokenizer::TokenType CalculatorExpressionTokenizer::getTokenType() const
{
    return m_tokenType;
}

QString CalculatorExpressionTokenizer::getToken() const
{
    return m_token;
}

CalculatorExpressionTokenizer::CalculatorExpressionTokenizerState CalculatorExpressionTokenizer::getState() const
{
    return m_state;
}

QString CalculatorExpressionTokenizer::getLastError() const
{
    return m_lastError;
}

void CalculatorExpressionTokenizer::setLastError(const QString& error)
{
    m_lastError = error;
}

CalculatorExpressionTokenizer::SymbolType CalculatorExpressionTokenizer::getSymbolType(QChar symbol) const
{
    if(symbol == '-')
    {
        return NegativeSymbol;
    }
    if(symbol.isDigit())
    {
        return DigitSymbol;
    }
    else if(symbol == '.')
    {
        return DotSymbol;
    }
    else if(symbol == '+' || symbol == '*' || symbol == '/')
    {
        return OperationSymbol;
    }
    else
    {
        return AnotherSymbol;
    }
}
