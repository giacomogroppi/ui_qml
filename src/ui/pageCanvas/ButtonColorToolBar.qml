import QtQuick 2.15
import QtQuick.Controls 2.12

RoundButton {
    property int objectTopMargin: 4
    property int objectBottomMargin: 4

    required property string colorName
    required property bool selected

    width: height

    anchors {
        top: parent.top
        bottom: parent.bottom
        topMargin: objectTopMargin
        bottomMargin: objectBottomMargin
        leftMargin: 4
    }

    background: Rectangle {
        color: colorName
        border.color: selected ? "white" : parent.colorName
        border.width: 1.5
        radius: 50
    }
}
