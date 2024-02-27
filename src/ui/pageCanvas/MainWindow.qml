import QtQuick 2.15
import QtQuick.Controls 2.12

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
            bottom: parent.bottom
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
            readonly property int wHeigthButton: 15
            id: containerPageCounter
            anchors {
                right: containerCanvasSurface.right
                bottom: parent.bottom
            }

            color:"red"
            width: 30
            height: 44
            anchors.bottomMargin: 0

            // Page -= 1
            Button {
                id: buttonPageUp
                anchors {
                    top: parent.top
                    right: parent.right
                    left: parent.left
                }
                height: 15
                text: "X"
            }

            // Counter for page
            Text {
                id: textWhatPageLeft
                text: _controllerPageCounter.page + "/" + _controllerPageCounter.numberOfPage

                anchors {
                    top: buttonPageUp.bottom
                    left: parent.left
                    right: parent.right
                }

                font.pixelSize: 12
            }

            // Page += 1
            Button {
                id: buttonPageDown
                anchors {
                    top: textWhatPageLeft.bottom
                    right: parent.right
                    left: parent.left
                }
                height: 15
                text: "H"
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
}
