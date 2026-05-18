#ifndef CALCULATOR_H
#define CALCULATOR_H

enum TypeWork
{
    Addition,
    Subtraction,
    Multiplication,
    Division
};

double doIt(int typeWork, double operandA, double operandB) noexcept(false);

#endif //CALCULATOR_H
