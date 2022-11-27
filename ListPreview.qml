import QtQuick

Rectangle {
    property int w: 100

    width: w
    height: parent.height

    Item {
        width: parent.width
        height: parent.height

        anchors {
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }

        anchors.margins: 10

        Rectangle {
            width: w
            height: 200

            anchors.fill: parent
        }
    }
}


