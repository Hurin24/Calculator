import QtQuick 2.15
import QtQuick.Controls 2.15

Rectangle
{
    id: topItem

    property alias currentText: text
    property real standartOpacity: 0.5

    opacity: standartOpacity

    radius: 6

    clip: true

    Flickable
    {
        id: flickable

        anchors.fill: parent

        contentWidth: width
        contentHeight: text.contentHeight

        //Флаг автопрокрутки
        property bool autoScrollEnabled: true


        TextEdit
        {
            id: text

            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.margins: 10

            clip: true
            // readOnly: true
            cursorVisible: false
            selectByMouse: true

            textFormat: Text.RichText

            horizontalAlignment: Text.AlignLeft
            verticalAlignment: Text.AlignBottom

            font.pixelSize: 20

            wrapMode: TextArea.Wrap

            //Автопрокрутка при добавлении текста
            onTextChanged:
            {
                if(flickable.autoScrollEnabled && flickable.contentHeight > flickable.height)
                {
                    flickable.contentY = flickable.contentHeight - flickable.height
                }
            }

        }

        onContentYChanged:
        {
            //Если пользователь долистал до самого низа - включаем автопрокрутку
            if(contentY >= contentHeight - height - 5)
            {
                autoScrollEnabled = true
            }
            else
            {
                autoScrollEnabled = false
            }
        }

        //Вертикальный ScrollBar
        ScrollBar.vertical: ScrollBar
                            {
                                id: vScrollBar
                                policy: ScrollBar.AsNeeded
                                width: 12

                                contentItem: Rectangle
                                            {
                                                implicitWidth: 6
                                                radius: width / 2
                                                color: vScrollBar.pressed ? "#80000000" : "#40000000"
                                            }
                            }
    }
}
