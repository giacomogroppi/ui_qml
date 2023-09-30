import QtQuick 2.0
import QtQuick.Controls 2.12
import writernote.WQMLControllerHighlighter 1.0
import writernote.WQMLControllerPen 1.0
import writernote.WQMLControllerRubber 1.0

Rectangle {
    id: root

    property string backColor: "#00248f"
    property int hAll: 100
    property int wButton: 30
    property int wButtonColor: 30

    color: backColor
    height: hAll
    width: parent.width

    ButtonToolInstruments {
        id: buttonBack
        buttonImageSource: ":/prefix_1/icon-hide-left.png"

        onClicked: {
            mainRoot.closeMain();
        }

        anchors {
            left: parent.left
        }
        Text {
            text: qsTr("<")
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
        color: backColor
        height: parent.height
        width: wButton * 6

        WPenButton {
            id: penButton

            width: 50
            height: 50

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    _controllerToolBar.clickSelectPen();
                }
            }

            anchors {
                left: parent.left
            }
        }

        WRubberButton {
            id: rubberButton

            MouseArea {
                anchors.fill: parent
                onClicked: _controllerToolBar.clickRubber()
            }

            width: 50
            height: 50

            anchors {
                left: penButton.right
            }
        }

        WHighlighterButton {
            id: highlighterButton
            height: 50
            width: 50

            MouseArea {
                anchors.fill: parent

                onClicked: _controllerToolBar.clickHighlighter()
            }
            anchors {
                left: rubberButton.right
            }
        }


        ButtonToolInstruments {
            id: cutButton
            buttonImageSource: ":/prefix_1/images/cut_option.png"

            onClicked: _controllerToolBar.clickCut()

            anchors {
                left: highlighterButton.right
            }
            Text {
                text: qsTr("4")
            }
        }
        ButtonToolInstruments {
            id: handButton
            buttonImageSource: ":/prefix_1/images/cut_option.png"

            onClicked: _controllerToolBar.clickHand()

            anchors {
                left: cutButton.right
            }
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
                    _controllerToolBar.clickBlack();
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
                    _controllerToolBar.clickYellow();
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
                    _controllerToolBar.clickRed();
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
                    _controllerToolBar.clickWhite();
                }
            }
        }
    }

    ButtonToolInstruments {
        id: recordingButton
        buttonImageSource: ":/prefix_1/images/cut_option.png"
        height: parent.height
        width: wButton
        x: parent.width * (3 / 4)

        Text {
            text: qsTr("rec")
        }
    }

    ButtonToolInstruments {
        id: hidePreviewButton
        anchors.right: parent.right
        buttonImageSource: ":/prefix_1/images/cut_option.png"
        height: parent.height
        width: wButton

        Text {
            text: qsTr("hide preview")
        }
        MouseArea {
            anchors.fill: parent

            onClicked: {
                console.log("Click on show/hide preview");
                var isVisible = _controllerListPreview.isVisible;
                _controllerListPreview.isVisible = !isVisible;
            }
        }
    }
}
