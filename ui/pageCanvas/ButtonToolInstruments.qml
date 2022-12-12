import QtQuick 2.15
import QtQuick.Controls 2.12

RoundButton {
    property string buttonImageSource: ""
    property int margin: 4

    background: Rectangle {
        color: "transparent"
    }

    anchors.margins: margin

    anchors.top: parent.top
    anchors.bottom: parent.bottom

    height: width
    width: 30

    Image {
        width: parent.width * .8
        height: width
        anchors.centerIn: parent
        source: parent.buttonImageSource
        fillMode: Image.PreserveAspectFit
    }
}
