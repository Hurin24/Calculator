#ifndef CALCULATOR_EXPRESSION_TOKENIZER_H
#define CALCULATOR_EXPRESSION_TOKENIZER_H

#include <QString>

class CalculatorExpressionTokenizer
{

public:
    enum CalculatorExpressionTokenizerState
    {
        WaitNegativeSymbol,            //Ожидаем отрицательный знак
        WaitStartIntegerPartNumber,    //Ожидаем начало целой части числа
        WaitEndIntegerPartNumber,      //Ожидаем конец целой части числа
        WaitStartFractionalPartNumber, //Ожидаем начало дробной части числа
        WaitEndFractionalPartNumber,   //Ожидаем конец дробной части числа
        WasFoundNumber,                //Нашли конец числа
        WaitOperationSymbol,           //Ожидаем операционный символ
        WasFoundOperationSymbol,       //Нашли операционный символ
        Error,
        QuantityParserStates
    };

    enum SymbolType
    {
        NegativeSymbol,
        DigitSymbol,
        DotSymbol,
        OperationSymbol,
        AnotherSymbol,
        QuantityParserSymbols
    };

    enum TokenType
    {
        Number,
        Operation,
        ErrorToken
    };

    int parse(const QString& expression, int offset);
    void reset();

    TokenType getTokenType() const;
    QString getToken() const;
    CalculatorExpressionTokenizerState getState() const;
    QString getLastError() const;

private:
    void setLastError(const QString& error);

    QString m_token;
    TokenType m_tokenType = ErrorToken;
    CalculatorExpressionTokenizerState m_state = WaitNegativeSymbol;
    QString m_lastError = "Нет ошибок";

    CalculatorExpressionTokenizerState m_transitionTable[QuantityParserStates][QuantityParserSymbols] =
    {
        //NegativeSymbol                    DigitSymbol                       DotSymbol                         OperationSymbol                   AnotherSymbol
        { WaitStartIntegerPartNumber,       WaitEndIntegerPartNumber,         WaitStartFractionalPartNumber,    Error,                            Error }, //WaitNegativeSymbol
        { Error,                            WaitEndIntegerPartNumber,         WaitStartFractionalPartNumber,    Error,                            Error }, //WaitStartIntegerPartNumber
        { WasFoundNumber,                   WaitEndIntegerPartNumber,         WaitStartFractionalPartNumber,    WasFoundNumber,                   Error }, //WaitEndIntegerPartNumber
        { WasFoundNumber,                   WaitEndFractionalPartNumber,      Error,                            WasFoundNumber,                   Error }, //WaitStartFractionalPartNumber
        { WasFoundNumber,                   WaitEndFractionalPartNumber,      Error,                            WasFoundNumber,                   Error }, //WaitEndFractionalPartNumber
        { Error,                            Error,                            Error,                            Error,                            Error }, //WasFoundNumber
        { WasFoundOperationSymbol,          Error,                            Error,                            WasFoundOperationSymbol,          Error }, //WaitOperationSymbol
        { Error,                            Error,                            Error,                            Error,                            Error }, //WasFoundOperationSymbol
        { Error,                            Error,                            Error,                            Error,                            Error }  //Error
    };


    // CalculatorExpressionTokenizerState m_transitionTable[QuantityParserStates][QuantityParserSymbols] =
    // {
    //     //NegativeSymbol                DigitSymbol                     DotSymbol                       OperationSymbol               AnotherSymbol
    //     { WaitEndIntegerPartNumber,     WaitEndIntegerPartNumber,       WaitEndFractionalPartNumber,    Error,                        Error }, //WaitNegativeSymbol
    //     { WasFoundNumber,               WaitEndIntegerPartNumber,       WaitEndFractionalPartNumber,    WasFoundNumber,               Error }, //WaitEndIntegerPartNumber
    //     { WasFoundNumber,               WaitEndFractionalPartNumber,    Error,                          WasFoundNumber,               Error }, //WaitEndFractionalPartNumber
    //     { WaitOperationSymbol,          Error,                          Error,                          WaitOperationSymbol,          Error }, //WasFoundNumber
    //     { WasFoundOperationSymbol,      Error,                          Error,                          WasFoundOperationSymbol,      Error }, //WaitOperationSymbol
    //     { Error,                        WaitEndIntegerPartNumber,       WaitEndIntegerPartNumber,       Error,                        Error }, //WasFoundOperationSymbol
    //     { Error,                        Error,                          Error,                          Error,                        Error }  //Error
    // };

    // CalculatorExpressionTokenizerState wasFoundEndNumber(SymbolType nextSymbolType, QChar nextSymbol);
    // CalculatorExpressionTokenizerState wasFoundEndOperation();

    SymbolType getSymbolType(QChar symbol) const;
};

#endif //CALCULATOR_EXPRESSION_TOKENIZER_H
