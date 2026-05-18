#include "CalculatorSharedWrapper.h"
#include <iostream>

#ifdef _WIN32
    #define GET_LAST_ERROR() GetLastError()
    #define GET_PROC_ADDRESS(handle, name) GetProcAddress((HMODULE)handle, name)
    #define LOAD_LIBRARY(path) LoadLibraryA(path)
    #define FREE_LIBRARY(handle) FreeLibrary((HMODULE)handle)
#else
    #define GET_LAST_ERROR() dlerror()
    #define GET_PROC_ADDRESS(handle, name) dlsym(handle, name)
    #define LOAD_LIBRARY(path) dlopen(path, RTLD_LAZY)
    #define FREE_LIBRARY(handle) dlclose(handle)
#endif

CalculatorSharedWrapper::~CalculatorSharedWrapper()
{
    unload();
}

bool CalculatorSharedWrapper::load(const std::string& libraryPath)
{
    if(m_isLoaded)
    {
        unload();
    }

    //Загружаем библиотеку
    m_handle = LOAD_LIBRARY(libraryPath.c_str());

    if(!m_handle)
    {
        #ifdef _WIN32
            m_errorMessage = "Не удалось найти библиотеку: " + std::to_string(GET_LAST_ERROR());
        #else
            const char* error = GET_LAST_ERROR();
            m_errorMessage = error ? error : "Не удалось найти библиотеку";
        #endif
        return false;
    }

    // Получаем указатель на функцию
    m_doIt = (double(*)(int, double, double))GET_PROC_ADDRESS(m_handle, "doIt");

    if (!m_doIt) {
        #ifdef _WIN32
            m_errorMessage = "Не удалось найти функцию 'doIt': " + std::to_string(GET_LAST_ERROR());
        #else
            const char* error = GET_LAST_ERROR();
            m_errorMessage = error ? error : "Не удалось найти функцию 'doIt'";
        #endif
        FREE_LIBRARY(m_handle);
        m_handle = nullptr;
        return false;
    }

    m_isLoaded = true;
    m_errorMessage.clear();
    return true;
}

void CalculatorSharedWrapper::unload()
{
    if(m_handle && m_isLoaded)
    {
        FREE_LIBRARY(m_handle);
        m_handle = nullptr;
        m_doIt = nullptr;
        m_isLoaded = false;
    }
}

double CalculatorSharedWrapper::doIt(int typeWork, double operandA, double operandB)
{
    if(!m_isLoaded || !m_doIt)
    {
        throw std::runtime_error("Библиотека не инициализирована");
    }

    return m_doIt(typeWork, operandA, operandB);
}