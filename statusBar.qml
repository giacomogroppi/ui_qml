import QtQuick 2.0
import QtQuick.Controls 6.3

Rectangle {
    id: statusBar
    anchors.left: parent
    anchors.right: parent
    anchors.top: parent
    width: parent.width
    height: 30

    RoundButton {
        id: back
        anchors.left: parent.left
        anchors.right: button2
        topPadding: 6

        height: parent.height
        width: height
    }

    RoundButton {
        id: button2
        anchors.left: back
        anchors.right: parent.right

        icon.source: "/home/giacomo/ui_qml/images/pen_option.png"
        icon.width: width
        icon.height: height
        icon.color: "transparent"
        icon.name: "Testing"

        height: parent.height
        width: height
    }
}
