#ifndef CALCULATOR_LIB_H
#define CALCULATOR_LIB_H

enum TypeWork
{
    Addition,
    Subtraction,
    Multiplication,
    Division
};

double doIt(int typeWork, double operandA, double operandB) noexcept(false);

#endif //CALCULATOR_LIB_H
