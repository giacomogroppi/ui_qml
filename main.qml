import QtQuick
import QtQuick.Controls 6.3

Window {
    width: 1024
    height: 680
    minimumHeight: 600
    minimumWidth: height
    visible: true
    title: qsTr("Hello World")

    Rectangle {
        id: containerStatusBar
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }

        width: parent.width
        height: 30

        StatusBar {
            id: statusBar
            anchors.fill: parent
        }
    }

    Rectangle {
        id: rowMainFrame
        anchors {
            left: parent.left
            right: parent.right
            top: containerStatusBar.bottom
            bottom: rowBottom.top
            margins: 0
        }

        CanvasSurcace {
            id: canvas_surface
            anchors {
                left: parent.left
                top: parent.top
                bottom: parent.bottom
                right: previewList.right
            }
        }


        ListPreview {
            id: previewList
            anchors {
                right: parent.right
                top: parent.top
                bottom: parent.bottom
            }
        }
    }

    Rectangle {
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
