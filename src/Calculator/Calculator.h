#ifndef CALCULATOR_H
#define CALCULATOR_H

#ifdef LIB_CALCULATOR_SHARED
#ifdef LIB_CALCULATOR
    #define LIB_CALCULATOR_EXPORT __declspec(dllexport)
#else
    #define LIB_CALCULATOR_EXPORT __declspec(dllimport)
#endif
#else
    #define LIB_CALCULATOR_EXPORT
#endif

enum TypeWork
{
    Addition,
    Subtraction,
    Multiplication,
    Division
};

LIB_CALCULATOR_EXPORT double doIt(int typeWork, double operandA, double operandB) noexcept(false);

#endif //CALCULATOR_H
