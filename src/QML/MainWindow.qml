import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Calculator 1.0
import Qt.labs.settings 1.0

ApplicationWindow
{
    id: topItem

    Settings
    {
        id: settings
        property alias windowWidth: topItem.width
        property alias windowHeight: topItem.height
    }

    width: settings.windowWidth
    height: settings.windowHeight

    visible: true

    title: "Калькулятор"

    color: "#1e1e1e"

    CalculatorInputReader
    {
        id: calculatorInputReader

        calculatorRequestQueue: calculatorRequestQueue
    }

    CalculatorOutputWriter
    {
        id: calculatorOutputWriter
    }

    CalculatorRequestWorker
    {
        id: calculatorRequestWorker

        calculatorRequestQueue: calculatorRequestQueue
        calculatorResponseQueue: calculatorResponseQueue
    }

    CalculatorRequestQueue
    {
        id: calculatorRequestQueue

        calculatorRequestWorker: calculatorRequestWorker
        calculatorOutputWriter: calculatorOutputWriter
    }

    CalculatorResponseWorker
    {
        id: calculatorResponseWorker

        calculatorResponseQueue: calculatorResponseQueue
    }

    CalculatorResponseQueue
    {
        id: calculatorResponseQueue

        calculatorResponseWorker: calculatorResponseWorker
        calculatorOutputWriter: calculatorOutputWriter
    }

    RowLayout
    {
        anchors.fill: parent
        anchors.margins: 10

        spacing: 10

        CalculatorWidget
        {
            Layout.minimumWidth: 300
            Layout.minimumHeight: 300

            Layout.preferredWidth: 50
            Layout.preferredHeight: 100

            Layout.fillWidth: true
            Layout.fillHeight: true

            calculatorInputReader: calculatorInputReader
        }

        HistoryRequestWidget
        {
            Layout.minimumWidth: 50
            Layout.minimumHeight: 100

            Layout.preferredWidth: 300
            Layout.preferredHeight: 300

            Layout.fillWidth: true
            Layout.fillHeight: true

            calculatorRequestQueue: calculatorRequestQueue
            calculatorResponseQueue: calculatorResponseQueue
            calculatorOutputWriter: calculatorOutputWriter
        }
    }
}
