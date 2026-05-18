import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Calculator 1.0

ApplicationWindow
{
    id: topItem

    visible: true

    width: 640
    height: 480

    title: "Калькулятор"

    color: "#1e1e1e"

    CalclulatorInputValidator
    {
        id: calclulatorInputValidator
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
    }

    Component.onCompleted:
    {
        calculatorRequestQueue.addRequest("123+123", 3);
        calculatorRequestQueue.addRequest("123+123", 3);
        calculatorRequestQueue.addRequest("123+123", 3);
        calculatorRequestQueue.addRequest("123+123", 3);
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

            calclulatorInputValidator: calclulatorInputValidator
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
        }
    }
}
