import QtQuick
import QtQuick.Controls 6.3

Window {
    width: 1024
    height: 680
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

        statusBar {
            id: statusBar
        }

        Rectangle {
            id: rowMainFrame
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.top: statusBar.bottom
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
            anchors.bottom: parent.bottom
            width: parent.width
            height: 20
            anchors.bottomMargin: 0

            Text {
                id: textWhatPageLeft
                anchors.bottom: parent.bottom
                text: qsTr("Page: ")
                anchors.right: textEdit.left
                anchors.rightMargin: 5
                font.pixelSize: 12
                height: parent.height
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
