cmake_minimum_required(VERSION 3.16)

project(Calculator VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_PREFIX_PATH "C:\\Qt\\5.15.2\\mingw81_64\\lib\\cmake")

find_package(Qt5 REQUIRED COMPONENTS Core Quick Qml)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(SOURCES
    src/CalclulatorInputValidator/CalclulatorInputValidator.cpp
    src/CalculatorExpressionTokenizer/CalculatorExpressionTokenizer.cpp
    src/CalculatorRequest/CalculatorRequest.cpp
    src/CalculatorRequestQueue/CalculatorRequestQueue.cpp
    src/CalculatorRequestWorker/CalculatorRequestWorker.cpp
    src/CalculatorResponse/CalculatorResponse.cpp
    src/CalculatorResponseQueue/CalculatorResponseQueue.cpp
    src/CalculatorResponseWorker/CalculatorResponseWorker.cpp
    src/main.cpp
)

set(HEADERS)

set(QRC_FILES
    src/QML/resources.qrc
)

add_subdirectory(src/Calculator)

add_executable(${PROJECT_NAME}
    ${SOURCES}
    ${HEADERS}
    ${QRC_FILES}
)

target_link_libraries(${PROJECT_NAME} Calculator::Static)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Quick Qt5::Qml)
