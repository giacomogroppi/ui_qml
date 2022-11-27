import QtQuick 2.0
import QtQuick.Controls 6.3

Rectangle {
    property string backColor: "#00248f"
    property int hAll: 30
    property int wButton: 30

    id: root
    width: parent.width
    height: hAll

    color: backColor

    ButtonToolInstruments {
        id: buttonBack
        buttonImageSource: ":/prefix_1/icon-hide-left.png"
        anchors {
            left: parent.left
            top: parent.top
            bottom: parent.bottom

        }
    }

    Rectangle {
        id: containerCenter
        anchors.centerIn: parent

        height: parent.height
        width: wButton * 5
        color: backColor

        ButtonToolInstruments {
            id: penButton
            buttonImageSource: ":/prefix_1/images/pen_option.png"
            anchors {
                left: parent.rigth
                right: rubberButton.left
            }
        }

        ButtonToolInstruments {
            id: rubberButton
            buttonImageSource: ":/prefix_1/images/rubber_option.png"
            anchors {
                left: penButton.right
                right: highlighterButton.left
            }
        }

        ButtonToolInstruments {
            id: highlighterButton
            buttonImageSource: ":/prefix_1/images/highlighter_option.png"
            anchors {
                left: rubberButton.right
                right: parent.right
            }
        }
    }
}
