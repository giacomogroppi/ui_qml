import QtQuick 2.0
import QtQuick.Controls 2.12

Rectangle {
    property string backColor: "#00248f"
    property int hAll: 100
    property int wButton: 30
    property int wButtonColor: 30

    id: root
    width: parent.width
    height: hAll

    color: backColor

    ButtonToolInstruments {
        id: buttonBack
        buttonImageSource: ":/prefix_1/icon-hide-left.png"
        anchors {
            left: parent.left
        }
        Text {
            text: qsTr("back")
        }
    }

    ButtonToolInstruments {
        id: undoButton
        buttonImageSource: ""
        anchors {
            left: buttonBack.right
        }
        Text {
            text: qsTr("undo")
        }
    }

    Rectangle {
        id: containerCenter
        anchors.centerIn: parent

        height: parent.height
        width: wButton * 6
        color: backColor

        ButtonToolInstruments {
            id: penButton
            buttonImageSource: ":/prefix_1/images/pen_option.png"
            anchors {
                left: parent.left
            }

            onClicked: {
                _controllerToolBar.clickSelectPen()
            }

            Text {
                text: qsTr("1")
            }
        }

        ButtonToolInstruments {
            id: rubberButton
            buttonImageSource: ":/prefix_1/images/rubber_option.png"
            anchors {
                left: penButton.right
            }

            onClicked: _controllerToolBar.clickRubber()

            Text {
                text: qsTr("2")
            }
        }

        ButtonToolInstruments {
            id: highlighterButton
            buttonImageSource: ":/prefix_1/images/highlighter_option.png"
            anchors {
                left: rubberButton.right
            }

            onClicked: _controllerToolBar.clickHighlighter()

            Text {
                text: qsTr("3")
            }
        }

        ButtonToolInstruments {
            id: cutButton
            buttonImageSource: ":/prefix_1/images/cut_option.png"
            anchors {
                left: highlighterButton.right
            }

            onClicked: _controllerToolBar.clickCut()

            Text {
                text: qsTr("4")
            }
        }

        ButtonToolInstruments {
            id: handButton
            buttonImageSource: ":/prefix_1/images/cut_option.png"
            anchors {
                left: cutButton.right
            }

            onClicked: _controllerToolBar.clickHand()

            Text {
                text: qsTr("5")
            }
        }

        ButtonColorToolBar {
            id: colorBlack
            colorName: "black"
            selected: _controllerToolBar.isBlack
            anchors {
                left: handButton.right
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    _controllerToolBar.clickBlack()
                }
            }
        }

        ButtonColorToolBar {
            id: colorYellow
            colorName: "yellow"
            selected: _controllerToolBar.isYellow
            anchors {
                left: colorBlack.right
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    _controllerToolBar.clickYellow()
                }
            }
        }

        ButtonColorToolBar {
            id: colorRed
            colorName: "red"
            selected: _controllerToolBar.isRed
            anchors {
                left: colorYellow.right
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    _controllerToolBar.clickRed()
                }
            }
        }

        ButtonColorToolBar {
            id: colorWhite
            colorName: "white"
            selected: _controllerToolBar.isWhite
            anchors {
                left: colorRed.right
            }
            MouseArea {
                anchors.fill: parent
                onClicked: {
                    _controllerToolBar.clickWhite()
                }
            }
        }
    }

    ButtonToolInstruments {
        id: recordingButton
        buttonImageSource: ":/prefix_1/images/cut_option.png"
        width: wButton
        height: parent.height

        x: parent.width * (3/4)

        Text {
            text: qsTr("rec")
        }
    }

    ButtonToolInstruments {
        id: hidePreviewButton
        buttonImageSource: ":/prefix_1/images/cut_option.png"
        width: wButton
        height: parent.height

        anchors.right: parent.right

        Text {
            text: qsTr("hide preview")
        }

        MouseArea {
            anchors.fill: parent
            onClicked: {
                console.log("Click on show/hide preview")
                var isVisible = _controllerListPreview.isVisible
                _controllerListPreview.isVisible = !isVisible
            }
        }
    }
}
