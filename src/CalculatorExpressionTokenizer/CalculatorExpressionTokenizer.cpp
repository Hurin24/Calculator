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

    for(; offset < expression.size(); ++offset)
    {
        QChar symbol = expression[offset];

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
                return offset;
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
                m_state = WaitStartIntegerPartNumber;
                m_tokenType = Operation;
                return offset;
                break;
            }
            case Error:
            {
                m_tokenType = ErrorToken;
                setLastError(QString("Не допустимый символ ") + symbol + QString(" в состоянии ") + m_state);
                return offset;
                break;
            }
        }

        qDebug() << m_token;
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
            m_state = WaitStartIntegerPartNumber;
            m_tokenType = Operation;
            break;
        }
        case Error:
        {
            m_tokenType = ErrorToken;
            setLastError(QString("Ошибка токенизицаии"));
            break;
        }
    }

    return expression.size() - 1;
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

// CalculatorExpressionTokenizer::CalculatorExpressionTokenizerState CalculatorExpressionTokenizer::wasFoundEndNumber(SymbolType nextSymbolType, QChar nextSymbol)
// {
//     m_tokenType = Number;

//     switch(nextSymbolType)
//     {
//         case NegativeSymbol:
//         {
//             return WaitOperationSymbol;
//             break;
//         }
//         case DigitSymbol:
//         {
//             setLastError(QString("Не допустимый символ ") + nextSymbol + QString(" после токена Number: ") + m_token + QString(", ожидались символы токена Operation"));
//             return Error;
//             break;
//         }
//         case DotSymbol:
//         {
//             setLastError(QString("Не допустимый символ ") + nextSymbol + QString(" после токена Number: ") + m_token + QString(", ожидались символы токена Operation"));
//             return Error;
//             break;
//         }
//         case OperationSymbol:
//         {
//             return WaitOperationSymbol;
//             break;
//         }
//         case AnotherSymbol:
//         {
//             setLastError(QString("Не допустимый символ ") + nextSymbol + QString(" после токена Number: ") + m_token + QString(", ожидались символы токена Operation"));
//             return Error;
//             break;
//         }
//         default:
//             setLastError(QString("Не допустимый символ ") + nextSymbol + QString(" после токена Number: ") + m_token + QString(", ожидались символы токена Operation"));
//             return Error;
//             break;
//     }
// }

// CalculatorExpressionTokenizer::CalculatorExpressionTokenizerState CalculatorExpressionTokenizer::wasFoundEndOperation()
// {
//     m_tokenType = Operation;
//     return WaitEndIntegerPartNumber;
// }

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
