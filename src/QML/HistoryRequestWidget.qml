import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Calculator 1.0

Rectangle
{
    color: Qt.rgba(0,0,0,0)

    required property CalculatorRequestQueue calculatorRequestQueue
    required property CalculatorResponseQueue calculatorResponseQueue
    required property CalculatorOutputWriter calculatorOutputWriter

    ColumnLayout
    {
        anchors.fill: parent

        spacing: 10

        RowLayout
        {
            spacing: 10

            Layout.minimumWidth: 300
            Layout.minimumHeight: 60

            Layout.preferredWidth: 100
            Layout.preferredHeight: 20

            Layout.fillWidth: true
            Layout.fillHeight: true

            TextIndicatorWidget
            {
                Layout.minimumWidth: 50
                Layout.minimumHeight: 30

                Layout.preferredWidth: 50
                Layout.preferredHeight: 50

                Layout.fillWidth: true
                Layout.fillHeight: true

                currentText.anchors.left: currentText.parent.left

                currentText.text: calculatorRequestQueue.size
            }

            TextIndicatorWidget
            {
                Layout.minimumWidth: 50
                Layout.minimumHeight: 30

                Layout.preferredWidth: 50
                Layout.preferredHeight: 50

                Layout.fillWidth: true
                Layout.fillHeight: true

                currentText.anchors.left: currentText.parent.left

                currentText.text: calculatorResponseQueue.size
            }
        }

        LogViewWidget
        {
            id: logViewWidget

            Layout.minimumWidth: 300
            Layout.minimumHeight: 300

            Layout.preferredWidth: 100
            Layout.preferredHeight: 80

            Layout.fillWidth: true
            Layout.fillHeight: true


            Connections
            {
                target: calculatorOutputWriter
                function onSendLogMessage(logMessage)
                {
                    logViewWidget.currentText.append(logMessage)
                }
            }
        }
    }
}
