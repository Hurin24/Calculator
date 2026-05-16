import QtQuick 2.15

Rectangle
{
    id: topItem

    property alias textButton: textButton.text
    property real standartOpacity: 0.5

    signal wasReleased(string symbol)

    opacity: standartOpacity

    radius: 6

    Text
    {
        id: textButton

        text: ""

        anchors.fill: parent

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        font.pixelSize: 16
    }

    MouseArea
    {
        anchors.fill: parent
        hoverEnabled: true

        onReleased:
        {
            //Проверяем, находится ли мышь внутри области в момент отпускания
            if(containsMouse)
            {
                wasReleased(textButton.text)
            }
        }

        onEntered:
        {
            topItem.opacity = topItem.standartOpacity + 0.2
        }

        onExited:
        {
            topItem.opacity = topItem.standartOpacity
        }
    }
}
