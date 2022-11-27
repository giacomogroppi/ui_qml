import QtQuick

Rectangle {
    Item {
        width: 100
        height: parent.height

        anchors {
            right: parent.right
            top: parent.top
            bottom: parent.bottom
        }

        anchors.margins: 10

        Rectangle {
            width: parent.width
            height: 200
            color: "black"
            anchors.fill: parent
        }
    }
}


