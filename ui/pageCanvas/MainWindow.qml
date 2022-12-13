import QtQuick 2.15

Item {
    Rectangle {
        id: containerStatusBar
        anchors {
            left: parent.left
            right: parent.right
            top: parent.top
        }

        width: parent.width
        height: 35

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

        Rectangle {
            id: containerCanvasSurface

            anchors {
                left: parent.left
                top: parent.top
                bottom: parent.bottom
                right: containerPreviewList.visible ?
                           containerPreviewList.left :
                           parent.right
            }

            CanvasSurface {
                id: canvas_surface
                anchors.fill: parent
            }
        }

        Rectangle {
            id: containerPreviewList
            visible: _controllerListPreview.isVisible

            anchors {
                right: parent.right
                top: parent.top
                bottom: parent.bottom
            }

            width: 200

            ListPreview {
                id: previewList
                anchors.fill: parent
                w: 100
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
            text: _controllerPageCounter.page + " of " + _controllerPageCounter.numberOfPage

            anchors {
                right: parent.right
                top: parent.top
                bottom: parent.bottom
            }

            anchors.rightMargin: 5

            font.pixelSize: 12
        }
    }
}
