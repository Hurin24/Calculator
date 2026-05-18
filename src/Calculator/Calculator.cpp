#include "Calculator.h"

#include <stdexcept>

double doIt(int typeWork, double operandA, double operandB) noexcept(false)
{
    switch(typeWork)
    {
        case Addition:
        {
            return operandA + operandB;
            break;
        }
        case Subtraction:
        {
            return operandA - operandB;
            break;
        }
        case Multiplication:
        {
            return operandA * operandB;;
            break;
        }
        case Division:
        {
            if(operandB == 0)
            {
                throw(std::logic_error("Невозможно делить на ноль"));
            }

            return operandA/operandB;;
            break;
        }
        default:
            throw(std::logic_error("Неизвестная операция"));
            break;
    }

    return 0.0;
}


