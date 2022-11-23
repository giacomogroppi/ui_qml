import QtQuick
import QtQuick.Controls 6.3

Window {
    width: 1280
    height: 720
    visible: true
    title: qsTr("Hello World")

    Frame {
        id: frame
        anchors.bottom: parent
        anchors.top: parent
        anchors.left: parent
        anchors.right: parent
        width: parent.width
        height: parent.height

        ToolBar {
            id: toolBar
            anchors.left: parent
            anchors.right: parent
            anchors.top: parent
            width: parent.width
            height: 50
            spacing: 10

            RoundButton {
                id: button
                anchors.left: parent.left
                anchors.right: button2

                height: parent.height - parent.spacing

                text: qsTr("button")
            }

            RoundButton {
                id: button2
                anchors.left: button
                anchors.right: parent.right
                icon:
            }
        }
    }
}
