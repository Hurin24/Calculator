import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Qt.labs.settings 1.0
import Calculator 1.0

Rectangle
{
    id: topItem

    color: Qt.rgba(0,0,0,0)

    required property Settings settings
    required property StackView stackView
    required property CalculatorInputReader calculatorInputReader

    ColumnLayout
    {
        anchors.fill: parent

        spacing: 10

        GridLayout
        {
            Layout.minimumWidth: 300
            Layout.minimumHeight: 300

            Layout.preferredWidth: 100
            Layout.preferredHeight: 80

            Layout.fillWidth: true
            Layout.fillHeight: true

            columns: 2

            rowSpacing: 10

            columnSpacing: 10

            DoubleTextIndicatorWidget
            {
                Layout.minimumWidth: 100
                Layout.minimumHeight: 60

                Layout.preferredWidth: 100
                Layout.preferredHeight: 100

                Layout.fillWidth: true
                Layout.fillHeight: true

                topTextEdit.text: "Ширина:"
                bottomTextEdit.text: settings.windowWidth
                bottomTextEdit.readOnly: true
            }

            DoubleTextIndicatorWidget
            {
                Layout.minimumWidth: 100
                Layout.minimumHeight: 60

                Layout.preferredWidth: 100
                Layout.preferredHeight: 100

                Layout.fillWidth: true
                Layout.fillHeight: true

                topTextEdit.text: "Высота:"
                bottomTextEdit.text: settings.windowHeight
                bottomTextEdit.readOnly: true
            }

            DoubleTextIndicatorWidget
            {
                Layout.minimumWidth: 100
                Layout.minimumHeight: 60

                Layout.preferredWidth: 100
                Layout.preferredHeight: 100

                Layout.fillWidth: true
                Layout.fillHeight: true

                topTextEdit.text: "Задержка вычислений"
                bottomTextEdit.text: calculatorInputReader.delay
                bottomTextEdit.onEditingFinished:
                {
                    calculatorInputReader.delay = bottomTextEdit.text
                }
            }
        }

        CalculatorButton
        {
            textButton: "НАЗАД"

            Layout.minimumWidth: 60
            Layout.minimumHeight: 60

            Layout.preferredWidth: 60
            Layout.preferredHeight: 20

            Layout.maximumHeight: 120
            Layout.maximumWidth: 120

            Layout.fillWidth: true
            Layout.fillHeight: true

            onWasReleased:
            {
                stackView.pop()
            }
        }
    }
}