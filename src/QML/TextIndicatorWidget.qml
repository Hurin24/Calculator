import QtQuick 2.15

Rectangle
{
    id: topItem

    property alias currentText: text
    property real standartOpacity: 0.5

    opacity: standartOpacity

    radius: 6

    clip: true

    TextEdit
    {
        id: text

        clip: true
        readOnly: true
        cursorVisible: false
        selectByMouse: true

        text: ""

        anchors.right: parent.right
        anchors.top: parent.top
        anchors.bottom: parent.bottom

        anchors.margins: 15

        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter

        font.pixelSize: 20
    }
}
