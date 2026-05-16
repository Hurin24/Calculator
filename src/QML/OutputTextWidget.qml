import QtQuick 2.15

Rectangle
{
    id: topItem

    property alias currentText: textEdit.text
    property real standartOpacity: 0.5

    opacity: standartOpacity

    radius: 6

    TextEdit
    {
        id: textEdit

        text: ""

        anchors.fill: parent
        anchors.margins: 15

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        readOnly: true

        font.pixelSize: 16
    }
}
