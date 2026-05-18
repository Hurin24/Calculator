import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.15
import Calculator 1.0

Rectangle
{
    color: Qt.rgba(0,0,0,0)

    required property CalculatorInputReader calculatorInputReader
    property alias textIndicatorWidget: textIndicatorWidget

    Connections
    {
        target: calculatorInputReader
        function onInvalidCharacter()
        {
            parallelAnim.complete()
            parallelAnim.restart()
        }
    }

    //Параллельная анимация
    ParallelAnimation
    {
        id: parallelAnim
        loops: 1

        ColorAnimation
        {
            target: textIndicatorWidget.currentText
            property: "color"
            from: "red"
            to: textIndicatorWidget.currentText.color
            duration: 400
            easing.type: Easing.InOutQuad
        }

        SequentialAnimation
        {
            id: sequentialAnimation

            property double offset: 1

            NumberAnimation
            {
                target: textIndicatorWidget.currentText
                property: "anchors.rightMargin"
                from: textIndicatorWidget.currentText.anchors.rightMargin
                to: textIndicatorWidget.currentText.anchors.rightMargin + sequentialAnimation.offset
                duration: 100
                easing.type: Easing.InOutSine
            }

            NumberAnimation
            {
                target: textIndicatorWidget.currentText
                property: "anchors.rightMargin"
                from: textIndicatorWidget.currentText.anchors.rightMargin + sequentialAnimation.offset
                to: textIndicatorWidget.currentText.anchors.rightMargin - sequentialAnimation.offset*2
                duration: 200
                easing.type: Easing.InOutSine
            }

            NumberAnimation
            {
                target: textIndicatorWidget.currentText
                property: "anchors.rightMargin"
                from: textIndicatorWidget.currentText.anchors.rightMargin - sequentialAnimation.offset
                to: textIndicatorWidget.currentText.anchors.rightMargin
                duration: 100
                easing.type: Easing.InOutSine
            }
        }
    }

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

            currentText.text: calculatorInputReader.text
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

            CalculatorButton
            {
                textButton: "C"

                Layout.minimumWidth: 30
                Layout.minimumHeight: 30

                Layout.preferredWidth: 100
                Layout.preferredHeight: 100

                Layout.fillWidth: true
                Layout.fillHeight: true

                onWasReleased:
                {
                    calculatorInputReader.clear()
                }
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

                onWasReleased:
                {
                    calculatorInputReader.chopText()
                }
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
                    calculatorInputReader.tryAppendText("/")
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
                    calculatorInputReader.tryAppendText(symbol)
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
                    calculatorInputReader.tryAppendText(symbol)
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
                    calculatorInputReader.tryAppendText(symbol)
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
                    calculatorInputReader.tryAppendText("*")
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
                    calculatorInputReader.tryAppendText(symbol)
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
                    calculatorInputReader.tryAppendText(symbol)
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
                    calculatorInputReader.tryAppendText(symbol)
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
                    calculatorInputReader.tryAppendText(symbol)
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
                    calculatorInputReader.tryAppendText(symbol)
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
                    calculatorInputReader.tryAppendText(symbol)
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
                    calculatorInputReader.tryAppendText(symbol)
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
                    calculatorInputReader.tryAppendText(symbol)
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
                    calculatorInputReader.tryAppendText(symbol)
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
                    calculatorInputReader.tryAppendText(symbol)
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

                onWasReleased:
                {
                    calculatorInputReader.createRequest()
                }
            }
        }
    }
}
