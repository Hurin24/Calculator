import QtQuick 2.15
import QtQuick.Layouts 1.15

Rectangle
{
    id: topItem

    property alias topTextEdit: topTextEdit
    property alias bottomTextEdit: bottomTextEdit

    property real standartOpacity: 0.5

    opacity: standartOpacity

    radius: 6

    clip: true

    ColumnLayout
    {
        anchors.fill: parent
        anchors.margins: 10

        spacing: 10

        Rectangle
        {
            Layout.minimumWidth: 100
            Layout.minimumHeight: 50

            Layout.preferredWidth: 100
            Layout.preferredHeight: 100

            Layout.fillWidth: true
            Layout.fillHeight: true

            opacity: standartOpacity

            radius: 6

            clip: true

            TextEdit
            {
                id: topTextEdit

                anchors.fill: parent
                anchors.margins: 10

                clip: true
                readOnly: true
                cursorVisible: false
                selectByMouse: true

                text: ""

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                font.pixelSize: 22
            }
        }

        Rectangle
        {
            Layout.minimumWidth: 100
            Layout.minimumHeight: 50

            Layout.preferredWidth: 100
            Layout.preferredHeight: 100

            Layout.fillWidth: true
            Layout.fillHeight: true

            opacity: standartOpacity

            radius: 6

            clip: true

            TextEdit
            {
                id: bottomTextEdit

                anchors.fill: parent
                anchors.margins: 10

                clip: true
                readOnly: false
                cursorVisible: true
                selectByMouse: true

                text: ""

                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter

                font.pixelSize: 20
            }
        }
    }
}
