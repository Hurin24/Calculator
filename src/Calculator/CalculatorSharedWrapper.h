#ifndef CALCULATOR_SHARED_WRAPPER_H
#define CALCULATOR_SHARED_WRAPPER_H

#include <string>
#include <functional>
#include "Calculator.h"

#ifdef _WIN32
    #include <windows.h>
    typedef HMODULE LibHandle;
#else
    #include <dlfcn.h>
    typedef void* LibHandle;
#endif

class CalculatorSharedWrapper
{

private:
    LibHandle m_handle = nullptr;
    double (*m_doIt)(int, double, double) = nullptr;
    bool m_isLoaded = false;
    std::string m_errorMessage;

public:
    CalculatorSharedWrapper() = default;
    ~CalculatorSharedWrapper();

    // Загрузка библиотеки
    bool load(const std::string& libraryPath);
    void unload();
    bool isLoaded() const { return m_isLoaded; }
    std::string getLastError() const { return m_errorMessage; }

    // Вызов функции
    double doIt(int typeWork, double operandA, double operandB);

    // Получение указателя на функцию для прямого вызова
    double (*getFunction())(int, double, double) { return m_doIt; }
};

#endif //CALCULATOR_SHARED_WRAPPER_H