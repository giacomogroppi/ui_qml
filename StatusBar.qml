import QtQuick 2.0
import QtQuick.Controls 6.3

Rectangle {
    width: parent.width
    height: 30

    color: "#00248f"

    ButtonToolInstruments {
        id: buttonBack
        buttonImageSource: ":/prefix_1/icon-hide-left.png"
        anchors {
            left: parent.left
            top: parent.top
            bottom: parent.bottom
        }
    }

    ButtonToolInstruments {
        id: penButton
        buttonImageSource: ":/prefix_1/images/pen_option.png"
        anchors {
            top: parent.top
            bottom: parent.bottom
            right: parent.right
        }
    }

}
