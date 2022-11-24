import QtQuick
import QtQuick.Controls 6.3

Window {
    width: 1280
    height: 720
    minimumHeight: 600
    minimumWidth: height
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

        rightPadding: 0
        leftPadding: 0
        padding: 0

        ToolBar {
            id: toolBarInstruments
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

        ScrollView {
            id: scrollView
            anchors.top: toolBarInstruments
            anchors.bottom: rowBottom
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Row {
            id: rowBottom
            anchros.top: scrollView.bottom
            anchros.bottom: parent.bottom
            width: parent.width
            height: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0
        }
    }
}
