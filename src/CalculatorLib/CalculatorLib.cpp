#include "CalculatorLib.h"

#include <stdexcept>

double doIt(int typeWork, double operandA, double operandB) noexcept(false)
{
    switch(typeWork)
    {
        case Addition:
        {
            return 0.0;
            break;
        }
        case Subtraction:
        {
            return 0.0;
            break;
        }
        case Multiplication:
        {
            return 0.0;
            break;
        }
        case Division:
        {
            return 0.0;
            break;
        }
        default:
            throw(std::logic_error("Недопустимая операция"));
            break;
    }

    return 0.0;
}
