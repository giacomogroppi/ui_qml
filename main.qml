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

        Rectangle {
            id: rowMainFrame
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: toolBarInstruments.bottom
            anchors.bottom: rowBottom.top
            anchors.leftMargin: 0
            anchors.rightMargin: 0
            anchors.bottomMargin: 0
            anchors.topMargin: 0

            ScrollView {
                id: canvasSurface
                anchors.left: parent.left
                anchors.right: previewList.left
                anchors.top: parent.top
                anchors.bottom: parent.right

            }

            ListView {
                id: previewList
                width: 100
                anchors.right: parent.right
                anchors.top: parent.top
                anchors.bottom: parent.border
                anchors.rightMargin: 0
                anchors.bottomMargin: 0
                anchors.topMargin: 0
                height: parent.height

                Rectangle {
                    width: parent.width
                    height: 200
                    color: "black"
                }
            }
        }

        Row {
            id: rowBottom
            anchros.top: rowMainFrame.bottom
            anchros.bottom: parent.bottom
            width: parent.width
            height: 20
            anchors.bottom: parent.bottom
            anchors.bottomMargin: 0

            Text {
                id: textWhatPageLeft
                anchros.top: scrollView.bottom
                anchros.bottom: parent.bottom
                text: qsTr("Page: ")
                anchors.right: textEdit.left
                anchors.rightMargin: 5
                font.pixelSize: 12
            }

            TextEdit {
                id: textEdit
                width: 20
                height: parent.height
                text: qsTr("1")
                anchors.right: textWhatPageRigth.left
                font.pixelSize: 12
                anchors.rightMargin: 0
            }

            Text {
                id: textWhatPageRigth
                text: qsTr(" of ")
                anchors.right: totalPage.left
                anchors.rightMargin: 6
                font.pixelSize: 12
                height: parent.height
            }

            Text {
                id: totalPage
                text: qsTr("Text")
                anchors.right: parent.right
                font.pixelSize: 12
                anchors.rightMargin: 0
            }


        }
    }
}
