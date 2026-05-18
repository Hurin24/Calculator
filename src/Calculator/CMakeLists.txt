cmake_minimum_required(VERSION 3.10)

project(libCalculator)

set(SOURCES Calculator.cpp CalculatorSharedWrapper.cpp)
set(HEADERS Calculator.h CalculatorSharedWrapper.cpp)

#Создаем статическую библиотеку
add_library(Calculator_static STATIC ${SOURCES} ${HEADERS})
target_include_directories(Calculator_static PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

#Создаем динамическую библиотеку
add_library(Calculator_shared SHARED ${SOURCES} ${HEADERS})
target_include_directories(Calculator_shared PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(Calculator_shared PRIVATE LIB_CALCULATOR_SHARED)
target_compile_definitions(Calculator_shared PRIVATE LIB_CALCULATOR)

#Aлиасы для удобства
add_library(Calculator::Static ALIAS Calculator_static)
add_library(Calculator::Shared ALIAS Calculator_shared)
