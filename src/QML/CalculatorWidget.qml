import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Calculator 1.0

Rectangle
{
    color: Qt.rgba(0,0,0,0)

    required property CalclulatorInputValidator calclulatorInputValidator
    property alias textIndicatorWidget: textIndicatorWidget

    ColumnLayout
    {
        anchors.fill: parent
        spacing: 10

        TextIndicatorWidget
        {
            id: textIndicatorWidget

            Layout.minimumWidth: 300
            Layout.minimumHeight: 60

            Layout.preferredWidth: 100
            Layout.preferredHeight: 20

            Layout.fillWidth: true
            Layout.fillHeight: true

            currentText.horizontalAlignment: Text.AlignRight
            currentText.verticalAlignment: Text.AlignBottom

            currentText.text: calclulatorInputValidator.text
        }

        //Кнопки калькулятора
        GridLayout
        {
            columns: 4
            rowSpacing: 10
            columnSpacing: 10

            Layout.minimumWidth: 300
            Layout.minimumHeight: 300

            Layout.preferredWidth: 100
            Layout.preferredHeight: 80

            Layout.fillWidth: true
            Layout.fillHeight: true

            //Первый ряд
            Item
            {
                Layout.minimumWidth: 30
                Layout.minimumHeight: 30

                Layout.preferredWidth: 100
                Layout.preferredHeight: 100

                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            Item
            {
                Layout.minimumWidth: 30
                Layout.minimumHeight: 30

                Layout.preferredWidth: 100
                Layout.preferredHeight: 100

                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            CalculatorButton
            {
                textButton: "⌫"

                Layout.minimumWidth: 30
                Layout.minimumHeight: 30

                Layout.preferredWidth: 100
                Layout.preferredHeight: 100

                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            CalculatorButton
            {
                textButton: "÷"

                Layout.minimumWidth: 30
                Layout.minimumHeight: 30

                Layout.preferredWidth: 100
                Layout.preferredHeight: 100

                Layout.fillWidth: true
                Layout.fillHeight: true

                onWasReleased:
                {
                    calclulatorInputValidator.tryAppendText(symbol)
                }
            }

            //Второй ряд
            CalculatorButton
            {
                textButton: "7"

                Layout.minimumWidth: 30
                Layout.minimumHeight: 30

                Layout.preferredWidth: 100
                Layout.preferredHeight: 100

                Layout.fillWidth: true
                Layout.fillHeight: true

                onWasReleased:
                {
                    calclulatorInputValidator.tryAppendText(symbol)
                }
            }

            CalculatorButton
            {
                textButton: "8"

                Layout.minimumWidth: 30
                Layout.minimumHeight: 30

                Layout.preferredWidth: 100
                Layout.preferredHeight: 100

                Layout.fillWidth: true
                Layout.fillHeight: true

                onWasReleased:
                {
                    calclulatorInputValidator.tryAppendText(symbol)
                }
            }

            CalculatorButton
            {
                textButton: "9"

                Layout.minimumWidth: 30
                Layout.minimumHeight: 30

                Layout.preferredWidth: 100
                Layout.preferredHeight: 100

                Layout.fillWidth: true
                Layout.fillHeight: true

                onWasReleased:
                {
                    calclulatorInputValidator.tryAppendText(symbol)
                }
            }

            CalculatorButton
            {
                textButton: "×"

                Layout.minimumWidth: 30
                Layout.minimumHeight: 30

                Layout.preferredWidth: 100
                Layout.preferredHeight: 100

                Layout.fillWidth: true
                Layout.fillHeight: true

                onWasReleased:
                {
                    calclulatorInputValidator.tryAppendText(symbol)
                }
            }

            //Третий ряд
            CalculatorButton
            {
                textButton: "4"

                Layout.minimumWidth: 30
                Layout.minimumHeight: 30

                Layout.preferredWidth: 100
                Layout.preferredHeight: 100

                Layout.fillWidth: true
                Layout.fillHeight: true

                onWasReleased:
                {
                    calclulatorInputValidator.tryAppendText(symbol)
                }
            }

            CalculatorButton
            {
                textButton: "5"

                Layout.minimumWidth: 30
                Layout.minimumHeight: 30

                Layout.preferredWidth: 100
                Layout.preferredHeight: 100

                Layout.fillWidth: true
                Layout.fillHeight: true

                onWasReleased:
                {
                    calclulatorInputValidator.tryAppendText(symbol)
                }
            }

            CalculatorButton
            {
                textButton: "6"

                Layout.minimumWidth: 30
                Layout.minimumHeight: 30

                Layout.preferredWidth: 100
                Layout.preferredHeight: 100

                Layout.fillWidth: true
                Layout.fillHeight: true

                onWasReleased:
                {
                    calclulatorInputValidator.tryAppendText(symbol)
                }
            }

            CalculatorButton
            {
                textButton: "-"

                Layout.minimumWidth: 30
                Layout.minimumHeight: 30

                Layout.preferredWidth: 100
                Layout.preferredHeight: 100

                Layout.fillWidth: true
                Layout.fillHeight: true

                onWasReleased:
                {
                    calclulatorInputValidator.tryAppendText(symbol)
                }
            }


            //Четвёртый ряд
            CalculatorButton
            {
                textButton: "1"

                Layout.minimumWidth: 30
                Layout.minimumHeight: 30

                Layout.preferredWidth: 100
                Layout.preferredHeight: 100

                Layout.fillWidth: true
                Layout.fillHeight: true

                onWasReleased:
                {
                    calclulatorInputValidator.tryAppendText(symbol)
                }
            }

            CalculatorButton
            {
                textButton: "2"

                Layout.minimumWidth: 30
                Layout.minimumHeight: 30

                Layout.preferredWidth: 100
                Layout.preferredHeight: 100

                Layout.fillWidth: true
                Layout.fillHeight: true

                onWasReleased:
                {
                    calclulatorInputValidator.tryAppendText(symbol)
                }
            }

            CalculatorButton
            {
                textButton: "3"

                Layout.minimumWidth: 30
                Layout.minimumHeight: 30

                Layout.preferredWidth: 100
                Layout.preferredHeight: 100

                Layout.fillWidth: true
                Layout.fillHeight: true

                onWasReleased:
                {
                    calclulatorInputValidator.tryAppendText(symbol)
                }
            }

            CalculatorButton
            {
                textButton: "+"

                Layout.minimumWidth: 30
                Layout.minimumHeight: 30

                Layout.preferredWidth: 100
                Layout.preferredHeight: 100

                Layout.fillWidth: true
                Layout.fillHeight: true

                onWasReleased:
                {
                    calclulatorInputValidator.tryAppendText(symbol)
                }
            }

            //Пятый ряд
            Item
            {
                Layout.minimumWidth: 30
                Layout.minimumHeight: 30

                Layout.preferredWidth: 100
                Layout.preferredHeight: 100

                Layout.fillWidth: true
                Layout.fillHeight: true
            }

            CalculatorButton
            {
                textButton: "0"

                Layout.minimumWidth: 30
                Layout.minimumHeight: 30

                Layout.preferredWidth: 100
                Layout.preferredHeight: 100

                Layout.fillWidth: true
                Layout.fillHeight: true

                onWasReleased:
                {
                    calclulatorInputValidator.tryAppendText(symbol)
                }
            }

            CalculatorButton
            {
                textButton: "."

                Layout.minimumWidth: 30
                Layout.minimumHeight: 30

                Layout.preferredWidth: 100
                Layout.preferredHeight: 100

                Layout.fillWidth: true
                Layout.fillHeight: true

                onWasReleased:
                {
                    calclulatorInputValidator.tryAppendText(symbol)
                }
            }

            CalculatorButton
            {
                textButton: "="

                Layout.minimumWidth: 30
                Layout.minimumHeight: 30

                Layout.preferredWidth: 100
                Layout.preferredHeight: 100

                Layout.fillWidth: true
                Layout.fillHeight: true
            }
        }
    }
}
